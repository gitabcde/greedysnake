#include "snake_function.h"
#include "snake_type.h"
#include "snake_define.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
void sna_init(int w,int h)
{
  context.map.w=w;
  context.map.h=h;
  context.map.map=(char*)malloc(h*w);
  memset(context.map.map,SNA_EMPTY,h*w);
  context.head=malloc(sizeof(sna_snake));
  context.head->begin.h=context.head->end.h=h/2;
  context.head->begin.w=context.head->end.w=w/2;
  context.head->pre=NULL;
  context.tail=context.head;
  context.seed_rnd=20131028;
  context.dir=SNA_RIGHT;
  context.food_exist=0;
  context.food_pos.w=context.food_pos.h=0;
  
}

void sna_rndfood()
{
  if(context.food_exist==0)
    {
      srand(context.seed_rnd);
      int h,w;
      while(context.map.map[context.map.w*h+w]!=SNA_EMPTY)
	{
	  h=rand()%context.map.h;
	  w=rand()%context.map.w;
	}
      context.seed_rnd=h*w;
      context.food_pos.h=h;
      context.food_pos.w=w;
      context.food_exist=1;
      context.seed_rnd=rand();
	  
    }
  context.map.map[context.food_pos.h*context.map.w+context.food_pos.w]=SNA_FOOD;

}


int sna_to(sna_direct d)
{
  switch(d)
    {
    case SNA_UP:
      if(context.dir==SNA_UP || context.dir==SNA_DOWN)
	return SNA_WRONG_DIRECTION;
      context.dir=SNA_UP;
      break;
    case SNA_DOWN:
      if(context.dir==SNA_UP || context.dir==SNA_DOWN)
	return SNA_WRONG_DIRECTION;
      context.dir=SNA_DOWN;
      break;
    case SNA_LEFT:
      if(context.dir==SNA_LEFT || context.dir==SNA_RIGHT)
	return SNA_WRONG_DIRECTION;
      context.dir=SNA_LEFT;
      break;
    case SNA_RIGHT:
      if(context.dir==SNA_LEFT || context.dir==SNA_RIGHT)
	return SNA_WRONG_DIRECTION;
      context.dir=SNA_RIGHT;
      break;
    }
  sna_snake* newhead=malloc(sizeof(sna_snake));
  newhead->pre=NULL;
  newhead->begin=newhead->end=context.head->begin;
  context.head->pre=newhead;
  context.head=newhead;
}

int sna_console_update(sna_direct d)
{
  sna_to(d);
  int ret=sna_move_head();
  if(ret==SNA_DIE)
    return SNA_DIE;
  if(context.map.map[(context.head->begin.h-1)*context.map.w+context.head->begin.w-1]==SNA_FOOD)
    context.food_exist=0;
  else
    sna_move_tail();
  memset(context.map.map,SNA_EMPTY,context.map.h*context.map.w);
  sna_showsnake();
  sna_rndfood();
  system(CONSOLE_CLEAR);
  sna_console_display();


}

int sna_move_head()
{
  switch(context.dir)
    {
    case SNA_UP:
      context.head->begin.h-=1;
      break;
    case SNA_DOWN:
      context.head->begin.h+=1;
      break;
    case SNA_LEFT:
      context.head->begin.w-=1;
      break;
    case SNA_RIGHT:
      context.head->begin.w+=1;
      break;
    }
  if(context.head->begin.h>context.map.h || context.head->begin.h<1 || context.head->begin.w>context.map.w || context.head->begin.w<1 || context.map.map[(context.head->begin.h-1)*context.map.w+context.head->begin.w-1]==SNA_SELF)
    {
      sna_die();
      return SNA_DIE;

    }
  return SNA_NORMAL;

}

void sna_move_tail()
{
  int factor;
  switch(context.tail->begin.w==context.tail->end.w)
    {
    case 0:
      factor=(context.tail->end.w>context.tail->begin.w)?-1:1;
      context.tail->end.w+=factor;
      break;
    default:
      factor=(context.tail->end.h>context.tail->begin.h)?-1:1;
      context.tail->end.h+=factor;
      break;
    }
  if(context.tail->begin.w+context.tail->begin.h-context.tail->end.w-context.tail->end.h ==0)
    {
      sna_snake* tmp;
      tmp=context.tail->pre;
      free(context.tail);
      context.tail=tmp;

    }
  
}

void sna_die()
{
  printf("\n\n\n\tyour snake died!\t\n\n\n");


}

void sna_showsnake()
{
  sna_snake* tmp=context.tail;
  while(tmp!=NULL)
    {
      sna_showline(tmp->begin,tmp->end);
      tmp=tmp->pre;
    }
#ifdef __SNAKE_CONSOLE__
  switch(context.head->begin.h==context.head->end.h)
    {
    case 0:
      if(context.head->begin.h>context.head->end.h)
	context.map.map[(context.head->begin.h-1)*context.map.w+context.head->begin.w-1]=SNA_HEAD_DOWN;
      if(context.head->begin.h<context.head->end.h)
	context.map.map[(context.head->begin.h-1)*context.map.w+context.head->begin.w-1]=SNA_HEAD_UP;
      break;
    default:
      if(context.head->begin.w>context.head->end.w)
	context.map.map[(context.head->begin.h-1)*context.map.w+context.head->begin.w-1]=SNA_HEAD_RIGHT;
      if(context.head->begin.w<context.head->end.w)
	context.map.map[(context.head->begin.h-1)*context.map.w+context.head->begin.w-1]=SNA_HEAD_LEFT;
      break;
    }
#endif

}

void sna_showline(sna_pos begin,sna_pos end)
{
  int i=0,factor;
  
  switch(begin.w==end.w)
    {
    case 0:
      factor=(begin.w>end.w)?-1:1;
      while(begin.w+i*factor!=end.w)
	{
	  context.map.map[(begin.h-1)*context.map.w+begin.w-1+i*factor]=SNA_SELF;
	  i++;
	}
      break;
    default:
      factor=(begin.h>end.h)?-1:1;
      while(begin.h+i*factor!=end.h)
	{
	  context.map.map[(begin.h-1+i*factor)*context.map.w+begin.w-1]=SNA_SELF;
	  i++;
	}
      break;

    }

}


void sna_console_display()
{
  int i=0;
  char str[20];
  sprintf(str,"%%-.%ds|\n",context.map.w);
  while(i<context.map.h)
    {
      printf(str,&context.map.map[i*context.map.w]);
      i++;
    }



}




















