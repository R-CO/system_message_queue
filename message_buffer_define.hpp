#ifndef SYSTEM_MESSAGE_QUEUE_CLIENT_HPP
#define SYSTEM_MESSAGE_QUEUE_CLIENT_HPP

constexpr size_t kLength_1K = 1024UL;
constexpr size_t kBufferSize = kLength_1K * 4UL;

struct MessageBuffer {
  long mtype;
  char mtext[kBufferSize];
};

#endif  // end of define SYSTEM_MESSAGE_QUEUE_CLIENT_HPP
