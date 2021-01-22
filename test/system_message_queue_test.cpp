#include "../system_message_queue.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <vector>
using std::vector;

#include <cstdio>

class SystemMessageQueueTest : public ::testing::Test {
 public:
  SystemMessageQueueTest()
      : kKeyCount_(3), smq_vector_(kKeyCount_), key_vector_(kKeyCount_) {
    printf("constructor()\n");
  }

  ~SystemMessageQueueTest() = default;

 protected:
  void SetUp() override {
    static int count = 0;
    printf("count = [%d]\n", count++);

    for (size_t i = 0; i < kKeyCount_; ++i) {
      smq_vector_[i].reset(new rco::SystemMessageQueue());
      key_vector_[i] = static_cast<key_t>(i);
    }
  }
  void TearDown() override {}

  const size_t kKeyCount_;
  vector<std::shared_ptr<rco::SystemMessageQueue>> smq_vector_;
  vector<key_t> key_vector_;
};

TEST_F(SystemMessageQueueTest, createQueue) {
  for (size_t i = 0; i < kKeyCount_; ++i) {
    EXPECT_TRUE(smq_vector_[i]->createQueue(key_vector_[i]));
    EXPECT_TRUE(smq_vector_[i]->removeQueue());
  }
}

TEST_F(SystemMessageQueueTest, bindQueueViaKey) {
  for (auto key : key_vector_) {
    rco::SystemMessageQueue smq;
    EXPECT_TRUE(smq.bindQueueViaKey(key));
  }
}

TEST_F(SystemMessageQueueTest, bindQueueViaQueueId) {
  for (auto &smq : smq_vector_) {
    rco::SystemMessageQueue temp_smq;
    EXPECT_TRUE(temp_smq.bindQueueViaQueueId(smq->getQueueId()));
  }
}

TEST_F(SystemMessageQueueTest, removeQueue) {
  for (size_t i = 0; i < kKeyCount_; ++i) {
    EXPECT_TRUE(smq_vector_[i]->createQueue(key_vector_[i]));
    EXPECT_TRUE(smq_vector_[i]->removeQueue());
  }
}
