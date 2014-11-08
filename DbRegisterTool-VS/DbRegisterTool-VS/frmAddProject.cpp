#include "frmAddProject.h"


void DbRegisterToolVS::frmAddProject::RefreshClientsList()
{
	DBClientsList^ l = gcnew DBClientsList;
	m_DBAdapter->QueryClientList(l);

	cbClientsList->Items->Clear();

	cbClientsList->SelectedIndex = -1;
	cbClientsList->Text = "<Выберите...>";

	for each(DBClient ^ client in l)
	{
		int r = cbClientsList->Items->Add(client);
		if (client->Equals(m_Filter))
			cbClientsList->SelectedIndex = cbClientsList->Items->Count - 1;
	}

	
	
}
