#ifndef RCO_UTILITY_SYSTEM_MESSAGE_QUEUE_HPP
#define RCO_UTILITY_SYSTEM_MESSAGE_QUEUE_HPP
/**
*** Author: R-CO
*** E-mail: daniel1820kobe@gmail.com
*** Date: 2021-01-22
**/
// unix system header
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

namespace rco {

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
   *   long mtype; // It must have, and named it "mtype".
   *   char mtext[1] // message data
   * }
   *
   * Please refer to `int msgsnd(int msqid, const void *msgp, size_t msgsz, int
   * msgflg)` in <sys/msg.h>
   */
  bool sendToQueue(const void* msgp, const size_t msgsz, const int msgflg);
  ssize_t receiveFromQueue(void* msgp, const size_t msgsz, const long msgtyp,
                           const int msgflg);

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

#endif  // end of defin RCO_UTILITY_SYSTEM_MESSAGE_QUEUE_HPP
