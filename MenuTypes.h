#pragma once

#include "stdafx.h"

struct MENUSTATE
{
	UINT Title; // The resource id of the context menu caption (relative to the locale id)
	UINT Help;  // The resource id of the status bar text for a menu item (relative to the locale id)
	BOOL Enabled; // Whether the menu item is enabled
	BOOL Visible; // Whether the menu item is disabled
};

struct MENUITEM
{
	LPTSTR Verb; // The verb this menu item applies to.
	LPTSTR Arguments; // The arguments to call firefox with.
	MENUSTATE ifNotLoaded; // The state of the menu when firefox is not running
	MENUSTATE ifLoaded; // The state of the menu when firefox is running
};
