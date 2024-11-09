#include <wx/uilocale.h>
#include <wx/app.h>
#include <wx/image.h>
#include "MyFrame.h"

class MyApp : public wxApp {
public:
  bool OnInit() override {
    wxUILocale::UseDefault();
#ifdef WITH_MSYS2
	  wxFileTranslationsLoader::AddCatalogLookupPathPrefix(PROGRAM_PREFIX "/share/locale");
#endif
    wxFileTranslationsLoader::AddCatalogLookupPathPrefix(wxT("locale"));
    auto trans = new wxTranslations();
    wxTranslations::Set(trans);
    trans->AddStdCatalog();
    trans->AddCatalog(PROGRAM_NAME);
    wxImage::AddHandler(new wxPNGHandler);
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load(XRC_FILE);
    auto frm = new MyFrame();
    frm->Show();
    return true;
  }
};
 
wxIMPLEMENT_APP(MyApp);
