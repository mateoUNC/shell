// Testing/src/test_utils.c

#include "test_utils.h"

int exit_called = 0;
int exit_status = 0;
jmp_buf exit_env;

void test_exit(int status) {
  exit_called = 1;
  exit_status = status;
  longjmp(exit_env, 1);
}
