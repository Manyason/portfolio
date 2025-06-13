CC = gcc
CFLAGS = -Wall -std=c11

OBJS = main.o maze.o player.o util.o dfs.o

maze_game: $(OBJS)
	$(CC) $(CFLAGS) -o maze_game $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o maze_game