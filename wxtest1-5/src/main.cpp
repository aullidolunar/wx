#include <wx/app.h>
#include <wx/uilocale.h>
#include "frame.h"

class MyApp : public wxApp
{
private:
// https://www.wxwidgets.org/about/translations/
public:
    bool OnInit() override
	{
		wxUILocale::UseDefault();
#ifdef USE_PROGRAM_CATALOG
		wxFileTranslationsLoader::AddCatalogLookupPathPrefix(PROGRAM_LOCALEDIR);
#endif
#ifdef WITH_MSYS2
		wxFileTranslationsLoader::AddCatalogLookupPathPrefix("/msys64/mingw64/share/locale");
#endif
		wxTranslations* const trans = new wxTranslations();
        wxTranslations::Set(trans);
// https://raw.githubusercontent.com/wxWidgets/wxWidgets/master/locale/es.po
		trans->AddStdCatalog();
// https://github.com/linuxmint/gtk/blob/master/po/es.po
        trans->AddCatalog(PROGRAM_CATALOG);
		auto frm = new MyFrame();
		frm->Show();
		return true;
	}
};
 
wxIMPLEMENT_APP(MyApp);
