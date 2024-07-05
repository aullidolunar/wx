#include "frame.h"

class MyApp : public wxApp
{
private:
// https://www.wxwidgets.org/about/translations/
	wxLocale m_locale;
public:
    bool OnInit() override
	{
		wxLocale::AddCatalogLookupPathPrefix (PROGRAM_LOCALEDIR);
		m_locale.Init();
		m_locale.AddCatalog (PROGRAM_CATALOG);
		auto frm = new MyFrame(&m_locale);
		frm->Show();
		return true;
	}
};
 
wxIMPLEMENT_APP(MyApp);
