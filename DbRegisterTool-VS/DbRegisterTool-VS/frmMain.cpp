#include "frmMain.h"
#include "DBScanner.h"

void DbRegisterToolVS::frmMain::RefereshClientsList()
{
	DBClientsList^ l = gcnew DBClientsList;
	m_DBAdapter->QueryClientList(l);

	cbClientsList->Items->Clear();

	for each(DBClient ^ client in l)
	{
		int r = cbClientsList->Items->Add(client);
	}

	cbClientsList->SelectedIndex = -1;
	cbClientsList->Text = "<Выберите...>";
}

void DbRegisterToolVS::frmMain::RefreshProjectList()
{
	DBProjectList^ l = gcnew DBProjectList;

	Int64 filter = -1;

	DBClient ^ c = (DBClient^)cbClientsList->SelectedItem;

	if (c)
	{
		filter = c->m_iDBId;
	}

	m_DBAdapter->QueryProjectList(l,filter);

	cbProjectsList->Items->Clear();

	for each(DBProject ^ project in l)
	{
		int r = cbProjectsList->Items->Add(project);
	}

	cbProjectsList->SelectedIndex = -1;
	cbProjectsList->Text = "<Выберите...>";

	if (cbProjectsList->Items->Count == 1)
		cbProjectsList->SelectedIndex = 0;
}

void DbRegisterToolVS::frmMain::ScanBasesList( String ^ path )
{
	DBScanRecordsList ^ l = gcnew DBScanRecordsList;
	DBScanner::ScanPath(path,l);

	cbFoundDatabases->Items->Clear();

	for each(DBScanRecord ^ baseFound in l)
	{
		cbFoundDatabases->Items->Add(baseFound);
	}
}

System::Void DbRegisterToolVS::frmMain::btAddBases_Click( System::Object^ sender, System::EventArgs^ e )
{
	if (cbProjectsList->SelectedIndex == -1)
	{
		Windows::Forms::MessageBox::Show("Не указан проект!");
		return;
	}

	DBScanRecordsList ^ l = gcnew DBScanRecordsList;

	for each(DBScanRecord ^ r in cbFoundDatabases->CheckedItems)
	{
again:
		String ^ name = "";
		Windows::Forms::DialogResult dr = ShowInputDialog(name,"Введите название для \"" + r->m_strPath + "\"");

		if (dr == Windows::Forms::DialogResult::Cancel || name == "")
		{
			Windows::Forms::DialogResult dr2 = Windows::Forms::MessageBox::Show(this,"Отменить добавление\"" + r->m_strPath + "\"?" ,"Регистрация баз данных",Windows::Forms::MessageBoxButtons::YesNo);

			if (dr2 == Windows::Forms::DialogResult::Yes)
			{
				continue;
			}
			else goto again;
		}

		r->m_strName = name;
		l->Add(r);
	}

	m_DBAdapter->RegisterDB((DBProject^)cbProjectsList->SelectedItem,l);
}

System::Void DbRegisterToolVS::frmMain::frmMain_Load( System::Object^ sender, System::EventArgs^ e )
{

}

System::Void DbRegisterToolVS::frmMain::btInvert_Click( System::Object^ sender, System::EventArgs^ e )
{
	for(int i = 0 ; i < cbFoundDatabases->Items->Count ; i++)
	{
		CheckState rev = cbFoundDatabases->GetItemCheckState(i);
		if (rev == CheckState::Checked)
			rev = CheckState::Unchecked;
		else rev = CheckState::Checked;

		cbFoundDatabases->SetItemCheckState(i,rev);
	}
}

System::Void DbRegisterToolVS::frmMain::btUnselectAll_Click( System::Object^ sender, System::EventArgs^ e )
{
	for(int i = 0 ; i < cbFoundDatabases->Items->Count ; i++)
	{
		cbFoundDatabases->SetItemCheckState(i,CheckState::Unchecked);
	}
}

System::Void DbRegisterToolVS::frmMain::btSelectAll_Click( System::Object^ sender, System::EventArgs^ e )
{
	for(int i = 0 ; i < cbFoundDatabases->Items->Count ; i++)
	{
		cbFoundDatabases->SetItemCheckState(i,CheckState::Checked);
	}
}

System::Void DbRegisterToolVS::frmMain::cbClientsList_SelectedIndexChanged( System::Object^ sender, System::EventArgs^ e )
{
	RefreshProjectList();
}

System::Void DbRegisterToolVS::frmMain::comboBox1_SelectedIndexChanged( System::Object^ sender, System::EventArgs^ e )
{

}

System::Void DbRegisterToolVS::frmMain::btAddProject_Click( System::Object^ sender, System::EventArgs^ e )
{
	frmAddProject ^ frm = gcnew frmAddProject(m_DBAdapter,(DBClient^)cbClientsList->SelectedItem);
	frm->ShowDialog();
	RefreshProjectList();
}

System::Void DbRegisterToolVS::frmMain::button1_Click( System::Object^ sender, System::EventArgs^ e )
{
	frmAddClient ^ frm = gcnew frmAddClient(m_DBAdapter);
	frm->ShowDialog();
	RefereshClientsList();
}

DbRegisterToolVS::frmMain::~frmMain()
{
	if (components)
	{
		delete components;
	}
}

DbRegisterToolVS::frmMain::frmMain( DBAdapter ^ db,array<String^>^ args )
{
	InitializeComponent();
	//
	//TODO: добавьте код конструктора
	//

	m_DBAdapter = db;
	RefereshClientsList();
	RefreshProjectList();

	ScanBasesList("E:\\Tmp\\DebugDBReg\\");
}
