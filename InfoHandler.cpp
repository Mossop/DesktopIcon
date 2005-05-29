#include "stdafx.h"
#include "IconHandler.h"

STDMETHODIMP CIconHandler::GetInfoTip(
    DWORD   dwFlags,
    LPWSTR* ppwszTip)
{
	USES_CONVERSION;

	flog("GetInfoTip\n");

	LPMALLOC pMalloc;

	if (FAILED(SHGetMalloc(&pMalloc)))
		return E_FAIL;

	wchar_t *tooltip = L"Mozilla Firefox Tooltip";
	
	*ppwszTip = (LPWSTR)pMalloc->Alloc((1+wcslen(tooltip))*sizeof(wchar_t));

	if ( NULL == *ppwszTip )
  {
    pMalloc->Release();
    return E_OUTOFMEMORY;
  }

  // Use the Unicode string copy function to put the tooltip text in the buffer.
  wcscpy(*ppwszTip,tooltip);

  pMalloc->Release();
  return S_OK;
}
