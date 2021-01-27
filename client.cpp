/**
*** Author: R-CO
*** E-mail: daniel1820kobe@gmail.com
*** Date: 2021-01-22
**/
// C++ standard library
#include <cstdlib>
#include <cstring>
#include <exception>
using std::exception;
#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

// R-CO's library
#include "message_buffer_define.hpp"
#include "system_message_queue.hpp"

int main(int argc, char* argv[]) {
  auto key_send = 123456;
  auto key_receive = key_send + 1;

  if (argc >= 2) {
    try {
      key_send = std::stoi(argv[1]);
      key_receive = key_send + 1;
    } catch (const exception& e) {
      cerr << "Convert argv[1] to int failed.\n Exception: " << e.what()
           << endl;
      return EXIT_FAILURE;
    }
  }

  rco::SystemMessageQueue smq_send;
  if (!smq_send.bindQueueViaKey(key_send)) {
    // message queue is not exist, try to create it with key
    if (smq_send.getErrorNo() == EACCES) {
      cerr << "Bind queue with key failed." << endl;
      cerr << "Errno = [" << smq_send.getErrorNo() << "]" << endl;
      return EXIT_FAILURE;
    }

    if (!smq_send.createQueue(static_cast<key_t>(key_send))) {
      cerr << "Can not create queue with key." << endl;
      cerr << "Errno = [" << smq_send.getErrorNo() << "]" << endl;
      return EXIT_FAILURE;
    }
  }

  rco::SystemMessageQueue smq_receive;
  if (!smq_receive.bindQueueViaKey(key_receive)) {
    // message queue is not exist, try to create it with key
    if (smq_receive.getErrorNo() == EACCES) {
      cerr << "Bind queue with (key+1) failed." << endl;
      cerr << "Errno = [" << smq_receive.getErrorNo() << "]" << endl;
      return EXIT_FAILURE;
    }

    if (!smq_receive.createQueue(static_cast<key_t>(key_receive))) {
      cerr << "Can not create queue with (key+1)." << endl;
      cerr << "Errno = [" << smq_receive.getErrorNo() << "]" << endl;
      return EXIT_FAILURE;
    }
  }

  string input_buffer;
  do {
    cout << "Please key in message or type \"q!\" to quit.\nKey in:";
    std::getline(cin, input_buffer);
    if (input_buffer != "q!" && input_buffer != "Q!") {
      const auto msgsz = input_buffer.size() + 1;
      MessageBuffer send_buffer;
      send_buffer.mtype = 1;
      memcpy(send_buffer.mtext, input_buffer.c_str(), msgsz);
      if (!smq_send.sendToQueue(&send_buffer, msgsz, 0)) {
        cerr << "Send message to queue failed." << endl;
        cerr << "Errno = [" << smq_send.getErrorNo() << "]" << endl;
        continue;
      }

      cout << "Wait for receiving message from queue..." << endl;
      MessageBuffer receive_data;
      receive_data.mtype = 1;
      if (smq_receive.receiveFromQueue(&receive_data,
                                       sizeof(receive_data.mtext), 0,
                                       0) == static_cast<ssize_t>(-1)) {
        cerr << "Receive message from queue failed." << endl;
        cerr << "Errno = [" << smq_receive.getErrorNo() << "]" << endl;
        continue;
      }

      cout << "Received message:" << endl;
      cout << receive_data.mtext << endl;
    }
  } while (input_buffer != "q!" && input_buffer != "Q!");

  return EXIT_SUCCESS;
}
