FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors
LIBS = -lm
FILES = cluster.o groups_division.o group.o matrixB.o maximization.o modularity.o powerIteration.o spmat.o vecOp.o

all: cluster
clean:
		rm -rf *.o cluster 

cluster: $(FILES)
		gcc $(FILES) -o cluster $(LIBS)

groups_division.o: groups_division.c groups_division.h group.h ERROR.h
		gcc $(FLAGS) -c $*.c
		
cluster.o: cluster.c ERROR.h
		gcc $(FLAGS) -c $*.c

group.o: group.c group.h
		gcc $(FLAGS) -c $*.c
		
matrixB.o: matrixB.c matrixB.h vecOp.h ERROR.h
		gcc $(FLAGS) -c $*.c


maximization.o: maximization.c maximization.h matrixB.h ERROR.h
		gcc $(FLAGS) -c $*.c
		
modularity.o: modularity.c modularity.h powerIteration.h matrixB.h maximization.h ERROR.h
		gcc $(FLAGS) -c $*.c

powerIteration.o: powerIteration.c powerIteration.h vecOp.h matrixB.h ERROR.h
		gcc $(FLAGS) -c $*.c
		
spmat.o: spmat.c spmat.h ERROR.h
		gcc $(FLAGS) -c $*.c

vecOp.o: vecOp.c vecOp.h groups_division.h
		gcc $(FLAGS) -c $*.c