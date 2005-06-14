#pragma once

#include "stdafx.h"

struct MENUSTATE
{
	LPTSTR Title;
	LPTSTR Help;
	BOOL Enabled;
	BOOL Visible;
};

struct MENUITEM
{
	LPTSTR Verb;
	LPTSTR Arguments;
	MENUSTATE ifNotLoaded;
	MENUSTATE ifLoaded;
};
