/**
*** Author: R-CO
*** Mail: daniel1820kobe@gmail.com
*** Date: 2021-01-27
***/
#include <wx/wx.h>

#include "client_gui.hpp"

// Include main_frame.h here

IMPLEMENT_APP(WxProjectTemplateApp)

bool WxProjectTemplateApp::OnInit() {
  wxFrame *main_frame = new wxFrame(NULL, wxID_ANY, wxT("hello world!"));

  return main_frame->Show();
}