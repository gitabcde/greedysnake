#ifndef SNA_DEFINE_H
#define SNA_DEFINE_H

#ifdef __WIN32_CONSOLE__
#define CONSOLE_CLEAR "cls"
#else 
#define CONSOLE_CLEAR "clear"
#endif

#ifdef __SNA_DEBUG_DETAIL__
#define SNA_DETAIL_OUTPUT(...) printf(__VA_ARGS__)
#else
#define SNA_DETAIL_OUTPUT(...) 
#endif

#ifdef __SNA_DEBUG_TMP__
#define SNA_TMP_OUTPUT(...) printf(__VA_ARGS__)
#else
#define SNA_TMP_OUTPUT(...) 
#endif




#define SNA_FOOD '*'
#define SNA_BLOCK '%'
#define SNA_EMPTY '+'
#define SNA_SELF '0'
#define SNA_HEAD_LEFT '<'
#define SNA_HEAD_RIGHT '>'
#define SNA_HEAD_UP 'A'
#define SNA_HEAD_DOWN 'V'




#define SNA_NORMAL 0
#define SNA_WRONG_DIRECTION 1
#define SNA_DIE 2





#endif


















