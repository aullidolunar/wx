#include <wx/xrc/xmlres.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <sstream>
#include "DialogItemEditor.h"

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

std::unique_ptr<DialogItemEditor> DialogItemEditor::Create(DialogItemEditorType type, wxWindow* parent) {
  std::unique_ptr<DialogItemEditor> dlg = make_unique<DialogItemEditor>(type, parent);
  wxXmlResource::Get()->LoadDialog(dlg.get(), parent, "MyDialog1");
  if (dlg) {
    std::stringstream ss;
    ss << (type == DialogItemEditorType::ADD_ITEM ? _("Add") : _("Edit")) << " " << _("item") << std::endl;
    dlg->SetTitle(ss.str());
  }
  return dlg;
}

DialogItemEditor::DialogItemEditor(DialogItemEditorType type, wxWindow*) {
  std::cout << "Dialog type loaded[0=add/1=edit]: " << type << std::endl;
}

void DialogItemEditor::on_button_selection(std::function<void(wxCommandEvent&)> slot) {
  Bind(wxEVT_BUTTON, slot, XRCID("dlg_button_ok"));
  Bind(wxEVT_BUTTON, slot, XRCID("dlg_button_cancel"));
}

void DialogItemEditor::on_key_down(std::function<void(wxKeyEvent&)> slot) {
  Bind(wxEVT_CHAR_HOOK, slot);
}

const wxString DialogItemEditor::get_value_from(const char* name, bool bcheck) {
  if (bcheck) {
    bool state = XRCCTRL(*this, name, wxCheckBox)->GetValue();
    return wxString::Format("%i", state);
  }
  return XRCCTRL(*this, name, wxTextCtrl)->GetValue();
}

void DialogItemEditor::set_value_to(const char* name, const wxString& val, bool bcheck) {
  if (bcheck) {
    XRCCTRL(*this, name, wxCheckBox)->SetValue(wxAtoi(val));
  } else {
    XRCCTRL(*this, name, wxTextCtrl)->SetValue(val);
  }
}

DialogItemEditor::~DialogItemEditor() {
  std::cout << "DialogItemEditor destroyed" << std::endl;
}