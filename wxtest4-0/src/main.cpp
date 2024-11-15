#include "main.h"
#include <wx/image.h>

bool MyApp::OnInit() {
	wxUILocale::UseDefault();
#ifdef WITH_MSYS2
	wxFileTranslationsLoader::AddCatalogLookupPathPrefix(wxT("/msys64/mingw64/share/locale"));
#endif
	wxFileTranslationsLoader::AddCatalogLookupPathPrefix(wxT("locale"));
	auto trans = new wxTranslations();
	wxTranslations::Set(trans);
	trans->AddStdCatalog();
	trans->AddCatalog(PROGRAM_NAME);
	wxImage::AddHandler(new wxPNGHandler);
	auto frm = new MyFrame();
	frm->Show();
	return true;

};
 
wxIMPLEMENT_APP(MyApp);
