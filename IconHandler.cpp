// IconHandler.cpp : Implementation of CIconHandler

#include "stdafx.h"
#include "IconHandler.h"


// CIconHandler

// Extracts the icon - delegates back to the calling application
STDMETHODIMP CIconHandler::Extract(LPCWSTR pszFile,
    UINT nIconIndex,
    HICON *phiconLarge,
    HICON *phiconSmall,
    UINT nIconSize)
{
	return S_FALSE;
}

// Gets the location of the icon
STDMETHODIMP CIconHandler::GetIconLocation(UINT uFlags,
    LPWSTR szIconFile,
    UINT cchMax,
    int *piIndex,
    UINT *pwFlags)
{
	USES_CONVERSION;

	wcsncpy(szIconFile,firefoxexe,cchMax);
	*piIndex=0;
	*pwFlags=0;
	return S_OK;
}
