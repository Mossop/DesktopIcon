
#include "stdafx.h"
#include "IconHandler.h"

// May need to get this from elsewhere for localisation
MENUITEM menus[4] = 
{
	{
		_T("open"),
		_T(""),
		{
			_T("&Browse the Internet"),
			_T("Browse the Internet with Mozilla Firefox"),
			TRUE,
			TRUE
		},
		{
			_T("Open a new window"),
			_T("Open a new Mozilla Firefox window"),
			TRUE,
			TRUE
		},
	},
	{
		_T("profiles"),
		_T(" -profilemanager"),
		{
			_T("&Profile Manager"),
			_T("Opens the Mozilla Firefox profile manager"),
			TRUE,
			TRUE
		},
		{
			_T("Profile Manager"),
			_T("Opens the Mozilla Firefox profile manager"),
			FALSE,
			TRUE
		},
	},
	{
		_T("safe"),
		_T(" -safe-mode"),
		{
			_T("&Safe Mode"),
			_T("Opens Mozilla Firefox in safe mode"),
			TRUE,
			TRUE
		},
		{
			_T("Safe Mode"),
			_T("Opens Mozilla Firefox in safe mode"),
			FALSE,
			TRUE
		},
	},
	{
		_T("properties"),
		_T(" -chrome chrome://browser/content/pref/pref.xul"),
		{
			_T("Mozilla Firefox &Options"),
			_T("Changes settings for Mozilla Firefox"),
			TRUE,
			TRUE
		},
		{
			_T("Mozilla Firefox &Options"),
			_T("Changes settings for Mozilla Firefox"),
			TRUE,
			TRUE
		},
	}
};

// Initializes the instance
STDMETHODIMP CIconHandler::Initialize(LPCITEMIDLIST pidlFolder,
		IDataObject* pdtobj,
		HKEY hkeyProgId)
{
	return NOERROR;
}

// Fill out the context menu
STDMETHODIMP CIconHandler::QueryContextMenu(HMENU hmenu, 
		UINT indexMenu,
		UINT idCmdFirst, 
		UINT idCmdLast, 
		UINT uflags)
{
	flog("QueryContextMenu\n");
	BOOL running;

	running=CheckLoadState();

	for (int i = 0; i<4; i++)
	{
		if ((i == 1) && (uflags & CMF_DEFAULTONLY))
			break;

		MENUSTATE* state;
		
		if (running)
			state = &menus[i].ifLoaded;
		else
			state = &menus[i].ifNotLoaded;

		MENUITEMINFO menu;
		menu.cbSize=sizeof(MENUITEMINFO);
		menu.fMask=MIIM_TYPE|MIIM_STATE|MIIM_ID;
		
		menu.fType=MFT_STRING;
		menu.dwTypeData=state->Title;
		menu.cch=(UINT)_tcslen(state->Title);
		
		menu.wID=idCmdFirst+i;
		
		menu.fState=0;
		if (i==0)
		{
			menu.fState|=MFS_DEFAULT;
		}
		if (state->Enabled)
		{
			menu.fState|=MFS_ENABLED;
		}
		else
		{
			menu.fState|=MFS_DISABLED;
		}

		InsertMenuItem(hmenu, indexMenu + i, TRUE, &menu);
	}

	return MAKE_HRESULT(SEVERITY_SUCCESS, 0, i);
}

// Execute a command from the context menu
STDMETHODIMP CIconHandler::InvokeCommand(LPCMINVOKECOMMANDINFO pici)
{
	flog("InvokeCommand\n");

	if (HIWORD(pici->lpVerb)==0)
	{
		UINT cmd = LOWORD(pici->lpVerb);
		ShellExecute(NULL,NULL,firefoxexe,menus[cmd].Arguments,firefoxdir,SW_SHOWNORMAL);
	}
	else
	{
		char text[255];
		sprintf(text,"Verb was string %s\n",pici->lpVerb);
		flog(text);
	}
	
	return S_OK;
}

// Get some information about a context menu entry
STDMETHODIMP CIconHandler::GetCommandString(UINT_PTR idCmd,
    UINT uFlags,
    UINT *pwReserved,
    LPSTR pszName,
    UINT cchMax)
{
	USES_CONVERSION;

	char text[255];
	sprintf(text,"GetCommandString  %i %i\n",idCmd,uFlags);
	flog(text);

	if ((idCmd < 0) || (idCmd >= 4))
  {
    return E_INVALIDARG;
  }

	TCHAR szText[255];

	if ((uFlags == GCS_HELPTEXTA) || (uFlags == GCS_HELPTEXTW))
	{
		BOOL running;
		running=CheckLoadState();
		if (running)
			LoadString(GetModuleHandle(NULL),menus[idCmd].ifLoaded.Help,szText,255);
		else
			LoadString(GetModuleHandle(NULL),menus[idCmd].ifNotLoaded.Help,szText,255);
	}
	else if ((uFlags == GCS_VERBA) || (uFlags == GCS_VERBW))
	{
		szText = menus[idCmd].Verb;
	}
	else
	{
		return E_INVALIDARG;
	}

	if (uFlags & GCS_UNICODE)
	{
		wcsncpy((LPWSTR)pszName, T2CW(szText), cchMax);
	}
	else
	{
		strncpy(pszName, T2CA(szText), cchMax);
	}
	
	return S_OK;
}
