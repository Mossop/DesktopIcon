
#include "stdafx.h"
#include "IconHandler.h"

// This needs to come out of the OS somewhere I guess. Or maybe the installed firefox version?
#define LOCALE 200

// May need to get this from elsewhere for localisation
MENUITEM menus[4] = 
{
	{
		_T("open"),
		_T(""),
		{
			0,
			1,
			TRUE,
			TRUE
		},
		{
			2,
			3,
			TRUE,
			TRUE
		},
	},
	{
		_T("profiles"),
		_T(" -profilemanager"),
		{
			4,
			5,
			TRUE,
			TRUE
		},
		{
			6,
			7,
			FALSE,
			TRUE
		},
	},
	{
		_T("safe"),
		_T(" -safe-mode"),
		{
			8,
			9,
			TRUE,
			TRUE
		},
		{
			10,
			11,
			FALSE,
			TRUE
		},
	},
	{
		_T("properties"),
		_T(" -chrome chrome://browser/content/pref/pref.xul"),
		{
			12,
			13,
			TRUE,
			TRUE
		},
		{
			14,
			15,
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

		TCHAR text[255];
		LoadString(_AtlBaseModule.GetModuleInstance(),LOCALE+state->Title,text,255);
		menu.dwTypeData=text;
		menu.cch=(UINT)_tcslen(text);
		
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

	LPTSTR szText;

	if ((uFlags == GCS_HELPTEXTA) || (uFlags == GCS_HELPTEXTW))
	{
		TCHAR text[255];
		BOOL running;
		running=CheckLoadState();
		if (running)
			LoadString(_AtlBaseModule.GetModuleInstance(),LOCALE+menus[idCmd].ifLoaded.Help,text,255);
		else
			LoadString(_AtlBaseModule.GetModuleInstance(),LOCALE+menus[idCmd].ifNotLoaded.Help,text,255);
		szText=text;
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
