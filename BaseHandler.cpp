#include "StdAfx.h"
#include "IconHandler.h"

#define MOZ_MESSAGE_WINDOW _T("FirefoxMessageWindow")

void CIconHandler::flog(char* text)
{
	FILE* file = fopen("C:\\shlex.log","a");
	fprintf(file,text);
	fclose(file);
}

// Check whether firefox is already running
BOOL CIconHandler::CheckLoadState()
{
	if (FindWindow(MOZ_MESSAGE_WINDOW,NULL)!=NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
	return S_OK;
}

void CIconHandler::FindFirefox(void)
{
	USES_CONVERSION;

	if (firefoxdir!=NULL)
	{
		delete [] firefoxdir;
		firefoxdir=NULL;
	}
	if (firefoxdir!=NULL)
	{
		delete [] firefoxexe;
		firefoxexe=NULL;
	}

  HMODULE hInstance = _AtlBaseModule.GetModuleInstance();

  if (hInstance==0)
  {
    return;
  }

  TCHAR szModule[MAX_PATH];
  DWORD dwFLen = ::GetModuleFileName(hInstance, szModule, MAX_PATH);

  if (dwFLen == 0)
  {
    return;
  }

	TCHAR szPath[MAX_PATH];
  TCHAR *pszFileName;
  dwFLen = ::GetFullPathName(szModule, MAX_PATH, szPath, &pszFileName);
  if (dwFLen == 0 || dwFLen >= MAX_PATH)
  {
    return;
  }
  *pszFileName = 0;

	firefoxdir = new TCHAR[dwFLen+1];
	_tcsncpy(firefoxdir,szPath,dwFLen);
	firefoxexe = new TCHAR[dwFLen+1+11];
	_tcscpy(firefoxexe,firefoxdir);
	_tcscat(firefoxexe,_T("firefox.exe"));
	flog(T2A(firefoxexe));
	flog("\n");
}
