// IconHandler.h : Declaration of the CIconHandler

#pragma once
#include "resource.h"       // main symbols

#include "DesktopIcon.h"
#include "MenuTypes.h"

// CIconHandler

class ATL_NO_VTABLE CIconHandler : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIconHandler, &CLSID_IconHandler>,
	public IShellFolder,
	public IDropTarget,
	public IExtractIcon,
	public IContextMenu,
	public IShellExtInit,
	public IQueryInfo,
	public IDispatchImpl<IIconHandler, &IID_IIconHandler, &LIBID_DesktopIconLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CIconHandler()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ICONHANDLER)

DECLARE_NOT_AGGREGATABLE(CIconHandler)

BEGIN_COM_MAP(CIconHandler)
	COM_INTERFACE_ENTRY(IIconHandler)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellFolder)
	COM_INTERFACE_ENTRY(IDropTarget)
	COM_INTERFACE_ENTRY(IExtractIcon)
	COM_INTERFACE_ENTRY(IContextMenu)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IQueryInfo)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		firefoxexe=NULL;
		firefoxdir=NULL;
		QueryRegistry();
		return S_OK;
	}
	
	void FinalRelease() 
	{
		if (firefoxexe!=NULL)
			free(firefoxexe);
		if (firefoxdir!=NULL)
			free(firefoxdir);
	}

private:

	wchar_t *firefoxexe;
	wchar_t *firefoxdir;

	MENUITEM *menus;

	void flog(char *text);
	BOOL CheckLoadState(void);
	void QueryRegistry(void);

public:

	// IShellExtInit
	STDMETHOD(Initialize)(LPCITEMIDLIST pidlFolder, IDataObject*, HKEY);

	// IContextMenu
	STDMETHOD(GetCommandString)(UINT_PTR, UINT, UINT*, LPSTR, UINT);
	STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO);
	STDMETHOD(QueryContextMenu)(HMENU, UINT, UINT, UINT, UINT);

	// IExtractIcon
  STDMETHOD(Extract)(LPCWSTR, UINT, HICON*, HICON*, UINT);
  STDMETHOD(GetIconLocation)(UINT, LPWSTR, UINT, int*, UINT*);

	// IQueryInfo
  STDMETHOD(GetInfoFlags)(DWORD*)																										{ return E_NOTIMPL; }
  STDMETHOD(GetInfoTip)(DWORD, LPWSTR*);

	// IDropTarget
	STDMETHOD(DragEnter)(IDataObject*, DWORD, POINTL, DWORD*);
	STDMETHOD(DragOver)(DWORD, POINTL, DWORD*);
	STDMETHOD(DragLeave)(void);
	STDMETHOD(Drop)(IDataObject*, DWORD, POINTL, DWORD*);

	// IShellFolder
	STDMETHOD(BindToObject)(LPCITEMIDLIST, LPBC, REFIID, VOID**)											{ return E_NOTIMPL; };
	STDMETHOD(BindToStorage)(LPCITEMIDLIST, LPBC, REFIID, VOID**)											{ return E_NOTIMPL; };
	STDMETHOD(CompareIDs)(LPARAM, LPCITEMIDLIST, LPCITEMIDLIST)												{ return E_NOTIMPL; };
	STDMETHOD(EnumObjects)(HWND, SHCONTF, IEnumIDList**)															{ return E_NOTIMPL; };
	STDMETHOD(GetAttributesOf)(UINT, LPCITEMIDLIST*, SFGAOF*)													{ return E_NOTIMPL; };
	STDMETHOD(GetDisplayNameOf)(LPCITEMIDLIST, DWORD, LPSTRRET)												{ return E_NOTIMPL; };
	STDMETHOD(GetUIObjectOf)(HWND, UINT, LPCITEMIDLIST*, REFIID, UINT*, VOID**)				{ return E_NOTIMPL; };
	STDMETHOD(ParseDisplayName)(HWND, LPBC, LPOLESTR, ULONG*, LPITEMIDLIST*, ULONG*)	{ return E_NOTIMPL; };
	STDMETHOD(SetNameOf)(HWND, LPCITEMIDLIST, LPCOLESTR, DWORD, LPITEMIDLIST*)				{ return E_NOTIMPL; };
	STDMETHOD(CreateViewObject)(HWND, REFIID, VOID**);

};

OBJECT_ENTRY_AUTO(__uuidof(IconHandler), CIconHandler)
