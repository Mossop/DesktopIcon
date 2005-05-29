struct MENUSTATE
{
	wchar_t* Title;
	wchar_t* Help;
	BOOL Enabled;
	BOOL Visible;
};

struct MENUITEM
{
	wchar_t* Verb;
	wchar_t* Arguments;
	MENUSTATE ifLoaded;
	MENUSTATE ifNotLoaded;
};
