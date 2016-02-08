
#include "stuff.h"
#include "search.h"
 
int debug(func)
char *func;

{
  extern int Debug;
  int who = RUSAGE_SELF;
  struct rusage *rusage;
  
  switch(Debug)
    {
      case(TRACE):
	{
	  rusage = (struct rusage*)malloc(sizeof(struct rusage));
	  getrusage(who, rusage);
	  printf("\n*%s memory = %d  \n", func, rusage->ru_maxrss*getpagesize());
	}
      break;
    }
}

