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
  wxString outstr(_(PROGRAM_DESC));
#if __WXMSW__
  WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), outstr.wc_str(), outstr.size(), nullptr, nullptr);
#else
  std::cout << outstr;
#endif
	frm->Show();
	return true;

};
 
wxIMPLEMENT_APP(MyApp);
