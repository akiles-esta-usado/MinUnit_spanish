CFLAGS = -Wall

TEST_SRC := minunit_example.c not_so_simpler.c
TEST_EXE := ${TEST_SRC:.c=}

default: ${TEST_EXE}

${TEST_EXE}: ${TEST_SRC}
	gcc -o $@ $@.c

