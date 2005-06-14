// IconHandler.cpp : Implementation of CIconHandler

#include "stdafx.h"
#include "IconHandler.h"

// Define both unicode and ascii equivalents of this interface for Win9x and WinNT

// IExtractIconW

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

	flog("IExtractIconW\n");

	wcsncpy(szIconFile,T2W(firefoxexe),cchMax);
	*piIndex=0;
	*pwFlags=0;
	return S_OK;
}

// IExtractIconA

// Extracts the icon - delegates back to the calling application
STDMETHODIMP CIconHandler::Extract(LPCSTR pszFile,
    UINT nIconIndex,
    HICON *phiconLarge,
    HICON *phiconSmall,
    UINT nIconSize)
{
	return S_FALSE;
}

// Gets the location of the icon
STDMETHODIMP CIconHandler::GetIconLocation(UINT uFlags,
    LPSTR szIconFile,
    UINT cchMax,
    int *piIndex,
    UINT *pwFlags)
{
	USES_CONVERSION;

	flog("IExtractIconA\n");

	strncpy(szIconFile,T2A(firefoxexe),cchMax);
	*piIndex=0;
	*pwFlags=0;
	return S_OK;
}
