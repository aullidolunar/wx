#ifndef _FRAME_H_INCLUDED_
#define _FRAME_H_INCLUDED_

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/sizer.h>

class MyFrame : public wxFrame
{
private:
	void on_button1_click(wxCommandEvent& event);
	 
public:
	MyFrame(wxWindow* parent = nullptr);
}; 

#endif
