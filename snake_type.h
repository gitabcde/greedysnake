#ifndef SNAKE_TYPE_H
#define SNAKE_TYPE_H

typedef struct tag_sna_map{
  int w;
  int h;
  char* map;

}sna_map;
typedef struct tag_sna_pos{
  int w;
  int h;
}sna_pos;

typedef struct tag_sna_snake{
  struct sna_snake* pre;
  sna_pos end;
  sna_pos begin;


}sna_snake;

typedef enum tag_sna_direct{
  SNA_UP,
  SNA_DOWN,
  SNA_LEFT,
  SNA_RIGHT,
  SNA_ANYTHING

}sna_direct;

typedef struct tag_sna_context
{
  sna_map map;
  sna_snake* head;
  sna_snake* tail;
  int seed_rnd;
  sna_direct dir;
  char food_exist;
  sna_pos food_pos;
}sna_context;
static  sna_context context;


#endif


