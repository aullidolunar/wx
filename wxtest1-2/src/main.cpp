#include "frame.h"

class MyApp : public wxApp
{
public:
    bool OnInit() override
	{
		auto frm = new MyFrame();
		frm->Show();
		return true;
	}
};
 
wxIMPLEMENT_APP(MyApp);
