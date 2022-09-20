///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/colour.h>
#include <wx/font.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/intl.h>
#include <wx/panel.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/xrc/xmlres.h>

///////////////////////////////////////////////////////////////////////////

namespace rco {
///////////////////////////////////////////////////////////////////////////////
/// Class ClientMainFrameBase
///////////////////////////////////////////////////////////////////////////////
class ClientMainFrameBase : public wxFrame {
 private:
 protected:
  wxSplitterWindow* m_splitter1;
  wxPanel* m_panel1;
  wxTextCtrl* m_textCtrlDisplay;
  wxPanel* m_panel2;
  wxTextCtrl* m_textCtrlKeyIn;
  wxStatusBar* m_statusBarMain;

  // Virtual event handlers, overide them in your derived class
  virtual void m_textCtrlKeyInOnTextEnter(wxCommandEvent& event) {
    event.Skip();
  }

 public:
  ClientMainFrameBase(wxWindow* parent, wxWindowID id = wxID_ANY,
                      const wxString& title = _("Message Queue Client"),
                      const wxPoint& pos = wxDefaultPosition,
                      const wxSize& size = wxSize(800, 600),
                      long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

  ~ClientMainFrameBase();

  void m_splitter1OnIdle(wxIdleEvent&) {
    m_splitter1->SetSashPosition(0);
    m_splitter1->Disconnect(
        wxEVT_IDLE, wxIdleEventHandler(ClientMainFrameBase::m_splitter1OnIdle),
        NULL, this);
  }
};

}  // namespace rco
