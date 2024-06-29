#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/xrc/xmlres.h>

class MyFrame : public wxFrame
{
private:
	 void on_button1_click(wxCommandEvent& event)
	 {
		 Close();
	 }
	 
public:
	MyFrame(wxWindow* parent = nullptr)
	{
		wxXmlResource::Get()->LoadFrame(this, parent, "MyFrame1");
		Bind(wxEVT_BUTTON, &MyFrame::on_button1_click, this, XRCID("m_button1"));
		// GetSizer()->SetSizeHints(this);
	}
}; 

class MyApp : public wxApp
{
public:
    bool OnInit() override
	{
		wxXmlResource::Get()->InitAllHandlers();
		wxXmlResource::Get()->Load(PROGRAM_DATADIR "/MyFrame.xrc");
		auto frm = new MyFrame();
		frm->Show();
		return true;
	}
};
 
wxIMPLEMENT_APP(MyApp);