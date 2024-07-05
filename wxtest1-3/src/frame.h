#ifndef _FRAME_H_INCLUDED_
#define _FRAME_H_INCLUDED_

#include <wx/app.h>
#include <wx/frame.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/intl.h>

class MyFrame : public wxFrame
{
private:
		wxListCtrl* m_list;
		int next_row;
public:
	MyFrame(wxLocale* loc, wxWindow* parent = nullptr);

protected:
	void on_button1_click(wxCommandEvent& event);
	void insert_item(const wxString&, const wxString&);
}; 

#endif
