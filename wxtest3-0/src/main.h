#ifndef MAIN_H_INC
#define MAIN_H_INC

#include <wx/uilocale.h>
#include <wx/app.h>
#include <wx/stdpaths.h>
#include "MyFrame.h"

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

#endif
