#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  int exit_status;
  argint(0, &exit_status); //argint() must be invoked to pass in an integer.
  exit(exit_status);
  return 0;  // not reached
}

int
sys_wait(void)
{
  //TODO: Fix this function if anything needs to be added
  int *wait_status;
  argptr(0, (char**)&wait_status, sizeof(int*));
  return wait(wait_status);
}

int
sys_waitpid(void)
{
  int pid;
  int* status;
  int option;
  argint(0, &pid);
  // if(argptr(1, (char**)&status, sizeof(*status)) < 0)
  // {
  //   return -1;
  // }
  argptr(1, (char**)&status, sizeof(*status));
  argint(2, &option);
  return waitpid(pid, status, option);
}

int
sys_setpriority(void)
{
  int priority;
  if(argint(0,&priority)<0) {return -1;}
  return setpriority(priority);
}

int
sys_getpriority(void)
{
  return getpriority();
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
