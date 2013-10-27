#ifndef SNAKE_FUNCTION_H
#define SNAKE_FUNCTION_H
#include "snake_type.h"

void sna_init(int w,int h);
void sna_rndfood();
int sna_to(sna_direct d);
int sna__console_update(sna_direct d);
int sna_move_head();
void sna_move_tail();
int sna__console_die();
void sna_console_display();
void sna_showsnake();
void sna_showline(sna_pos begin,sna_pos end);

#ifdef __SNAKE_CONSOLE__
#define sna_display sna_console_display
#define sna_update sna_console_update
#define sna_die sna_console_die

#else
#define sna_display sna_sdl_display
#define sna_die sna_sdl_die
#define sna_update sna_sdl_update
#endif


#endif


















