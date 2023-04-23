#include <sys/syscall.h>
#include <unistd.h>
#include <uv-common.h>
#include <uv.h>

#define CALL_NO_SYSCALL 514
#define CALL_NO_REQ_DERIVE 515
#define CALL_NO_WORKER_THREAD 519

void log_syscall(int call, const void* handle_or_req) {
  syscall(CALL_NO_SYSCALL, call, handle_or_req);
}

// 一些地方 (fs) 存在请求自行派生了新请求的状况
// 用此函数记录这种派生关系
void log_req_derive(const void* parent_req, const void* child_req) {
  syscall(CALL_NO_REQ_DERIVE, parent_req, child_req);
}

void log_worker_thread(const void* handle_or_req) {
  syscall(CALL_NO_WORKER_THREAD, handle_or_req);
}

void log_recvmmsg(const void* handle_or_req) {
#if defined(__i386__)
  log_syscall(SYS_sosocketcall, handle_or_req);
#elif defined(__NR_recvmmsg)
  log_syscall(__NR_recvmmsg, handle_or_req);
#endif
}

void log_sendmmsg(const void* handle_or_req) {
#if defined(__i386__)
  log_syscall(SYS_sosocketcall, handle_or_req);
#elif defined(__NR_sendmmsg)
  log_syscall(__NR_sendmmsg, handle_or_req);
#endif
}

void log_accept(const void* handle_or_req) {
#if defined(__linux__)
  log_syscall(SYS_accept4, handle_or_req);
#else
  log_syscall(SYS_accept, handle_or_req);
#endif
}
