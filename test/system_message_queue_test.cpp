#include "../system_message_queue.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>
using std::string;
#include <vector>
using std::vector;

#include <cstdio>

class SystemMessageQueueTest : public ::testing::Test {
 public:
  SystemMessageQueueTest()
      : kMaxKeyCount_(2),
        smq_vector_(kMaxKeyCount_),
        key_vector_(kMaxKeyCount_) {}

  ~SystemMessageQueueTest() = default;

 protected:
  void SetUp() override {
    for (size_t i = 0; i < kMaxKeyCount_; ++i) {
      smq_vector_[i].reset(new rco::SystemMessageQueue());
      key_vector_[i] = static_cast<key_t>(gKeyIndex++);
    }
  }
  void TearDown() override {}

  static size_t gKeyIndex;
  const size_t kMaxKeyCount_;
  vector<std::shared_ptr<rco::SystemMessageQueue>> smq_vector_;
  vector<key_t> key_vector_;
};

size_t SystemMessageQueueTest::gKeyIndex = 1;

TEST_F(SystemMessageQueueTest, createQueue) {
  for (size_t i = 0; i < kMaxKeyCount_; ++i) {
    auto &smq = *smq_vector_[i];
    auto key = key_vector_[i];

    // create queue
    EXPECT_TRUE(smq.createQueue(key));

    // TODO: bug fix => using msgctl to query queue
    auto msqid = msgget(key, 0);
    EXPECT_NE(msqid, -1);

    // remove queue
    if (msqid != -1) {
      EXPECT_EQ(msgctl(msqid, IPC_RMID, nullptr), 0);
    }
  }
}

TEST_F(SystemMessageQueueTest, bindQueueViaKey) {
  for (auto key : key_vector_) {
    // create new message queue
    auto msqid = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
    EXPECT_NE(msqid, -1);

    // bind queue via key
    rco::SystemMessageQueue smq;
    EXPECT_TRUE(smq.bindQueueViaKey(key));
    EXPECT_NE(smq.getQueueId(), -1);
    EXPECT_EQ(smq.getQueueId(), msqid);

    // remove queue
    EXPECT_EQ(msgctl(msqid, IPC_RMID, nullptr), 0);
  }
}

TEST_F(SystemMessageQueueTest, bindQueueViaQueueId) {
  for (auto key : key_vector_) {
    // create new message queue
    auto msqid = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
    EXPECT_NE(msqid, -1);

    // bind queue via queue id
    rco::SystemMessageQueue smq;
    EXPECT_TRUE(smq.bindQueueViaQueueId(msqid));
    if (smq.getErrorNo() != 0) {
      printf("%s\n", strerror(smq.getErrorNo()));
    }
    EXPECT_EQ(smq.getQueueId(), msqid);

    // remove queue
    EXPECT_EQ(msgctl(msqid, IPC_RMID, nullptr), 0);
  }
}

TEST_F(SystemMessageQueueTest, removeQueue) {
  for (size_t i = 0; i < kMaxKeyCount_; ++i) {
    // create queue
    EXPECT_TRUE(smq_vector_[i]->createQueue(key_vector_[i]));

    // remove queue
    EXPECT_TRUE(smq_vector_[i]->removeQueue());
  }
}

TEST_F(SystemMessageQueueTest, sendToQueue) {
  rco::SystemMessageQueue smq;
  EXPECT_TRUE(smq.createQueue(gKeyIndex++));

  static const size_t kLength_1K = 1024;
  static const size_t kBufferSize = kLength_1K * 4;  // 4kb
  struct MyData {
    MyData() : mtype(1) {}

    long mtype;
    char mbuffer[kBufferSize];
  };

  string msg =
      "hello, here is a test string with long long long long long long long "
      "length.";
  auto msg_size = msg.size() + 1 /* extra 1 byte for '\0' */;

  MyData send_data;
  memcpy(send_data.mbuffer, msg.c_str(), msg_size);

  enum MessageFlag { kBlockMode = 0 };
  const auto is_send_success =
      smq.sendToQueue(&send_data, msg_size, static_cast<int>(kBlockMode));
  EXPECT_TRUE(is_send_success);

  if (is_send_success) {
    MyData receive_data;
    enum MessageType { kReadFirst = 0 };
    EXPECT_EQ(
        msgrcv(smq.getQueueId(), &receive_data, sizeof(receive_data.mbuffer),
               MessageType::kReadFirst, kBlockMode),
        msg_size);
  }

  EXPECT_TRUE(smq.removeQueue());
}

TEST_F(SystemMessageQueueTest, RecieveFromQueue) {
  rco::SystemMessageQueue smq;
  EXPECT_TRUE(smq.createQueue(gKeyIndex++));

  static const size_t kLength_1K = 1024;
  static const size_t kBufferSize = kLength_1K * 4;  // 4kb
  struct MyData {
    MyData() : mtype(1) {}

    long mtype;
    char mbuffer[kBufferSize];
  };

  string msg =
      "hello, here is a test string with long long long long long long long "
      "length.";
  auto msg_size = msg.size() + 1 /* extra 1 byte for '\0' */;

  MyData send_data;
  memcpy(send_data.mbuffer, msg.c_str(), msg_size);

  enum MessageFlag { kBlockMode = 0 };
  const auto is_send_success =
      smq.sendToQueue(&send_data, msg_size, static_cast<int>(kBlockMode));
  EXPECT_TRUE(is_send_success);

  if (is_send_success) {
    MyData receive_data;
    enum MessageType { kReadFirst = 0 };
    EXPECT_EQ(smq.recieveFromQueue(&receive_data, sizeof(receive_data.mbuffer),
                                   MessageType::kReadFirst, kBlockMode),
              msg_size);
  }

  EXPECT_TRUE(smq.removeQueue());
}
