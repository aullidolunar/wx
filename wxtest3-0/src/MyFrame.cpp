#include "MyFrame.h"
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/msgdlg.h>
#include <wx/aboutdlg.h>
#include "MesonHelper.h"

MyFrame::MyFrame(wxWindow* parent) {
	
	wxXmlResource::Get()->LoadFrame(this, parent, "MyFrame1");
	wxIcon icon;
#ifdef __WXMSW__
	icon.LoadFile("IDI_ICON1", wxBITMAP_TYPE_ICO_RESOURCE);
#else
	icon.LoadFile(PROGRAM_DATADIR "/qt_main.ico", wxBITMAP_TYPE_ICO);
#endif
	SetIcon(icon);
	SetTitle(PROGRAM_TITLE);
	
	auto buttonOK = XRCCTRL(*this, "buttonOK", wxButton);
	auto textCtrl1 = XRCCTRL(*this, "m_textCtrl1", wxTextCtrl);
	auto check1 = XRCCTRL(*this, "m_checkBox1", wxCheckBox);
	
	check1->Bind(wxEVT_CHECKBOX, [textCtrl1](wxCommandEvent& event){
		textCtrl1->Enable(!event.IsChecked());
	});
	
	buttonOK->Bind(wxEVT_BUTTON, [check1, textCtrl1, this](wxCommandEvent& WXUNUSED(event)){
		bool checked = check1->IsChecked();
		if (checked) {
			showAboutDlg();
		} else {
			wxString message = textCtrl1->GetValue();
			wxMessageBox(message, _("This your message"), wxOK|wxCENTRE, this);
		}
	});
	
	
}

void MyFrame::showAboutDlg() {
  wxAboutDialogInfo aboutInfo;
  
  aboutInfo.SetName(PROGRAM_NAME);
  aboutInfo.SetVersion(PROGRAM_VERSION);
  aboutInfo.SetDescription(PROGRAM_DESC);
  aboutInfo.SetCopyright("(C) 2024");
  aboutInfo.AddDeveloper("aullidolunar");
  
  wxAboutBox(aboutInfo, this);
}

MyFrame::~MyFrame() {
	//
}
