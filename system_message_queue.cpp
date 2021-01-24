#include "system_message_queue.hpp"

#include <errno.h>

namespace rco {

SystemMessageQueue::SystemMessageQueue(const key_t key, const int msgflg)
    : key_(key), msgflg_(msgflg) {}

SystemMessageQueue::~SystemMessageQueue() {
  // TODO:
}

// default permission: Permission::all
bool SystemMessageQueue::createQueue(const key_t key) {
  static const int kMessageFlag =
      IPC_CREAT | IPC_EXCL | static_cast<int>(Permission::all);

  this->key_ = key;
  this->msgflg_ = kMessageFlag;
  this->queue_id_ = msgget(key, kMessageFlag);
  error_no_ = errno;

  return (this->queue_id_ >= 0) ? true : false;
}

bool SystemMessageQueue::createQueueWithPermission(
    const key_t key, const Permission permission) {
  // TODO:
  return false;
}

bool SystemMessageQueue::bindQueueViaKey(const key_t key) {
  static const int kGetMessageflg = 0;
  static const int kCreateOnlyMessageflg =
      static_cast<int>(Permission::all) | IPC_CREAT | IPC_EXCL;

  // check exist
  auto msqid = msgget(key, kCreateOnlyMessageflg);
  if (msqid != -1) {
    msgctl(msqid, IPC_RMID, nullptr);
    return false;
  }

  this->queue_id_ = msgget(key, kGetMessageflg);
  if (this->queue_id_ == -1) {
    return false;
  }

  return true;
}

bool SystemMessageQueue::bindQueueViaQueueId(const int queue_id) {
  // TODO:
  return false;
}

bool SystemMessageQueue::removeQueue() {
  auto rc = msgctl(this->queue_id_, IPC_RMID, nullptr);
  this->error_no_ = errno;

  return (rc == 0) ? true : false;
}

bool SystemMessageQueue::sendToQueue() {
  // TODO:
  return false;
}

bool SystemMessageQueue::recieveFromQueue() {
  // TODO:
  return false;
}

int SystemMessageQueue::getQueueId() const { return this->queue_id_; }

}  // end of namespace rco
