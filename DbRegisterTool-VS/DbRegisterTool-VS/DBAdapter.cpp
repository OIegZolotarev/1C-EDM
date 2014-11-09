#include "DBAdapter.h"

using namespace DatabaseRegister;
using namespace Windows::Forms;

DBAdapter::DBAdapter(void)
{
	m_DBConnection = gcnew SQLiteConnection("Data Source=database.db;Version=3;");
	m_DBConnection->Open();
	
}

DBAdapter::~DBAdapter(void)
{
	m_DBConnection->Close();
}

bool DBAdapter::RegisterClient(String ^ strClientName)
{
	auto CmdText = String::Format("INSERT INTO CLIENTS (rowid,name) VALUES(NULL,\"{0}\")",strClientName);
	SQLiteCommand ^ c = gcnew SQLiteCommand(CmdText,m_DBConnection);
	return c->ExecuteNonQuery() != 0;
}


bool DBAdapter::RegisterProject(String ^ strProjectName,String ^ strProjectDescription,Int64 ClientID)
{
	auto CmdText = String::Format("INSERT INTO Projects (rowid,title,description,clientid) VALUES(NULL,\"{0}\",\"{1}\",\"{2}\")",strProjectName,strProjectDescription,ClientID);
	SQLiteCommand ^ c = gcnew SQLiteCommand(CmdText,m_DBConnection);
	return c->ExecuteNonQuery() != 0;
}

void DBAdapter::RegisterProject( DBProject ^ p )
{
	p->WriteToDB(this);
}

void DBAdapter::QueryClientList(DBClientsList^ list)
{
	auto CmdText = String::Format("SELECT * FROM Clients");
	list->Clear();
	SQLiteCommand ^ c = gcnew SQLiteCommand(CmdText,m_DBConnection);
	SQLiteDataReader^ r = c->ExecuteReader();

	while(r->Read())
	{
		DBClient ^ c = gcnew DBClient();
		c->m_iDBId = Int64::Parse(r["id"]->ToString());
		c->m_strName = r["name"]->ToString();
		list->Add(c);
	}
}

void DBAdapter::QueryProjectList( DBProjectList^ list,Int64 filter)
{
	auto CmdText = String::Format("SELECT * FROM Projects");

	if (filter != -1)
	{
		CmdText = String::Format("{0} WHERE clientId = {1}",CmdText,filter);
	}

	list->Clear();
	SQLiteCommand ^ c = gcnew SQLiteCommand(CmdText,m_DBConnection);
	SQLiteDataReader^ r = c->ExecuteReader();

	while(r->Read())
	{
		DBProject ^ c = gcnew DBProject();
		c->m_iDBId = Int64::Parse(r["id"]->ToString());
		c->m_strDescription = r["description"]->ToString();
		c->m_strTitle = r["title"]->ToString();
		
		c->m_DBClient = gcnew DBClient();
		c->m_DBClient->m_iDBId = Int64::Parse(r["clientId"]->ToString());
		c->m_DBClient->QueryFromDB(this);
				
		list->Add(c);
	}
}

String^ DBAdapter::QuerySetting( String ^ settingName )
{
	return QuerySetting(settingName,"");
}

String^ DBAdapter::QuerySetting( String ^ settingName,String ^ defaultValue )
{
	String ^ cmdText = "SELECT * FROM Settings WHERE settingId = :Id LIMIT 1";
	SQLiteCommand ^ c = gcnew SQLiteCommand(cmdText,m_DBConnection);

	SQLiteParameter ^ p = gcnew SQLiteParameter;
	p->ParameterName = "Id";
	p->Value = settingName;

	c->Parameters->Add(p);

	SQLiteDataReader ^ r = c->ExecuteReader();

	if (r->Read())
	{
		return r["settingValue"]->ToString();
	}
	else return defaultValue;
}

void DBAdapter::WriteSetting( String ^ settingName,String ^ settingValue )
{
	String ^ OldValue = QuerySetting(settingName);
	String ^ cmdText = "";


	if (OldValue != "")
	{
		cmdText = "UPDATE Settings SET settingValue=:Value WHERE settingId=:Id";
	}
	else
	{
		cmdText = "INSERT INTO Settings (id,settingId,settingValue) VALUES(NULL,:Id,:Value)";
	}

	SQLiteCommand ^ c = gcnew SQLiteCommand(cmdText,m_DBConnection);

	SQLiteParameter ^ p = gcnew SQLiteParameter;
	p->ParameterName = "Id";
	p->Value = settingName;
	c->Parameters->Add(p);

	p = gcnew SQLiteParameter;
	p->ParameterName = "Value";
	p->Value = settingValue;
	c->Parameters->Add(p);

	c->ExecuteNonQuery();
}

void DBAdapter::EnsureDirExists( String ^ path )
{
	if (!System::IO::Directory::Exists(path))
	{
		System::IO::Directory::CreateDirectory(path);
	}
}

void DBAdapter::RegisterDB( DBProject^ project, DBScanRecordsList ^ l )
{
	for each(DBScanRecord ^ r in l)
	{
		EnterpriseDatabase ^ d = gcnew EnterpriseDatabase;
		DatabaseRegister::DBSettingsForm ^ pForm = gcnew DatabaseRegister::DBSettingsForm(d);
		DialogResult ^ r = pForm->ShowDialog();

		if (r == DialogResult::OK)
		{
			d->WriteToDB();
		}
	}
	
}

DBClient::DBClient()
{
	m_strName = String::Format("");
	m_iDBId = 0;
}

DBClient::~DBClient()
{

}

void DBClient::QueryFromDB( DBAdapter ^ adapter )
{
	auto CmdText = String::Format("SELECT * FROM Clients WHERE id = {0}",m_iDBId);
	SQLiteCommand ^ c = gcnew SQLiteCommand(CmdText,adapter->GetDBConnetion());
	
	SQLiteDataReader ^ Reader = c->ExecuteReader();

	if (Reader->Read())
	{
		m_strName = Reader["name"]->ToString();
	}
}

void DBClient::WriteToDB( DBAdapter ^ adapter )
{
	String^CmdText;

	if (m_iDBId != 0)
		CmdText = String::Format("UPDATE Clients SET name = \"{0}\" WHERE id = {1}",m_strName,m_iDBId);
	else 
		CmdText = String::Format("INSERT INTO Clients (rowid,name) VALUES(NULL,\"{0}\")",m_strName);

	SQLiteCommand ^ c = gcnew SQLiteCommand(CmdText,adapter->GetDBConnetion());
	int r = c->ExecuteNonQuery();

	m_iDBId = adapter->GetDBConnetion()->LastInsertRowId;
}

DBProject::DBProject()
{
	m_strDescription = String::Format("");
	m_strTitle = String::Format("");
	m_strRepresentation = String::Format("");


	m_iDBId = 0;
	m_DBClient = nullptr;
}

DBProject::~DBProject()
{

}

void DBProject::QueryFromDB( DBAdapter ^ adapter )
{
	if (m_iDBId == 0) return;

	auto CmdText = String::Format("SELECT * From Projects WHERE id = {0}",m_iDBId);

	SQLiteCommand ^ c = gcnew SQLiteCommand(CmdText,adapter->GetDBConnetion());

	SQLiteDataReader ^ r = c->ExecuteReader();

	if (r->Read())
	{
		m_strTitle = r["title"]->ToString();
		m_strDescription = r["description"]->ToString();
		m_DBClient = gcnew DBClient();
		m_DBClient->m_iDBId = Int64::Parse(r["clientId"]->ToString());
		m_DBClient->QueryFromDB(adapter);
	}

}

void DBProject::WriteToDB( DBAdapter ^ adapter )
{
	String^CmdText;

	if (m_iDBId != 0)
		CmdText = String::Format("UPDATE Projects SET title = \"{0}\",description = \"{1}\",clientId={2} WHERE id = {3}",m_strTitle,m_strDescription,m_DBClient->m_iDBId,m_iDBId);
	else 
		CmdText = String::Format("INSERT INTO Projects (rowid,title,description,clientId) VALUES(NULL,\"{0}\",\"{1}\",{2})",m_strTitle,m_strDescription,m_DBClient->m_iDBId);

	SQLiteCommand ^ c = gcnew SQLiteCommand(CmdText,adapter->GetDBConnetion());
	int r = c->ExecuteNonQuery();

	m_iDBId = adapter->GetDBConnetion()->LastInsertRowId;

	// Создадим или переименуем папку проекта
	String ^ workDir = adapter->QuerySetting(SETTING_WORK_DIR);
	String ^ projectsdir = adapter->QuerySetting(SETTING_PROJECT_DIR,"Projects");
	
	if (workDir == "") 
		return;
		
	adapter->EnsureDirExists(workDir);
	adapter->EnsureDirExists(workDir + "/" + projectsdir);

	String ^ projectPath = String::Format("{0}/{1}/{2}",workDir,projectsdir,FormatProjectPath());
	adapter->EnsureDirExists(projectPath);

	array<String^>^ projectDirs = gcnew array<String^>(7); 
	

	projectDirs[0] = String::Format("{0}/bases",projectPath);
	projectDirs[1] = String::Format("{0}/backups",projectPath);
	projectDirs[2] = String::Format("{0}/cf",projectPath);
	projectDirs[3] = String::Format("{0}/epf",projectPath);
	projectDirs[4] = String::Format("{0}/erf",projectPath);
	projectDirs[5] = String::Format("{0}/notes",projectPath);
	projectDirs[6] = String::Format("{0}/misc",projectPath);

	for each(String ^ dir in projectDirs)
		adapter->EnsureDirExists(dir);

}
