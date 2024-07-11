#ifndef _FRAME_H_INCLUDED_
#define _FRAME_H_INCLUDED_

#include <wx/frame.h>
#include <wx/listctrl.h>

class MyFrame : public wxFrame
{
private:
	int next_row;
	wxListView* m_list;
public:
	MyFrame(wxWindow* parent = nullptr);

protected:
	void on_button1_click(wxCommandEvent& event);
	void insert_item(const wxString&, const wxString&);
}; 

#endif
