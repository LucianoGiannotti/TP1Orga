#OBJS specifies which files to compile as part of the project
OBJS = main.c mymalloc.S

#CPPC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -Wall

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = tp1

#This is the target that compiles our executable
all : tp1

tp1: $(OBJS)
	$(CC) $(COMPILER_FLAGS) $(OBJS) -o $(OBJ_NAME)

clean: 
	rm -f *.o tp1
