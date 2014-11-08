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
