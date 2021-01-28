///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui_widgets_base.h"

///////////////////////////////////////////////////////////////////////////
using namespace rco;

ClientMainFrameBase::ClientMainFrameBase(wxWindow* parent, wxWindowID id,
                                         const wxString& title,
                                         const wxPoint& pos, const wxSize& size,
                                         long style)
    : wxFrame(parent, id, title, pos, size, style) {
  this->SetSizeHints(wxDefaultSize, wxDefaultSize);

  wxBoxSizer* bSizer1;
  bSizer1 = new wxBoxSizer(wxVERTICAL);

  m_splitter1 = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition,
                                     wxDefaultSize, wxSP_3D);
  m_splitter1->Connect(
      wxEVT_IDLE, wxIdleEventHandler(ClientMainFrameBase::m_splitter1OnIdle),
      NULL, this);

  m_panel1 = new wxPanel(m_splitter1, wxID_ANY, wxDefaultPosition,
                         wxDefaultSize, wxTAB_TRAVERSAL);
  wxBoxSizer* bSizer2;
  bSizer2 = new wxBoxSizer(wxVERTICAL);

  m_textCtrlDisplay = new wxTextCtrl(
      m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
      wxHSCROLL | wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH | wxTE_RICH2);
  bSizer2->Add(m_textCtrlDisplay, 1, wxALL | wxEXPAND, 5);

  m_panel1->SetSizer(bSizer2);
  m_panel1->Layout();
  bSizer2->Fit(m_panel1);
  m_panel2 = new wxPanel(m_splitter1, wxID_ANY, wxDefaultPosition,
                         wxDefaultSize, wxTAB_TRAVERSAL);
  wxBoxSizer* bSizer3;
  bSizer3 = new wxBoxSizer(wxVERTICAL);

  m_textCtrlKeyIn = new wxTextCtrl(
      m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
      wxHSCROLL | wxTE_MULTILINE | wxTE_PROCESS_ENTER | wxTE_RICH2);
  bSizer3->Add(m_textCtrlKeyIn, 1, wxALL | wxEXPAND, 5);

  m_panel2->SetSizer(bSizer3);
  m_panel2->Layout();
  bSizer3->Fit(m_panel2);
  m_splitter1->SplitHorizontally(m_panel1, m_panel2, 0);
  bSizer1->Add(m_splitter1, 1, wxEXPAND, 5);

  this->SetSizer(bSizer1);
  this->Layout();
  m_statusBarMain = this->CreateStatusBar(2, wxSTB_SIZEGRIP, wxID_ANY);

  this->Centre(wxBOTH);

  // Connect Events
  m_textCtrlKeyIn->Connect(
      wxEVT_COMMAND_TEXT_ENTER,
      wxCommandEventHandler(ClientMainFrameBase::m_textCtrlKeyInOnTextEnter),
      NULL, this);
}

ClientMainFrameBase::~ClientMainFrameBase() {
  // Disconnect Events
  m_textCtrlKeyIn->Disconnect(
      wxEVT_COMMAND_TEXT_ENTER,
      wxCommandEventHandler(ClientMainFrameBase::m_textCtrlKeyInOnTextEnter),
      NULL, this);
}
