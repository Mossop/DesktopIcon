
#include "stdafx.h"
#include "IconHandler.h"

// Initializes the instance
STDMETHODIMP CIconHandler::Initialize(LPCITEMIDLIST pidlFolder,
		IDataObject* pdtobj,
		HKEY hkeyProgId)
{
	flog("Initialize Menus\n");

	// For the moment lets just hardcode the entries
	menus = new MENUITEM[4];
	menus = (MENUITEM*)malloc(sizeof(MENUITEM)*4);

	menus[0].ifNotLoaded.Title=L"&Browse the Internet";
	menus[0].ifNotLoaded.Help=L"Browse the Internet with Mozilla Firefox";
	menus[0].ifNotLoaded.Enabled=TRUE;
	menus[0].ifNotLoaded.Visible=TRUE;
	menus[0].ifLoaded.Title=L"Open a new window";
	menus[0].ifLoaded.Help=L"Open a new Mozilla Firefox window";
	menus[0].ifLoaded.Enabled=TRUE;
	menus[0].ifLoaded.Visible=TRUE;
	menus[0].Verb=L"open";
	menus[0].Arguments=L"";

	menus[1].ifNotLoaded.Title=L"&Profile Manager";
	menus[1].ifNotLoaded.Help=L"Opens the Mozilla Firefox profile manager";
	menus[1].ifNotLoaded.Enabled=TRUE;
	menus[1].ifNotLoaded.Visible=TRUE;
	menus[1].ifLoaded.Title=L"Profile Manager";
	menus[1].ifLoaded.Help=L"Opens the Mozilla Firefox profile manager";
	menus[1].ifLoaded.Enabled=FALSE;
	menus[1].ifLoaded.Visible=TRUE;
	menus[1].Verb=L"profilemanager";
	menus[1].Arguments=L" -profilemanager";

	menus[2].ifNotLoaded.Title=L"&Safe Mode";
	menus[2].ifNotLoaded.Help=L"Opens Mozilla Firefox in safe mode";
	menus[2].ifNotLoaded.Enabled=TRUE;
	menus[2].ifNotLoaded.Visible=TRUE;
	menus[2].ifLoaded.Title=L"Safe Mode";
	menus[2].ifLoaded.Help=L"Opens Mozilla Firefox in safe mode";
	menus[2].ifLoaded.Enabled=FALSE;
	menus[2].ifLoaded.Visible=TRUE;
	menus[2].Verb=L"safemode";
	menus[2].Arguments=L" -safe-mode";

	menus[3].ifNotLoaded.Title=L"Mozilla Firefox &Options";
	menus[3].ifNotLoaded.Help=L"Changes settings for Mozilla Firefox";
	menus[3].ifNotLoaded.Enabled=TRUE;
	menus[3].ifNotLoaded.Visible=TRUE;
	menus[3].ifLoaded.Title=L"Mozilla Firefox &Options";
	menus[3].ifLoaded.Help=L"Changes settings for Mozilla Firefox";
	menus[3].ifLoaded.Enabled=TRUE;
	menus[3].ifLoaded.Visible=TRUE;
	menus[3].Verb=L"properties";
	menus[3].Arguments=L" -chrome chrome://browser/content/pref/pref.xul";

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
		menu.cch=(UINT)wcslen(state->Title);
		
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

	if ((idCmd < 0) || (idCmd > 4))
  {
    return E_INVALIDARG;
  }

	LPCTSTR szText;

	if ((uFlags == GCS_HELPTEXTA) || (uFlags == GCS_HELPTEXTW))
	{
		BOOL running;
		running=CheckLoadState();
		if (running)
			szText = menus[idCmd].ifLoaded.Help;
		else
			szText = menus[idCmd].ifNotLoaded.Help;
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
		strncpy(pszName, W2CA(szText), cchMax);
	}
	
	return S_OK;
}
