#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/vector.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/dirdlg.h>
#include <json/json.h>
#include <fstream>
#include "MyFrame.h"
#include "DialogItemEditor.h"

MyFrame::MyFrame(wxWindow* parent) {
  wxIcon win_icon;
#ifdef __WXMSW__
  win_icon.LoadFile("IDI_ICON1", wxBITMAP_TYPE_ICO_RESOURCE);
#else
  win_icon.LoadFile(PROGRAM_DATADIR "/main.ico", wxBITMAP_TYPE_ICO);
#endif
	wxXmlResource::Get()->LoadFrame(this, parent, "MyFrame1");
  SetTitle(PROGRAM_NAME);
  SetIcon(win_icon);
  
  m_grid1 = XRCCTRL(*this, "grid1", wxGrid);
  wxVector<wxString> colnames;
  colnames.push_back("jMan");
  colnames.push_back(_("Title"));
  colnames.push_back(_("Author"));
  colnames.push_back(_("Link"));
  wxVector<wxString>::size_type ncols = colnames.size();
  m_grid1->CreateGrid(0, ncols);
  for(wxVector<wxString>::size_type npos = 0; npos < ncols; npos++) {
    m_grid1->SetColLabelValue(npos, colnames[npos]);
  }
  m_grid1->SetSelectionMode(wxGrid::wxGridSelectionModes::wxGridSelectRows);
  m_grid1->SetColFormatBool(0);
  //m_grid1->Fit();
  // todo: allow a single selecction
  
  auto textctrl_dir = XRCCTRL(*this, "textctrl_dir", wxTextCtrl);
  auto standpaths = wxStandardPaths::Get();
  textctrl_dir->SetValue(standpaths.GetUserDir(wxStandardPaths::Dir::Dir_Music));
  
  XRCCTRL(*this, "button_find", wxButton)->Bind(wxEVT_BUTTON, [this, textctrl_dir](wxCommandEvent&) {
    wxDirDialog chooser(this, _("Select output folder"), textctrl_dir->GetValue(), wxDD_DEFAULT_STYLE|wxDD_DIR_MUST_EXIST);
    if (chooser.ShowModal() == wxID_OK) {
      textctrl_dir->SetValue(chooser.GetPath());
    }
  });
    
  auto menubar = GetMenuBar();
  
  on_menu_item_selected(menubar, XRCID("menuitem_open"), [this](wxCommandEvent&) {
    json_dlg(JSON_DLG_TYPE::OPEN);
  });
  
  on_menu_item_selected(menubar, XRCID("menuitem_saveas"), [this](wxCommandEvent&) {
    json_dlg(JSON_DLG_TYPE::SAVEAS);
  });
  
  on_menu_item_selected(menubar, XRCID("menuitem_remove"), [this](wxCommandEvent&) {
    if (m_grid1->IsSelection()) {
      int n_item = m_grid1->GetSelectedRows()[0]; //fixme: failed on nonselection
      std::cout << n_item << std::endl;
      if (n_item) m_grid1->DeleteRows(n_item);
    } else {
      wxMessageDialog msgbox(this, _("Empty grid"));
      msgbox.SetExtendedMessage(_("You must select something first"));
      msgbox.ShowModal();
    }
  });
  
  on_menu_item_selected(menubar, XRCID("menuitem_removeAll"), [this](wxCommandEvent&) {
    int items = m_grid1->GetNumberRows();
    if (items) {
      m_grid1->DeleteRows(0, items);
    } else {
      wxMessageDialog msgbox(this, _("Empty grid"));
      msgbox.SetExtendedMessage(_("You can't clear an empty list"));
      msgbox.ShowModal();
    }
  });
  
  on_menu_item_selected(menubar, XRCID("menuitem_close"), [this](wxCommandEvent&) {
    Close();
  });
  
  on_menu_item_selected(menubar, XRCID("menuitem_add"), [this](wxCommandEvent&) {
    std::unique_ptr<DialogItemEditor> ptrDlg = DialogItemEditor::Create(DialogItemEditorType::ADD_ITEM, this);
    if (ptrDlg) {
      ptrDlg->on_key_down([&ptrDlg](wxKeyEvent& event) {
        if (event.GetKeyCode() == WXK_ESCAPE) {
          ptrDlg->Destroy();
        }
        event.DoAllowNextEvent();
      });
      
      ptrDlg->on_button_selection([this, &ptrDlg](wxCommandEvent& event){
        int id = event.GetId();
        if (id == XRCID("dlg_button_ok")) {
          ptrDlg->Hide(); // oculto el diálogo
          insert_row_helper(
            ptrDlg->get_value_from("jman_check", true),
            ptrDlg->get_value_from("textctrl_title"),
            ptrDlg->get_value_from("textctrl_author"),
            ptrDlg->get_value_from("textctrl_link")
          );
        }
        ptrDlg->Destroy();
      });
      ptrDlg->ShowModal();
    } else {
      std::cout << "Error while loading DialogItemEditor" << std::endl;
    }
    
  });
  
  on_menu_item_selected(menubar, XRCID("menuitem_edit"), [this](wxCommandEvent&) {
    if (!m_grid1->IsSelection()) {
      wxMessageDialog msgbox(this, _("No selection"));
      msgbox.SetExtendedMessage(_("You must select something first"));
      msgbox.ShowModal();
      return;
    }
    std::unique_ptr<DialogItemEditor> ptrDlg = DialogItemEditor::Create(DialogItemEditorType::EDIT_ITEM, this);
    if (ptrDlg) {
      ptrDlg->on_key_down([&ptrDlg](wxKeyEvent& event) {
        if (event.GetKeyCode() == WXK_ESCAPE) {
          ptrDlg->Destroy();
        }
        event.DoAllowNextEvent();
      });
      
      ptrDlg->on_button_selection([this, &ptrDlg](wxCommandEvent& event) {
        int id = event.GetId();
        if (id == XRCID("dlg_button_ok")) {
          ptrDlg->Hide();
          int row_selected = m_grid1->GetSelectedRows()[0];
          insert_row_helper(
            ptrDlg->get_value_from("jman_check", true),
            ptrDlg->get_value_from("textctrl_title"),
            ptrDlg->get_value_from("textctrl_author"),
            ptrDlg->get_value_from("textctrl_link"),
            row_selected
          );
        }
        ptrDlg->Destroy();
      });
      int row_selected = m_grid1->GetSelectedRows()[0];
      ptrDlg->set_value_to("jman_check", m_grid1->GetCellValue(row_selected, 0), true);
      ptrDlg->set_value_to("textctrl_title", m_grid1->GetCellValue(row_selected, 1));
      ptrDlg->set_value_to("textctrl_author", m_grid1->GetCellValue(row_selected, 2));
      ptrDlg->set_value_to("textctrl_link", m_grid1->GetCellValue(row_selected, 3));
      ptrDlg->ShowModal();
    } else {
      std::cout << "Error while loading DialogItemEditor" << std::endl;
    }
  });
  
}

void MyFrame::on_menu_item_selected(wxMenuBar *ptrMenuBar, int itemId, std::function<void(wxCommandEvent&)> handler) {
  auto menuitem = ptrMenuBar->FindItem(itemId);
  if (menuitem) {
    Bind(wxEVT_MENU, handler, menuitem->GetId());
  } else {
    std::cout << "Couldn't load the menu item with ID: " << itemId << std::endl;
  }
}

void MyFrame::insert_row_helper(const wxString& j, const wxString& t, const wxString& a, const wxString& l, int num_row) {
  int curr_row;
  if (num_row == -1) {
    curr_row = m_grid1->GetNumberRows();
    m_grid1->InsertRows(curr_row+1);
  } else {
    curr_row = num_row;
  }
  m_grid1->SetCellValue(curr_row, 0, j);
  m_grid1->SetCellValue(curr_row, 1, t);
  m_grid1->SetCellValue(curr_row, 2, a);
  m_grid1->SetCellValue(curr_row, 3, l);
  m_grid1->MakeCellVisible(curr_row, 0);
}

void MyFrame::json_dlg(int type) {
  if (type == JSON_DLG_TYPE::OPEN) {
    wxFileDialog opener(this, _("Select JSON file"), wxEmptyString, wxEmptyString, "JSON (*.json)|*.json", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (opener.ShowModal() == wxID_OK) {
      std::ifstream file_in(opener.GetPath());
      Json::Value json_obj;
      file_in >> json_obj;
      int items_len = json_obj.size();
      for (int pos = 0; pos < items_len; pos++) {
        std::stringstream ss;
        ss << "Song" << pos;
        std::string header = ss.str();
        insert_row_helper(
          (json_obj[header]["jMan"].asBool() ? "1" : "0"),
          json_obj[header]["Title"].asString(),
          json_obj[header]["Artist"].asString(),
          json_obj[header]["Link"].asString()
        );
      }
    }
  } else {
    int items_len = m_grid1->GetNumberRows();
    if (items_len) {
      wxFileDialog saver(this, _("Save JSON file"), wxEmptyString, wxEmptyString, "JSON (*.json)|*.json", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
      if (saver.ShowModal() == wxID_OK) {
        std::ofstream file_out(saver.GetPath());
        Json::StreamWriterBuilder builder;
        builder.settings_["emitUTF8"] = true;
        Json::Value json_obj;
        for (int pos = 0; pos < items_len; pos++) {
          std::stringstream ss;
          ss << "Song" << pos;
          std::string header = ss.str();
          int state;
          m_grid1->GetCellValue(pos, 0).ToInt(&state);
          json_obj[header]["jMan"] = (state ? true : false);
          json_obj[header]["Title"] = m_grid1->GetCellValue(pos, 1).ToStdString();
          json_obj[header]["Artist"] = m_grid1->GetCellValue(pos, 2).ToStdString();
          json_obj[header]["Link"] = m_grid1->GetCellValue(pos, 3).ToStdString();
        }
        std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        writer->write(json_obj, &file_out);
        file_out.close();
       }
     } else {
       	wxMessageDialog msgbox(this, _("Empty grid"));
        msgbox.SetExtendedMessage(_("You can't save an empty list"));
        msgbox.ShowModal();
     }
  }
}