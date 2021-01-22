#ifndef RCO_UTILITY_SYSTEM_MESSAGE_QUEUE
#define RCO_UTILITY_SYSTEM_MESSAGE_QUEUE
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
  enum class Permission : int {
    owner_only = 0x0600,
    owner_and_group = 0x0660,
    all = 0x0666
  };

  SystemMessageQueue() = default;
  SystemMessageQueue(const key_t key, const int msgflg);

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

  bool sendToQueue();
  bool recieveFromQueue();

  int getQueueId() const;

 protected:
 private:
  key_t key_ = 0;
  int msgflg_ = 0;

  int queue_id_ = -1;

  int error_no_ = 0;
};

}  // end of namespace rco

#endif  // end of defin RCO_UTILITY_SYSTEM_MESSAGE_QUEUE
