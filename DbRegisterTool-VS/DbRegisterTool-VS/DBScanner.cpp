#include "DBScanner.h"

using namespace System::Collections::Generic;


void DBScanner::ScanPath( String ^ path,DBScanRecordsList ^ list )
{
	String ^ fileName = System::IO::Path::GetFileName(path);
	String ^ dirName = System::IO::Path::GetDirectoryName(path);
	String ^ extension = System::IO::Path::GetExtension(path);

	if (!System::IO::Directory::Exists(path))
	{
		AddBaseFromFile(path,list);
	}
	else
	{
		ScanDirectory(path,list,true);
	}
}

void DBScanner::AddBaseFromFile( String ^ path,DBScanRecordsList ^list  )
{
	String ^ extension = System::IO::Path::GetExtension(path);

	if (extension == ".dt")
	{
		DBScanRecord ^ r = gcnew DBScanRecord();
		r->m_eType = DBT_DT;
		r->m_strPath = path;
		list->Add(r);
		return;
	}
	else if (extension == ".1cd")
	{
		DBScanRecord ^ r = gcnew DBScanRecord();
		r->m_eType = DBT_1CD;
		r->m_strPath = path;
		list->Add(r);
	}
}

void DBScanner::ScanDirectory( String ^ path,DBScanRecordsList ^ l,bool bRecursive )
{
	IEnumerable<String^> ^ files = System::IO::Directory::EnumerateFiles(path);

	for each(String ^ file in files)
	{
		AddBaseFromFile(file,l);
	}

	if (bRecursive)
	{
		IEnumerable<String^> ^ subdirs = System::IO::Directory::EnumerateDirectories(path);

		for each(String ^ subdir in subdirs)
		{
			ScanDirectory(subdir,l,bRecursive);
		}
	}
}
