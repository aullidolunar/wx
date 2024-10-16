#ifndef MY_FRAME_H_INC
#define MY_FRAME_H_INC

#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <string>

class MyFrame : public wxFrame
{
  wxTextCtrl m_entry1;
  wxCheckBox m_check1;
public:
	MyFrame(wxWindow* parent = nullptr);
	virtual ~MyFrame();
protected:
}; 

#endif
