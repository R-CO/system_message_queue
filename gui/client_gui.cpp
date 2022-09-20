/**
*** Author: R-CO
*** Mail: daniel1820kobe@gmail.com
*** Date: 2021-01-27
***/
#include "client_gui.hpp"

#include <wx/wx.h>

// Include main_frame.h here
#include "client_main_frame.hpp"

IMPLEMENT_APP(WxProjectTemplateApp)

bool WxProjectTemplateApp::OnInit() {
  rco::ClientMainFrame *main_frame = new rco::ClientMainFrame(nullptr);

  return main_frame->Show();
}