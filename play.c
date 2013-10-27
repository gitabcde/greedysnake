#include "snake.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <termios.h>
void sna_get_key(void);
void sna_help();
char dir[100];
int main(int argc,char** argv)
{
  
  struct  timeval pre_t,next_t;
  struct termios oldter,newter;
  tcgetattr(fileno(stdin),&oldter);
  newter=oldter;
  newter.c_lflag&=~ECHO;
  newter.c_lflag&=~ICANON;
  newter.c_cc[VMIN]=1;
  newter.c_cc[VTIME]=0;
  if(tcsetattr(fileno(stdin),TCSAFLUSH,&newter)!=0)
    {
      fprintf(stderr,"cannot set attrbutes of terminal\n");
      return -1;
    }
  int w,h,speed;
  if(argc==4)
    {
      w=atoi(argv[1]);
      h=atoi(argv[2]);
      speed=atoi(argv[3]);
      sna_init(w,h);

    }
  else
    {
      sna_help();
      tcsetattr(fileno(stdin),TCSANOW,&oldter);
      return 0;
    }
  int i=0;
  pthread_t msg_t;
  pthread_create(&msg_t,NULL,sna_get_key,NULL);
  gettimeofday(&pre_t,NULL);
  float inter;
  while(1)
    {
      gettimeofday(&next_t,NULL);
      inter=next_t.tv_sec*1000+next_t.tv_usec/1000-pre_t.tv_sec*1000-pre_t.tv_usec/1000;
      SNA_DETAIL_OUTPUT("before : next_t - pre_t is %f\n",inter);
      if(inter<1000/speed)
	continue;
      int ret;
      switch(dir[i])
	{
	case 'w':
	  ret=sna_update(SNA_UP);
	  break;
	case 's':
	  ret=sna_update(SNA_DOWN);
	  break;
	case 'd':
	  ret=sna_update(SNA_RIGHT);
	  break;
	case 'a':
	  ret=sna_update(SNA_LEFT);
	  break;
	case 'q':
	  tcsetattr(fileno(stdin),TCSANOW,&oldter);
	  exit(0);
	  break;
	default:
	  ret=sna_update(SNA_ANYTHING);
	  break;
	}
      if(ret==SNA_DIE)
	{
	  tcsetattr(fileno(stdin),TCSANOW,&oldter);
	  return SNA_DIE;
	}
      
      if(dir[i]!=0)
	{
	  dir[i]=0;
	  i++;
	  i=i%100;
	}
      SNA_DETAIL_OUTPUT("after : pre-next is %f\n",inter);
      pre_t=next_t;
    }
      

  tcsetattr(fileno(stdin),TCSANOW,&oldter);
  return SNA_NORMAL;
}





void sna_get_key(void)
{
  SNA_DETAIL_OUTPUT("putting message\n");
  char c;
  char last;
  int i=0;
  while(1)
    {
      c=getchar();
      if(dir[i]==0 && c!=last)
	{
	  last=c;
	  dir[i]=c;
	  i++;
	  i=i%100;
	}
    }

}

void sna_help()
{
  printf("usage:\n\
test [width] [height] [speed]\n\n");

}




















