#include "stdafx.h"
#include "IconHandler.h"

// Doesnt appear to work currently.

STDMETHODIMP CIconHandler::GetInfoTip(
    DWORD   dwFlags,
    LPWSTR* ppwszTip)
{
	flog("GetInfoTip\n");

	USES_CONVERSION;

	LPMALLOC pMalloc;

	if (FAILED(SHGetMalloc(&pMalloc)))
		return E_FAIL;

	LPTSTR tooltip = _T("Mozilla Firefox Tooltip");
	
	*ppwszTip = (LPWSTR)pMalloc->Alloc((1+_tcslen(tooltip))*sizeof(WCHAR));

	if ( NULL == *ppwszTip )
  {
    pMalloc->Release();
    return E_OUTOFMEMORY;
  }

  // Use the Unicode string copy function to put the tooltip text in the buffer.
  wcscpy(*ppwszTip,T2W(tooltip));

  pMalloc->Release();
  return S_OK;
}
