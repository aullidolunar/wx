#include "MyFrame.h"
#include <wx/panel.h>
#include <wx/gbsizer.h>
#include <wx/statbmp.h>
#include <wx/filename.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/msgdlg.h>
#include <wx/aboutdlg.h>
#include "ok_22.h"
#include "close_24.h"
#include "platform.h"

MyFrame::MyFrame(wxWindow* parent) : wxFrame(parent, wxID_ANY, PROGRAM_NAME) {
  wxBitmap platform_image = wxBITMAP_PNG_FROM_DATA(platform);
  wxIcon win_icon;
#ifdef __WXMSW__
  win_icon.LoadFile("IDI_ICON1", wxBITMAP_TYPE_ICO_RESOURCE);
#else
  win_icon.CopyFromBitmap(platform_image);
#endif
  SetIcon(win_icon);
	auto panel = new wxPanel(this, wxID_ANY);
  auto sizer = new wxGridBagSizer(10, 10);

  auto platform = new wxStaticBitmap(panel, wxID_ANY, wxBitmapBundle::FromBitmap(platform_image));
  platform->SetToolTip(_("Your platform icon"));
  
  auto label1 = new wxStaticText(panel, wxID_ANY, _("Type something nice:"));
  
  m_entry1.Create(panel, wxID_ANY);
  
  m_check1.Create(panel, wxID_ANY, _("Show wxAboutDialog"));
  
  auto button1 = new wxButton(panel, wxID_OK);
  button1->SetToolTip(_("Show a dialog with information"));
  button1->SetBitmap(wxBITMAP_PNG_FROM_DATA(ok_22));
  
  auto button2 = new wxButton(panel, wxID_CLOSE);
  button2->SetToolTip(_("Exit the application"));
  button2->SetBitmap(wxBITMAP_PNG_FROM_DATA(close));
  
  button1->Bind(wxEVT_BUTTON, [this, win_icon](wxCommandEvent&){
    if (m_check1.IsChecked()) {
      wxAboutDialogInfo aboutInfo;
      aboutInfo.SetName(PROGRAM_NAME);
      aboutInfo.SetVersion(PROGRAM_VERSION);
      aboutInfo.SetDescription(_(PROGRAM_DESC));
      aboutInfo.SetCopyright("(C) 2024");
      aboutInfo.AddDeveloper("aulidolunar");
      aboutInfo.SetIcon(win_icon);
      wxAboutBox(aboutInfo, this);
    } else {
      wxString message = m_entry1.GetValue();
      wxMessageDialog msgdlg(this, _("This is your message"));
      msgdlg.SetExtendedMessage(message);
      msgdlg.ShowModal();
   }
  });
  
  button2->Bind(wxEVT_BUTTON, [this](wxCommandEvent&){
    Close();
  });
  
  m_check1.Bind(wxEVT_CHECKBOX, [this](wxCommandEvent& event){
    m_entry1.Enable(!event.IsChecked());
  });
  
  // row, col
  sizer->Add(platform, wxGBPosition(0, 0), wxGBSpan(2, 1), wxLEFT|wxTOP|wxALIGN_CENTRE_VERTICAL, 10);
  sizer->Add(label1, wxGBPosition(0, 1), wxDefaultSpan, wxTOP|wxALIGN_CENTRE_VERTICAL, 10);
  sizer->Add(&m_entry1, wxGBPosition(0, 2), wxDefaultSpan, wxEXPAND|wxTOP|wxALIGN_CENTRE_VERTICAL, 10);
  sizer->Add(button1, wxGBPosition(0, 3), wxDefaultSpan, wxTOP|wxALIGN_CENTRE_VERTICAL, 10);
  sizer->Add(button2, wxGBPosition(0, 4), wxDefaultSpan, wxTOP|wxRIGHT|wxALIGN_CENTRE_VERTICAL, 10);
  sizer->Add(&m_check1, wxGBPosition(1, 1), wxGBSpan(1, 2), wxBOTTOM|wxRIGHT|wxALIGN_CENTRE_VERTICAL, 10);
  panel->SetSizer(sizer);
  sizer->AddGrowableCol(2);
  sizer->SetSizeHints(this);
}

MyFrame::~MyFrame() {
	//
}
