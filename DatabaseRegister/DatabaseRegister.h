// DatabaseRegister.h

#pragma once
#include <vector>


using namespace System;
using namespace System::Collections;
using namespace System::Data::SQLite;

namespace DatabaseRegister {

		public enum class eEnterpiseDBTypes
		{
			BT_FILE = 0
		};

		public enum class eLaunchTypes
		{
			LT_DONT_CARE = 0,
			LT_THICK_CLIENT,
			LT_THIN_CLIENT
		};

		public enum class eMajorEnterpriseVer
		{
			V80,
			V81,
			V82,
			V83,
			UNKNOWN
		};

		public ref class EnterpriseVersionDescriptor
		{
		public:
			String ^ m_InstallPath;
			short m_Ver1;
			short m_Ver2;
			short m_Ver3;
			short m_Ver4;
			
			eMajorEnterpriseVer m_MajorVersion;

			EnterpriseVersionDescriptor()
			{
				m_InstallPath = "";
				
				m_Ver1 = 0;
				m_Ver2 = 0;
				m_Ver3 = 0;
				m_Ver4 = 0;


				m_MajorVersion = eMajorEnterpriseVer::UNKNOWN;
			}

			virtual String ^ ToString() override
			{
				return String::Format("{0}.{1}.{2}.{3}",m_Ver1,m_Ver2,m_Ver3,m_Ver4);
			}

			bool Older(EnterpriseVersionDescriptor ^ other)
			{
				if (m_Ver1 < other->m_Ver1)
					return true;
				else if (m_Ver1 > other->m_Ver1)
					return false;
				else
				{
					if (m_Ver2 < other->m_Ver2)
						return true;
					else if (m_Ver2 > other->m_Ver2)
						return false;
					else
					{
						if (m_Ver3 < other->m_Ver3)
							return true;
						else if (m_Ver3 > other->m_Ver3)
							return false;
						else
						{
							if (m_Ver4 < other->m_Ver4)
								return true;
							else if (m_Ver4 > other->m_Ver4)
								return false;
							else 
								return false;
						}
					}
				}
				
			}
		};

		public ref class EnterpriseDatabase
		{
		public:
			String ^ m_EnterpiseId;
			String ^ m_Title;
			String ^ m_Description;
			String ^ m_Path;
			eEnterpiseDBTypes m_Type;
			eLaunchTypes m_LaunchType;
			Int64 m_ProjectId;

			EnterpriseDatabase();
			~EnterpriseDatabase();

			void QueryFromDB();
			void WriteToDB();
		};
		

		public ref class PlatformManager
		{
			static Collections::Generic::List<EnterpriseVersionDescriptor^> ^ m_PlatformList;
		public:
			static void ScanInstalledPlatforms();
			static Collections::Generic::List<EnterpriseVersionDescriptor^> ^ GetPlatformList();
		};
		

		public ref class DBConnector
		{
			static SQLiteConnection^ m_DBConnection;
		public:
			SQLiteConnection ^ GetDBConnection()
			{
				return m_DBConnection;
			}

			void SetDBConnection(SQLiteConnection ^ conn)
			{
				m_DBConnection = conn;
			}
		};
}
