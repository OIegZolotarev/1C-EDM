#include "frmMain.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace DatabaseRegister;

int main(array<String^>^ args) {
	
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	
	
	DatabaseRegister::PlatformManager::ScanInstalledPlatforms();
	DbRegisterToolVS::frmMain ^ frm = gcnew DbRegisterToolVS::frmMain(gcnew DBAdapter(),args);

	Application::Run(frm);

}