#include "system_message_queue.hpp"

#include <errno.h>

namespace rco {

// SystemMessageQueue::SystemMessageQueue(const key_t key, const int msgflg)
//     : key_(key), msgflg_(msgflg) {
//   // TODO:
// }

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
  if (this->queue_id_ == -1) {
    this->error_no_ = errno;
    return false;
  }

  return true;
}

bool SystemMessageQueue::createQueueWithPermission(
    const key_t key, const Permission permission) {
  // TODO:
  return false;
}

bool SystemMessageQueue::bindQueueViaKey(const key_t key) {
  static const int kGetMessageflg = 0;

  this->queue_id_ = msgget(key, kGetMessageflg);
  if (this->queue_id_ == -1) {
    this->error_no_ = errno;
    return false;
  }

  return true;
}

bool SystemMessageQueue::bindQueueViaQueueId(const int queue_id) {
  // check existed and accessible
  msqid_ds ds;
  if (msgctl(queue_id, IPC_STAT, &ds) == -1) {
    this->queue_id_ = -1;
    this->error_no_ = errno;
    return false;
  }

  this->queue_id_ = queue_id;

  return true;
}

bool SystemMessageQueue::removeQueue() {
  if (msgctl(this->queue_id_, IPC_RMID, nullptr) == -1) {
    this->error_no_ = errno;
    return false;
  }

  reset();

  return true;
}

bool SystemMessageQueue::sendToQueue(const void *msgp, const size_t msgsz,
                                     const int msgflg) {
  enum ReturnCode { ok = 0, fail = -1 };

  if (msgsnd(this->getQueueId(), msgp, msgsz, msgflg) ==
      static_cast<int>(ReturnCode::fail)) {
    this->error_no_ = errno;
    return false;
  }

  return true;
}

ssize_t SystemMessageQueue::recieveFromQueue(void *msgp, const size_t msgsz,
                                             const long msgtyp,
                                             const int msgflg) {
  const auto return_value =
      msgrcv(this->getQueueId(), msgp, msgsz, msgtyp, msgflg);
  if (return_value == static_cast<ssize_t>(-1)) {
    this->error_no_ = errno;
  }

  return return_value;
}

int SystemMessageQueue::getQueueId() const { return this->queue_id_; }

int SystemMessageQueue::getErrorNo() const { return this->error_no_; }

void SystemMessageQueue::reset() {
  this->key_ = 0;
  this->msgflg_ = 0;
  this->queue_id_ = -1;
  this->error_no_ = 0;
}

}  // end of namespace rco
