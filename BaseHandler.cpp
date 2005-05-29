#include "StdAfx.h"
#include "IconHandler.h"

#define MOZ_MESSAGE_WINDOW L"FirefoxMessageWindow"

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

void CIconHandler::QueryRegistry(void)
{
	firefoxexe=NULL;
	firefoxdir=NULL;

	// Query the registry for the latest version of firefox and its exe.
	HKEY key,versionKey,main;
	if (ERROR_SUCCESS==RegOpenKeyEx(HKEY_LOCAL_MACHINE,L"SOFTWARE\\Mozilla\\Deer Park Alpha 1",0,KEY_READ,&key))
	{
		DWORD len = 255;
		wchar_t *version = (wchar_t*)malloc(len);
		if (ERROR_SUCCESS==RegQueryValueEx(key,L"CurrentVersion",NULL,NULL,(LPBYTE)version,&len))
		{
			if (ERROR_SUCCESS==RegOpenKeyEx(key,version,0,KEY_READ,&versionKey))
			{
				if (ERROR_SUCCESS==RegOpenKeyEx(versionKey,L"Main",0,KEY_READ,&main))
				{
					len=255;
					firefoxexe = (wchar_t*)malloc(len);
					RegQueryValueEx(main,L"PathToExe",NULL,NULL,(LPBYTE)firefoxexe,&len);
					len=255;
					firefoxdir = (wchar_t*)malloc(len);
					RegQueryValueEx(main,L"Install Directory",NULL,NULL,(LPBYTE)firefoxdir,&len);
					RegCloseKey(main);
				}
				RegCloseKey(versionKey);
			}
		}
		free(version);
		RegCloseKey(key);
	}
}
