#include "dbscanner.h"

#pragma once

using namespace System::Data::SQLite;
using namespace System;


ref class DBClient;
ref class DBProject;

typedef Collections::Generic::List<DBClient^> DBClientsList;
typedef Collections::Generic::List<DBProject^> DBProjectList;


#define SETTING_WORK_DIR "com.WorkDir"
#define SETTING_PROJECT_DIR "com.ProjectsDir"

public ref class DBAdapter
{
	SQLiteConnection ^ m_DBConnection;
public:
	void EnsureDirExists(String ^ path);

	DBAdapter(void);
	~DBAdapter(void);
	void QueryClientList(DBClientsList^ list);
	void QueryProjectList(DBProjectList^ list,Int64 filter);
	bool RegisterClient(String ^ strClientName);
	bool RegisterProject(String ^ strProjectName,String ^ strProjectDescription,Int64 ClientID);

	void RegisterProject(DBProject ^ p);

	String^ QuerySetting(String ^ settingName);
	String^ QuerySetting(String ^ settingName,String ^ defaultValue);
	void WriteSetting(String ^ settingName,String ^ settingValue);

	SQLiteConnection ^ GetDBConnetion()
	{
		return m_DBConnection;
	}
	void RegisterDB( DBProject^ project, DBScanRecordsList ^ l );
};

public ref class DBClient
{
public:
	Int64 m_iDBId;;
	String^ m_strName;

	DBClient();
	~DBClient();

	void QueryFromDB(DBAdapter ^ adapter);
	void WriteToDB(DBAdapter ^ adapter);

	virtual String ^ ToString() override
	{
		return m_strName;
	}

	virtual bool Equals(DBClient ^ c)
	{
		if (!c) return false;

		if (c->m_iDBId == m_iDBId) return true;

		return false;
	}
};

public ref class DBProject
{
	String ^ m_strRepresentation;
public:
	DBProject();
	~DBProject();

	Int64 m_iDBId;
	String ^ m_strTitle;
	String ^ m_strDescription;
	DBClient ^ m_DBClient;

	void QueryFromDB(DBAdapter ^ adapter);
	void WriteToDB(DBAdapter ^ adapter);

	virtual String ^ ToString() override
	{
		return m_strTitle;
	}

	String ^ FormatProjectPath()
	{
		String ^ str = "#" + m_iDBId.ToString() + "_" +  m_strTitle + "_" + "_#" +m_DBClient->m_iDBId.ToString() + "_" + m_DBClient->m_strName;
		str = str->Replace(" ","_");
		return str;
	}

	void QueryClient(Int64 id,DBAdapter ^ db)
	{
		m_DBClient = gcnew DBClient();
		m_DBClient->m_iDBId = id;
		m_DBClient->QueryFromDB(db);
	}
};