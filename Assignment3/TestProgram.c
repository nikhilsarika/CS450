#include "types.h"
#include "stat.h"
#include "user.h"
#include "stdlib.h"

int
main(int argc, char *argv[])
{	
  int key = atoi(argv[1]);
  int noOfPages = atoi(argv[2]);
  getSharedPage(key,noOfPages);
  freeSharedPage(key);
  exit();
}


int
main(int argc, char *argv[])
{
   getpid();
   int pid = fork();
   if (pid ==0) {
   printf(1,"%s","inside child process\n");
} else{
   printf(1,"%s", "inside parent prcoess\n");
}

   countTraps();
// printf(1,"%d",err);
// printf(stderr, "%s", "Error from kernel");
  exit();
}


#include "types.h"
#include "stat.h"
#include "user.h"
int
main(int argc, char *argv[])
{
   int p =0;
   int* test;
   p = getSharedPage(0,3);
   test = (int *)p;
   *test = 10;
   printf(1,"Inside Parent : %d", *test);
  exit();
}


#include "types.h"
#include "stat.h"
#include "user.h"
int
main(int argc, char *argv[])
{
   int p =0;
   int* test;
   p = getSharedPage(0,3);
   test = (int *)p;
   printf(1,"Inside Parent : %d", *test);
  exit();
}   