CC = gcc

mainfile = game_of_life.c
outfile = game_of_life

all: $(mainfile)
	$(CC) -o $(outfile) $(mainfile)

clean:
	rm -v $(outfile)