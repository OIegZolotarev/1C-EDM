#include "frmMain.h"


using namespace System;
using namespace System::Windows::Forms;

int main(array<String^>^ args) {
	
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	
	
	DbRegisterToolVS::frmMain ^ frm = gcnew DbRegisterToolVS::frmMain(gcnew DBAdapter(),args);

	Application::Run(frm);

}