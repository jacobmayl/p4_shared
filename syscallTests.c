#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"
#include "param.h"

int
main(int argc, char **argv)
{
  int pid = getpid();
  
  // Test get and set slice
  int slice = getslice(pid);
  if (slice ==  -1) {
    printf(2, "getslice() failed!");
    exit();
  }
  printf(1, "Pid: %d, Timeslice: %d\n", pid, slice);
  
  printf(1, "Setting slice to 4\n");
  // try assigning return val to a local before compare?
  if (setslice(pid, 4) == -1) {
    printf(2, "setslice() failed!\n");
    exit();
  }
  
  printf(1, "Pid: %d, Timeslice: %d\n", pid, getslice(pid));
  
  struct pstat * stats = malloc(sizeof(struct pstat));
  getpinfo(stats);  // not currently working
    
  
  for (int i = 0; i < NPROC; i++) {
    if (stats->pid[i] < 1) {
      printf(1, "Process not found at index %d\n", i);
    } else {
      printf(1, "Process at index %d has pid %d\n", i, stats->pid[i]);
    }
  }
  exit();    
}