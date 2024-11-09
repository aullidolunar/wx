#ifndef DIALOGITEMEDITOR_H_INC
#define DIALOGITEMEDITOR_H_INC

#include <wx/dialog.h>
#include <memory>
#include <iostream>

enum DialogItemEditorType {
  ADD_ITEM = 0,
  EDIT_ITEM
};

class DialogItemEditor : public wxDialog
{
private:
public:
	static std::unique_ptr<DialogItemEditor> Create(DialogItemEditorType, wxWindow* parent = nullptr);
  DialogItemEditor(DialogItemEditorType, wxWindow* parent = nullptr);
  virtual ~DialogItemEditor();
  void on_button_selection(std::function<void(wxCommandEvent&)>);
  void on_key_down(std::function<void(wxKeyEvent&)>);
  const wxString get_value_from(const char*, bool bcheck = false);
  void set_value_to(const char*, const wxString&, bool bcheck = false);
protected:
}; 

#endif
