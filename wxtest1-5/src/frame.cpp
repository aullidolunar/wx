#include "frame.h"
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/bmpbndl.h>
#ifndef __WXMSW__
#include "app.xpm"
#endif
#include "quit_16.xpm"

MyFrame::MyFrame(wxWindow* parent) 
	: wxFrame(parent, wxID_ANY, PROGRAM_NAME), next_row(0)
{
	SetIcon(wxICON(AppIcon));
	
	wxVector<wxBitmap> bitmaps;
	bitmaps.push_back(wxIcon(quit_16_xpm));
	
	auto frame_panel = new wxPanel(this, wxID_ANY);
	auto panel_sizer = new wxBoxSizer(wxVERTICAL);

	m_list = new wxListView(frame_panel);
	m_list->InsertColumn(0, _("Name"));
	m_list->InsertColumn(1, _("Info"));
	
	insert_item(_("unnamed"), _("undetermined")); // wxstd 
	insert_item(wxT("Joel"), _("Artists")); // wxstd
	insert_item(wxT("Arch"), _("System")); // gtk30.mo
	insert_item(wxT("Windows"), _("None")); // wxstd
	insert_item(wxT("iOS"), _("Nope")); // wxstd
		
	
	auto button = new wxButton(frame_panel, wxID_CLOSE);
	button->SetBitmap(wxBitmapBundle::FromBitmaps(bitmaps));

// binders:
	button->Bind(wxEVT_BUTTON, &MyFrame::on_button1_click, this);
	
// layout:
	panel_sizer->Add(m_list, 1, wxALL | wxEXPAND, FromDIP(10));
	panel_sizer->Add(button, 0, wxLEFT | wxBOTTOM, FromDIP(10));
	frame_panel->SetSizer(panel_sizer);
	panel_sizer->SetSizeHints(this);
}

void MyFrame::insert_item(const wxString& caption, const wxString& str)
{
	m_list->InsertItem(next_row, caption);
	m_list->SetItem(next_row, 1, str);
	next_row++;
}

void MyFrame::on_button1_click(wxCommandEvent& event)
{
	Close();
}