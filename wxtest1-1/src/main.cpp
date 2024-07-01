#include "frame.h"

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
