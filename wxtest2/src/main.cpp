#include <wx/uilocale.h>
#include <wx/app.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/bmpbndl.h>
#include <wx/statbmp.h>
#ifdef __WXMSW__
#include <wx/msgdlg.h>
#include <wx/msw/registry.h>
#include "windows-vista.xpm"
#else
#include <wx/utils.h>
#include "Regedit-Icon-32.xpm"
#include "tux-logo.xpm"
#endif

class MyFrame : public wxFrame
{
private:
	wxTextCtrl *m_tctrl_name;
	wxTextCtrl *m_tctrl_org;
#ifdef __WXMSW__
	wxRegKey *regedit;
#endif

public:
	MyFrame(wxWindow* parent = nullptr) :
		wxFrame(parent, wxID_ANY, PROGRAM_NAME, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
	{
		
		SetIcon(wxICON(AppIcon));
		auto frame_panel = new wxPanel(this, wxID_ANY);
		auto panel_sizer = new wxBoxSizer(wxVERTICAL);
		
		auto sz = new wxStaticBoxSizer(wxHORIZONTAL, frame_panel, wxT("Datos del usuario actual"));
		
		wxVector<wxBitmap> bitmaps;
		bitmaps.push_back(wxIcon(os_icon_xpm));
		auto logo_widget = new wxStaticBitmap(sz->GetStaticBox(), wxID_ANY, wxBitmapBundle::FromBitmaps(bitmaps));
		
		auto sz_child = new wxFlexGridSizer(2, 10, 10);
		sz_child->AddGrowableCol(1);
		
		auto label_name = new wxStaticText(sz->GetStaticBox(), wxID_ANY, _("Name"));
		m_tctrl_name = new wxTextCtrl(sz->GetStaticBox(), wxID_ANY);
		auto label_org = new wxStaticText(sz->GetStaticBox(), wxID_ANY, wxT("Organización"));
		m_tctrl_org = new wxTextCtrl(sz->GetStaticBox(), wxID_ANY);

// Regedit (only on __WXMSW__)
		wxString owner, org;
#ifdef __WXMSW__
		regedit = new wxRegKey(wxRegKey::HKLM, wxT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion"));
		regedit->QueryValue(wxT("RegisteredOwner"), owner);
		regedit->QueryValue(wxT("RegisteredOrganization"), org);
#else
// https://docs.wxwidgets.org/latest/group__group__funcmacro__networkuseros.html
		owner = wxGetUserName();
		org = wxGetHostName();
#endif
		*m_tctrl_name << owner;
		*m_tctrl_org << org;
		
		auto button_sizer = new wxBoxSizer(wxHORIZONTAL);
		auto button_save = new wxButton(frame_panel, wxID_SAVE);
#ifndef __WXMSW__
		button_save->Enable(false);
#endif
		auto button_exit = new wxButton(frame_panel, wxID_CLOSE);
		button_save->Bind(wxEVT_BUTTON, &MyFrame::on_button_save_click, this);
		button_exit->Bind(wxEVT_BUTTON, &MyFrame::on_button_exit_click, this);

// layout:
		sz->Add(logo_widget, 0, wxLEFT|wxALIGN_CENTER_VERTICAL, 10);
		sz_child->Add(label_name, 0, wxALIGN_CENTER_VERTICAL);
		sz_child->Add(m_tctrl_name, 1, wxEXPAND);
		sz_child->Add(label_org, 0, wxALIGN_CENTER_VERTICAL);
		sz_child->Add(m_tctrl_org, 1, wxEXPAND);
		sz->Add(sz_child, 1, wxALL|wxEXPAND, 10);
		panel_sizer->Add(sz, 0, wxALL|wxEXPAND, 10);
		button_sizer->AddStretchSpacer();
		button_sizer->Add(button_save, 0, wxRIGHT, 10);
		button_sizer->Add(button_exit);
		panel_sizer->Add(button_sizer, 0, wxEXPAND|wxBOTTOM|wxRIGHT, 10);
		frame_panel->SetSizerAndFit(panel_sizer);
		panel_sizer->SetSizeHints(this);
	}
	
	virtual ~MyFrame()
	{
#ifdef __WXMSW__
		regedit->Close();
		delete regedit;
#endif
	}

protected:
	void on_button_save_click(wxCommandEvent& event)
	{
#ifdef __WXMSW__
		int no_error = 0;
		if (regedit->SetValue(wxT("RegisteredOwner"), m_tctrl_name->GetValue()))
			no_error++;
		
		if (regedit->SetValue(wxT("RegisteredOrganization"), m_tctrl_org->GetValue()))
			no_error++;
		
		if (no_error)
			wxMessageBox(wxT("Las acciones fueron registradas con éxito."), PROGRAM_NAME, wxICON_INFORMATION);
#endif
	}
	
	void on_button_exit_click(wxCommandEvent& event)
	{
		Close();
	}
}; 

class MyApp : public wxApp
{
private:

public:
    bool OnInit() override
	{
		wxUILocale::UseDefault();
#ifdef WITH_MSYS2
		wxFileTranslationsLoader::AddCatalogLookupPathPrefix(wxT("/msys64/mingw64/share/locale"));
#endif
		wxTranslations* const trans = new wxTranslations();
        wxTranslations::Set(trans);
		trans->AddStdCatalog();
		auto frm = new MyFrame();
		frm->Show();
		return true;
	}
};
 
wxIMPLEMENT_APP(MyApp);
