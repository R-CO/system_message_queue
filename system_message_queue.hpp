#ifndef RCO_UTILITY_SYSTEM_MESSAGE_QUEUE_HPP
#define RCO_UTILITY_SYSTEM_MESSAGE_QUEUE_HPP
/**
*** Author: R-CO
*** E-mail: daniel1820kobe@gmail.com
*** Date: 2021-01-22
**/
// unix system header
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

namespace rco {

namespace sysmsgq {

/*
 * To inherit this structure for calling template function send/receive
 * ex:
 *   struct MyData : public rco::sysmsgq::MessageBufferBase {
 *     struct TYPE_OF_CONTIGUOUS_MEMORY_BLOCK {
 *       // ...
 *     };
 *   };
 *   rco::SystemMessageQueue smq;
 *   smq.createQueueViaKey(key);
 *   MyData data;
 *   data.mtype = 1;
 *   // data.actual_data = XXXXXX;
 *   smq.sendToQueue(data, msgflg);
 */
struct MessageBufferBase {
  long mtype;

  MessageBufferBase() : mtype(0) {}
  explicit MessageBufferBase(const long message_type) : mtype(message_type) {}
};

}  // end of namespace sysmsgq

class SystemMessageQueue {
 public:
  enum class SystemMessageFlag : int {
    open_existed,
    create_or_open_existed,
    create_new_only
  };

  // these values is "NOT" hex
  enum class Permission : int {
    owner_only = 0600,
    owner_and_group = 0660,
    all = 0666
  };

  SystemMessageQueue() = default;
  // SystemMessageQueue(const key_t key, const int msgflg); // TODO:

  // No default copy constructor
  SystemMessageQueue(const SystemMessageQueue& SystemMessageQueeu) = delete;
  // No default operator=
  SystemMessageQueue& operator=(
      const SystemMessageQueue& system_message_queue) = delete;

  ~SystemMessageQueue();

  // default permission: Permission::all
  bool createQueue(const key_t key);
  bool createQueueWithPermission(const key_t key, const Permission permission);
  bool bindQueueViaKey(const key_t key);
  bool bindQueueViaQueueId(const int queue_id);
  bool removeQueue();

  /*
   * structure should be somthing like
   * struct {
   *   long mtype; // Structure must have this member(1st), and it's type must
   * be 'long int'. char mtext[1] // message data
   * }
   *
   * Please refer to `int msgsnd(int msqid, const void *msgp, size_t msgsz, int
   * msgflg)` in <sys/msg.h>
   */
  bool sendToQueue(const void* msgp, const size_t msgsz, const int msgflg);
  ssize_t receiveFromQueue(void* msgp, const size_t msgsz, const long msgtyp,
                           const int msgflg);

  template <typename T>
  bool sendToQueue(const T& msgst, const int msgflg) {
    const sysmsgq::MessageBufferBase& msg_buffer = msgst;
    enum ReturnCode { ok = 0, fail = -1 };
    if (msgsnd(this->getQueueId(), &msgst,
               sizeof(msgst) - sizeof(msg_buffer.mtype),
               msgflg) == static_cast<int>(ReturnCode::fail)) {
      this->error_no_ = errno;
      return false;
    }

    return true;
  }

  int getQueueId() const;
  int getErrorNo() const;

 protected:
  void reset();

 private:
  key_t key_ = 0;
  int msgflg_ = 0;

  int queue_id_ = -1;

  int error_no_ = 0;
};

}  // end of namespace rco

#endif  // end of define RCO_UTILITY_SYSTEM_MESSAGE_QUEUE_HPP
