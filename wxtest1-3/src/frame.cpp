#include "frame.h"
#ifndef __WXMSW__
#include "app.xpm"
#endif

MyFrame::MyFrame(wxLocale* loc, wxWindow* parent) 
	: wxFrame(parent, wxID_ANY, PROGRAM_NAME), next_row(0)
{
	SetIcon(wxICON(AppIcon));
	auto frame_panel = new wxPanel(this, wxID_ANY);
	auto panel_sizer = new wxBoxSizer(wxVERTICAL);
	m_list = new wxListView(frame_panel);
	m_list->InsertColumn(0, _("unnamed"));
	m_list->InsertColumn(1, _("value"));
	
	insert_item("GetCanonicalName", loc->GetCanonicalName());
	insert_item("GetSysName", loc->GetSysName());
	insert_item("GetLocale", loc->GetLocale());
	insert_item("GetName", loc->GetName());
	insert_item("GetLanguageName", wxLocale::GetLanguageName(loc->GetLanguage()));
		
	
	auto button = new wxButton(frame_panel, wxID_CLOSE);

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