
#include "stdafx.h"
#include "IconHandler.h"

STDMETHODIMP CIconHandler::DragEnter(IDataObject* pDataObject,
  DWORD grfKeyState,
  POINTL pt,
  DWORD* pdwEffect)
{
	flog("DragEnter\n");
	*pdwEffect=DROPEFFECT_NONE;

	FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stg = { TYMED_HGLOBAL };
	HDROP     hDrop;

	if ( FAILED(pDataObject->GetData(&fmt,&stg)))
	{
		return S_OK;
	}

	hDrop = (HDROP)GlobalLock(stg.hGlobal);

	if (hDrop==NULL)
	{
		return S_OK;
	}

	UINT numFiles = DragQueryFile ( hDrop, 0xFFFFFFFF, NULL, 0 );

  if (numFiles>0)
  {
		*pdwEffect=DROPEFFECT_COPY;
  }

  GlobalUnlock(stg.hGlobal);
  ReleaseStgMedium(&stg);

	return S_OK;
}

STDMETHODIMP CIconHandler::DragOver(DWORD grfKeyState,
  POINTL pt,
  DWORD* pdwEffect)
{
	*pdwEffect=DROPEFFECT_COPY;
	return S_OK;
}

STDMETHODIMP CIconHandler::DragLeave(void)
{
	return S_OK;
}

STDMETHODIMP CIconHandler::Drop(IDataObject* pDataObject,
  DWORD grfKeyState,
  POINTL pt,
  DWORD* pdwEffect)
{
	flog("Drop\n");
	FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stg = { TYMED_HGLOBAL };
	HDROP     hDrop;

	if ( FAILED(pDataObject->GetData(&fmt,&stg)))
	{
		return E_INVALIDARG;
	}

	hDrop = (HDROP)GlobalLock(stg.hGlobal);

	if (hDrop==NULL)
	{
		return E_INVALIDARG;
	}

	UINT numFiles = DragQueryFile ( hDrop, 0xFFFFFFFF, NULL, 0 );

  if (numFiles==0)
  {
		GlobalUnlock(stg.hGlobal);
		ReleaseStgMedium(&stg);
		return E_INVALIDARG;
  }

	LPTSTR start = _T("-url \"");
	LPTSTR end = _T("\"");
	size_t extra = _tcslen(start)+_tcslen(end);

	for (UINT i = 0; i<numFiles; i++)
	{
		UINT count = DragQueryFile(hDrop,i,NULL,0);
		if (count!=0)
		{
			LPTSTR file = new TCHAR[count+2];
			DragQueryFile(hDrop,i,file,count+1);
			LPTSTR arg = new TCHAR[count+extra+1];
			_tcscpy(arg,start);
			_tcscat(arg,file);
			_tcscat(arg,end);
			ShellExecute(NULL,NULL,firefoxexe,arg,firefoxdir,SW_SHOWNORMAL);
			delete [] arg;
			delete [] file;
		}
	}

  GlobalUnlock(stg.hGlobal);
  ReleaseStgMedium(&stg);

	*pdwEffect=DROPEFFECT_COPY;
	return S_OK;
}
