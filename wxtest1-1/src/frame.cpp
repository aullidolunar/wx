#include "frame.h"

MyFrame::MyFrame(wxWindow* parent)
{
	wxXmlResource::Get()->LoadFrame(this, parent, "MyFrame1");
	Bind(wxEVT_BUTTON, &MyFrame::on_button1_click, this, XRCID("m_button1"));
} 

void MyFrame::on_button1_click(wxCommandEvent& event)
{
	Close();
}