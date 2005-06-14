
#include "stdafx.h"
#include "IconHandler.h"

STDMETHODIMP CIconHandler::CreateViewObject(HWND hwndOwner,
 REFIID iid,
 VOID **ppvOut)
{
	flog("CreateViewObject\n");
	if (iid==IID_IDropTarget)
	{
		return QueryInterface(iid,ppvOut);
	}
	else
	{
		char text[255];
		sprintf(text,"CreateViewObject - {%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}\n",
								iid.Data1,
								iid.Data2,
								iid.Data3,
								iid.Data4[0], iid.Data4[1], iid.Data4[2], iid.Data4[3],
								iid.Data4[4], iid.Data4[5], iid.Data4[6], iid.Data4[7]);
		flog(text);
		return E_NOTIMPL;
	}
}
