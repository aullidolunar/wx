#ifndef MY_FRAME_H_INC
#define MY_FRAME_H_INC

#include <wx/xrc/xmlres.h>
#include <wx/grid.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/stdpaths.h>

enum JSON_DLG_TYPE {
  OPEN = 0,
  SAVEAS
};

class MyFrame : public wxFrame
{
private:
  wxGrid* m_grid1;
public:
	MyFrame(wxWindow* parent = nullptr);
protected:
  void on_menu_item_selected(wxMenuBar*, int, std::function<void(wxCommandEvent&)>);
  void insert_row_helper(const wxString&, const wxString&, const wxString&, const wxString&, int num_row = -1);
  void json_dlg(int);
}; 

#endif
