#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include "param.h"
#include <stddef.h>

int
main(int argc, char **argv)
{

  if(argc != 6){
    printf(2, "ERROR: incorrect arg format \n");
    exit();
  }
  
  int sliceA = atoi(argv[1]);
  char* sleepA = argv[2];
  int sliceB = atoi(argv[3]);
  char* sleepB = argv[4];
  int sleepParent = atoi(argv[5]);
  
  int pidA = fork2(sliceA);
  int pidB = 0;
  if (pidA != 0) 
    pidB = fork2(sliceB);
  
  if (pidA < 0) {
    printf(2, "Fork2(A) failed");
  } else if (pidA == 0) {  // child process
    char* argsA[] = {"loop", sleepA, NULL};
    if (exec("loop", argsA) == -1) {
      printf(1, "Loop execution failed: A");
    }
  } else if (pidB == 0) {
    char* argsB[] = {"loop", sleepB, NULL};
    if (exec("loop", argsB) == -1) {
      printf(1, "Loop execution failed: B");
    }
  } else { // parent process
    sleep(sleepParent);
    struct pstat * stats = malloc(sizeof(struct pstat));
    getpinfo(stats);
    
    int compticksA = 0;
    int compticksB = 0;
    for (int i = 0; i < NPROC; i++) {
      if (stats->pid[i] < 1) {
        continue;
      } else if (stats->pid[i] == pidA) {
        compticksA = stats->compticks[i];
      } else if (stats->pid[i] == pidB) {
        compticksB = stats->compticks[i];
      } 
    }
    
    printf(1, "%d %d\n", compticksA, compticksB);
    wait();
    wait();
    
    exit();
  }
}