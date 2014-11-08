#pragma once

using  namespace System;

enum eDataBaseTypes
{
	DBT_1CD = (1<<0),
	DBT_DT = (1<<1),
	DBT_PACKED_ZIP = (1<<2)
};

public ref class DBScanRecord
{
public:
	eDataBaseTypes m_eType;
	String ^ m_strPath;
	String ^ m_strName;

	DBScanRecord()
	{
		m_strPath = m_strName = "";
	}

	virtual String ^ ToString() override
	{
		return m_strPath;
	}
};

typedef Collections::Generic::List<DBScanRecord^> DBScanRecordsList;

class DBScanner
{
	static void ScanDirectory(String ^ path,DBScanRecordsList ^ l,bool bRecursive);
	static void AddBaseFromFile(String ^ filePath,DBScanRecordsList ^ l);
public:
	static void ScanPath(String ^ path,DBScanRecordsList ^ list);	
};

