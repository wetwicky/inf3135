#  Main targets can be executed directly, and they are:
#  
#     compile                  compile .c file into .o
#     clean                    remove compile files
#     link                     create executable from all .o specified
#     all                      build 
#     help                     print help mesage
#  

# Environment 
CC = gcc
EXE = executable
FILE = test.txt
TEST-EXE = testexec
OBJS = arrlist.o main.o
C= arrlist.c main.c
TEST-OBJS = arrlist.o main.o
HELP = readme.txt

.SUFFIXES: .c .o

# all-------------------------------
all: link start

#link for program-------------------
link: compile
	$(CC) $(OBJS) -o $(EXE)

#link for test----------------------
test-link: test-compile
	$(CC) $(TEST-OBJS) -o $(TEST-EXE)

# compile---------------------------
compile: $(OBJS)

test-compile: $(TEST-OBJS)

.c.o:
	$(CC) -Wall -c $*.c

debug: $(OBJS) 
	$(CC) -g -c $(C)
	gdb $(EXE)

# clean-----------------------------
clean:
	rm $(EXE)
	rm $(OBJS)

test-clean:
	rm $(TEST-EXE)
	rm $(TEST-OBJS)

#run program------------------------
start: link
	./$(EXE) $(FILE)
 
# run tests-------------------------
test:  test-link
	./$(TEST-EXE) 
# help------------------------------
help: 
	less $(HELP)
	

#=======================================
