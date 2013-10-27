CC=gcc
LIB_DEP=-lpthread
SNA_DEFINE=-D__SNAKE_CONSOLE__
SRC_FILE=play.c snake.c
default:
	$(CC) -oplay $(SRC_FILE) $(LIB_DEP) $(SNA_DEFINE) -g
