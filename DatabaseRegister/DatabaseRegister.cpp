// ֳכאגםûי DLL-פאיכ.

#include "stdafx.h"
#include "DatabaseRegister.h"

using namespace System::IO;
using namespace System::Collections::Generic;


DatabaseRegister::EnterpriseDatabase::EnterpriseDatabase()
{
	m_Description = m_EnterpiseId = m_Path = m_Title = "";
	m_Type = eEnterpiseDBTypes::BT_FILE;
	m_LaunchType = eLaunchTypes::LT_DONT_CARE;
}

DatabaseRegister::EnterpriseDatabase::~EnterpriseDatabase()
{

}

void DatabaseRegister::EnterpriseDatabase::QueryFromDB()
{

}

void DatabaseRegister::EnterpriseDatabase::WriteToDB()
{

}

void DatabaseRegister::PlatformManager::ScanInstalledPlatforms()
{
	m_PlatformList = gcnew Collections::Generic::List<EnterpriseVersionDescriptor^>;
	m_PlatformList->Clear();

	String ^ programFilesPath = Environment::GetFolderPath(Environment::SpecialFolder::ProgramFiles);
	auto subdirs = System::IO::Directory::EnumerateDirectories(programFilesPath,"1cv*");

	for each(String ^ dir in subdirs)
	{
		if (dir == "1cv81")
		{
			EnterpriseVersionDescriptor ^ desc = gcnew EnterpriseVersionDescriptor();
			desc->m_InstallPath = programFilesPath + "/" + dir;
			desc->m_MajorVersion = eMajorEnterpriseVer::V81;
			desc->m_Ver1 = 8;
			desc->m_Ver2 = 1;

			m_PlatformList->Add(desc);
		}
		else
		{
			auto verDirs = System::IO::Directory::EnumerateDirectories(dir,"8.*");		
			
			for each(String ^ verDir in verDirs)
			{
				Int16 ver[4];
				auto folder = IO::Path::GetFileName(verDir);
				auto versionDigits = folder->Split(L'.');

				if (versionDigits->Length != 4)
				{
					continue;
				}

				for(int i = 0 ; i < 4 ; i++)	
				{
					ver[i] = Int16::Parse(versionDigits[i]);
				}
				
				if (!System::IO::File::Exists(verDir + "/bin/1cv8.exe"))
				{
					continue;
				}

				EnterpriseVersionDescriptor ^ desc = gcnew EnterpriseVersionDescriptor();
				desc->m_Ver1 = ver[0];
				desc->m_Ver2 = ver[1];
				desc->m_Ver3 = ver[2];
				desc->m_Ver4 = ver[3];

				desc->m_InstallPath = verDir;
				desc->m_MajorVersion = (ver[1] == 2 ? eMajorEnterpriseVer::V82 : eMajorEnterpriseVer::V83);

				m_PlatformList->Add(desc);
			}
		}
	}

}

namespace DatabaseRegister
{
	Collections::Generic::List<EnterpriseVersionDescriptor^> ^ DatabaseRegister::PlatformManager::GetPlatformList()
	{
		return m_PlatformList;
	}
}


