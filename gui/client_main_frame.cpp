#include "client_main_frame.hpp"

// C++ standard library
#include <mutex>
#include <thread>

// R-CO's library
#include "../message_buffer_define.hpp"
#include "../system_message_queue.hpp"

namespace rco {

SystemMessageQueue g_smq_send;
SystemMessageQueue g_smq_receive;

std::mutex g_mutex_receive;
bool stop_receive = false;

void receiveThread(const ClientMainFrame *frame) {
  while (!stop_receive) {
    static MessageBuffer receive_data = {1, ""};
    memset(receive_data.mtext, 0, sizeof(receive_data.mtext));
    if (g_smq_receive.receiveFromQueue(
            &receive_data, sizeof(receive_data.mtext), 0, IPC_NOWAIT) !=
        static_cast<ssize_t>(-1)) {
      wxString message =
          std::move(wxString::FromUTF8Unchecked(receive_data.mtext));
      wxThreadEvent thread_event;
      thread_event.SetString(message);
      wxQueueEvent(const_cast<ClientMainFrame *>(frame), thread_event.Clone());
    }

    std::this_thread::sleep_for(std::chrono::microseconds(20));
  }

  {
    std::lock_guard lock_guard(g_mutex_receive);
    stop_receive = false;
  }
}

ClientMainFrame::ClientMainFrame(wxWindow *parent)
    : ClientMainFrameBase(parent) {
  const auto key_send = 123456;
  const auto key_receive = key_send + 1;

  if (!g_smq_send.bindQueueViaKey(key_send)) {
    if (!g_smq_send.createQueue(key_send)) {
      // throw here?
    }
  }
  if (!g_smq_receive.bindQueueViaKey(key_receive)) {
    if (!g_smq_receive.createQueue(key_receive)) {
      // throw here?
    }
  }

  Bind(wxEVT_THREAD, &ClientMainFrame::receiveThreadEventHandler, this,
       wxID_ANY);

  std::thread(receiveThread, this).detach();
}

ClientMainFrame::~ClientMainFrame() {
  // TODO: Stop receiveThread before close app
  {
    std::lock_guard lock_guard(g_mutex_receive);
    stop_receive = true;
  }

  while (stop_receive) {
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
}

void ClientMainFrame::m_textCtrlKeyInOnTextEnter(wxCommandEvent &event) {
  wxString buffer = m_textCtrlKeyIn->GetValue();
  const auto msgsz = buffer.utf8_str().length() + 1;

  static MessageBuffer message_buffer = {1, ""};
  memset(message_buffer.mtext, 0, sizeof(message_buffer.mtext));
  memcpy(message_buffer.mtext, buffer.utf8_str().data(), msgsz);
  g_smq_send.sendToQueue(&message_buffer, msgsz, 0);

  m_textCtrlKeyIn->Clear();
}

void ClientMainFrame::receiveThreadEventHandler(wxThreadEvent &event) {
  static const wxString title{
      _("Receive message from server:\n")};  // A better name?
  static const wxString new_line{wxS("\n")};
  m_textCtrlDisplay->AppendText(title);
  m_textCtrlDisplay->AppendText(event.GetString());
  m_textCtrlDisplay->AppendText(new_line);
}

}  // end of namespace rco
