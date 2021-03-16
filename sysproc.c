#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include <stddef.h>
// these functions should deal with getting the args that are used and calling the real function
int sys_setslice(void)
{
  int pid;
  int slice;
  
  if(argint(0, &pid) < 0 || argint(1, &slice) < 0)
    return -1;

  return setslice(pid, slice);
}

int sys_getslice(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;

  return getslice(pid);
}

int sys_fork2(void)
{

  int slice;

  if(argint(0, &slice) < 0)
    return -1;

  return fork2(slice);
}

int sys_getpinfo(void)
{
  // not sure what the struct equiv is to make this one like the ones above

  struct pstat *p; // needs to be initialized  
  
  if(argptr(0, (void*) &p, sizeof(p)) < 0) {  // examples used sizeof(*p) but this gives me an error
    cprintf("FAILED\n");
    return -1;
  }
  
  return getpinfo(p);
  
}


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  myproc()->timeToSleep = n;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
