#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include "param.h"
#include <stddef.h>

int
main(int argc, char **argv)
{
  
  int pidA = fork2(2);
  int pidB = 0;
  if (pidA != 0) {
    pidB = fork2(3);
  }
  
  if (pidA < 0 || pidB < 0) {
    printf(2, "Fork2() failed\n");
  } else if (pidA == 0) {  // child process
    printf(1, "Process A\n");
    exit();
  } else if (pidB == 0) {
    printf(1, "Process B\n");
    exit();
  } else { // parent process
    printf(1, "Parent Process\n");
    wait();
    wait();
    
    exit();
  }
}