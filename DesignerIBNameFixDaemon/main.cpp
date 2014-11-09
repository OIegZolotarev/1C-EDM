#include <windows.h>
#include <winternl.h>
#include <shlwapi.h>

#pragma comment(lib,"ntdll.lib")

PWSTR ReadCmdLine(HANDLE hProcess)
{
	
	PROCESS_BASIC_INFORMATION inf;

	PVOID pinfo = &inf;

	LONG status = NtQueryInformationProcess(hProcess,(PROCESSINFOCLASS)0,pinfo,sizeof(PVOID)*6,NULL);
	PPEB ppeb = (PPEB)((PVOID*)pinfo)[1];
	PPEB ppebCopy = (PPEB)malloc(sizeof(PEB));
	
	BOOL result = ReadProcessMemory(hProcess,ppeb,ppebCopy,sizeof(PEB),NULL);

	PRTL_USER_PROCESS_PARAMETERS pRtlProcParam = ppebCopy->ProcessParameters;
	PRTL_USER_PROCESS_PARAMETERS pRtlProcParamCopy = (PRTL_USER_PROCESS_PARAMETERS)malloc(sizeof(RTL_USER_PROCESS_PARAMETERS));
	result = ReadProcessMemory(hProcess,pRtlProcParam,pRtlProcParamCopy,sizeof(RTL_USER_PROCESS_PARAMETERS),NULL);
	
	PWSTR wBuffer = pRtlProcParamCopy->CommandLine.Buffer;
	USHORT len =  pRtlProcParamCopy->CommandLine.Length;
	PWSTR wBufferCopy = (PWSTR)malloc(len);
	
	result = ReadProcessMemory(hProcess,wBuffer,wBufferCopy,len,NULL);

	return wBufferCopy;
}

BOOL CALLBACK EnumWindowsProc(_In_  HWND hwnd,_In_  LPARAM lParam)
{
	TCHAR textBuffer[1024];
	GetWindowText(hwnd,textBuffer,1024);

	if (wcsstr(textBuffer,L"Конфигуратор") && *textBuffer != (L'['))
	{

		DWORD pid;
		GetWindowThreadProcessId(hwnd,&pid);
		HANDLE proc = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid);

		PWSTR cmd = ReadCmdLine(proc);
		
		TCHAR * baseNamePtr = wcsstr(cmd,L"/IBName\"");
		baseNamePtr+=8;

		TCHAR * ptr = baseNamePtr;

		while(*ptr != L'\"')
		{
			ptr++;
		}

		*ptr = 0;

		TCHAR windowTitle[1024];

		wsprintf(windowTitle,L"[%s] - %s",baseNamePtr,textBuffer);
		SetWindowText(hwnd,windowTitle);


		free(cmd);
	}

	return true;
}

int __stdcall WinMain( __in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd )
{
	while(true)
	{

		EnumWindows(EnumWindowsProc,0);
		Sleep(1000);
	}

	return 0;
}