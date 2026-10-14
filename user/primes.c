#include "kernel/types.h"
#include "user/user.h"

void primes(int left) __attribute__((noreturn));

//left - doc cua pipe trai
void
primes(int left)
{
  int p;
  //doc so dau tien 
  if(read(left, &p, 4) != 4){
    close(left);
    exit(0);
  }

  printf("prime %d\n", p);

  int right[2];
  if(pipe(right) < 0){
    fprintf(2, "primes: pipe failed\n");
    exit(1);
  }

  int pid = fork();
  if(pid < 0){
    fprintf(2, "primes: fork failed\n");
    exit(1);
  }

  if(pid == 0){
    //pipe ke tiep
    close(left);        //khong doc pipe ben trai
    close(right[1]);    //khong ghi pipe ben phai
    primes(right[0]);   
  }

  //pipe hien tai khong doc tu pipe ben phai
  close(right[0]);

  //loc nhung so chia het cho p
  int n;
  while(read(left, &n, 4) == 4){
    if(n % p != 0)
      write(right[1], &n, 4);
  }

  close(left); //ben trai het so
  close(right[1]);
  wait(0);
  exit(0);
}

int
main(int argc, char *argv[])
{
  int p[2];
  pipe(p);

  if(fork() == 0){
    close(p[1]);         
    primes(p[0]);
  }

  close(p[0]);
  for(int i = 2; i <= 280; i++)
    write(p[1], &i, 4);   
  close(p[1]);           
  wait(0);              
  exit(0);
}