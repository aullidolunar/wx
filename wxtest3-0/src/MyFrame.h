#ifndef MY_FRAME_H_INC
#define MY_FRAME_H_INC

#include <wx/frame.h>
#include <wx/xrc/xmlres.h>

class MyFrame : public wxFrame
{
public:
	MyFrame(wxWindow* parent = nullptr);
	~MyFrame() override;
protected:
	void showAboutDlg();
}; 

#endif
