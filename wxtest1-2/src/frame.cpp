#include "frame.h"

MyFrame::MyFrame(wxWindow* parent) 
	: wxFrame(parent, wxID_ANY, PROGRAM_NAME)
{
	auto panel_frame = new wxPanel(this, wxID_ANY);
	auto vbox = new wxBoxSizer(wxVERTICAL);
	auto panel_inner = new wxPanel(panel_frame, wxID_ANY);
	panel_inner->SetBackgroundColour(wxColour("white"));
	
// layout:
	vbox->Add(panel_inner, 1, wxEXPAND | wxALL, 10);
	panel_frame->SetSizer(vbox);
} 

void MyFrame::on_button1_click(wxCommandEvent& event)
{
	Close();
}