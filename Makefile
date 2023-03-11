## Set default configuration
CC = gcc
FLAGS = -g -O0 -w
INC_DIR = -L. -I./src/
DEF =
CHECK_LIB = -lcheck
OS:=$(shell uname -s)
CCOV = -lgcov --coverage

LIB_HEADER = s21_string.h
LIB_FILE =
LIB =
LIB_DIR = src/lib/
OBJ_DIR = obj/
COV_DIR = coverage_info/
TEST_DIR = tests/
LIB_OBJ_DIR = $(OBJ_DIR)lib/
COV_OBJ_DIR = $(COV_DIR)$(OBJ_DIR)

ifeq ($(OS), Darwin)
	LIB_FILE += s21_string.a
	LIB += s21_string.a
else
	CHECK_LIB += -lrt -lpthread -lm -lsubunit
	LIB_FILE = libs21_string.a
	LIB += -ls21_string
	DEF = -DLINUX
endif

## Make array of all object files for library
LIB_SRCS = $(addprefix $(LIB_DIR),s21_string.c \
								  s21_common.c \
								  s21_sprintf.c \
								  s21_sprintf_specs.c \
								  s21_sprintf_getters.c \
								  s21_sprintf_converters.c \
								  s21_sprintf_flags.c \
								  s21_sscanf.c \
								  s21_sscanf_specs.c \
								  s21_sscanf_preparing.c \
								  s21_sscanf_converters.c \
								  s21_sscanf_setters.c \
								  s21_sprintf_common.c)

RND_TEST_SRCS = $(addprefix $(TEST_DIR),s21_string_test_main.c \
								    	s21_string_test.c \
										s21_string_basic_test.c \
										s21_string_extended_test.c \
										s21_string_sprintf_basic_test.c \
										s21_string_sscanf_test.c)

LIB_OBJS = $(patsubst src/%.c, $(OBJ_DIR)%.o, $(LIB_SRCS))
COV_OBJS = $(patsubst %.c, $(COV_OBJ_DIR)%.o, $(LIB_SRCS))

TEST_FILE = $(TEST_DIR)s21_tests.c
TEST_EXEC = test
RND_TEST_EXEC = random_test
COV_EXEC = $(COV_DIR)test_cov
COV_INFO = $(COV_DIR)s21_string.info
COV_REPORT = $(COV_DIR)index.html

vpath %.c $(LIB_DIR)
vpath $(LIB_HEADER) src/

all: $(LIB_FILE)

test: $(LIB_FILE)
	checkmk $(TEST_DIR)s21_coverage_tests.check > $(TEST_FILE)
	$(CC) $(FLAGS) $(INC_DIR) $(TEST_FILE) $(LIB) $(CHECK_LIB) -o $(TEST_EXEC)

random_test: $(LIB_FILE) $(RND_TEST_SRCS)
	$(CC) $(FLAGS) $(INC_DIR) $(RND_TEST_SRCS) $(LIB) $(CHECK_LIB) -o $(RND_TEST_EXEC)

extended_test: $(LIB_FILE)
	$(CC) $(FLAGS) $(INC_DIR) tests/vova_test.c $(LIB) $(CHECK_LIB) -o vova_test
	$(CC) $(TEST_DIR)SUITE_main.c $(LIB) $(INC_DIR) $(CHECK_LIB) -o suite_main
	$(CC) $(TEST_DIR)SUITE_aux__1.c $(LIB) $(INC_DIR) $(CHECK_LIB) -o suite_1
	$(CC) $(TEST_DIR)SUITE_aux__2.c $(LIB) $(INC_DIR) $(CHECK_LIB) -o suite_2
	$(CC) $(TEST_DIR)SUITE_aux__3.c $(LIB) $(INC_DIR) $(CHECK_LIB) -o suite_3
	$(CC) $(TEST_DIR)SUITE_aux__4.c $(LIB) $(INC_DIR) $(CHECK_LIB) -o suite_4

gcov_report: test $(COV_OBJS)
	$(CC) $(FLAGS) $(INC_DIR) $(CCOV) $(LIB) $(TEST_FILE) $(COV_OBJS) $(CHECK_LIB) -o $(COV_EXEC)
	@-./$(COV_EXEC)
	@gcov -f $(COV_EXEC) -o $(COV_DIR)
	@lcov -q -c -d $(COV_DIR) -o $(COV_INFO) --exclude "$(TEST_DIR)*"
	@genhtml -q $(COV_INFO) -o $(COV_DIR)
	@open $(COV_REPORT)
	@rm -rf *.gc*

$(LIB_FILE): $(LIB_OBJS)
	ar rc $@ $^
	ranlib $@

$(LIB_OBJ_DIR)%.o: %.c $(LIB_HEADER)
	@mkdir -p $(LIB_OBJ_DIR)
	$(CC) $(FLAGS) $(INC_DIR) $(DEF) -c $< -o $@

$(COV_OBJ_DIR)%.o: %.c $(LIB_HEADER)
	@mkdir -p $(COV_OBJ_DIR)$(LIB_DIR)
	@$(CC) $(FLAGS) $(INC_DIR) $(DEF) $(CCOV) -c $< -o $@

style:
	clang-format -n $(LIB_HEADER) $(LIB_DIR)* $(TEST_DIR)*

clean: extended_test_clean
	rm -rf $(OBJ_DIR) \
		   $(LIB_FILE) \
		   $(TEST_EXEC) \
		   $(RND_TEST_EXEC) \
		   $(TEST_EXEC).dSYM \
		   $(RND_TEST_EXEC).dSYM \
		   test.log  \
		   $(COV_DIR) \
		   *.gc* \
		   $(TEST_DIR)s21_tests.c

extended_test_clean: 
	rm -f ./add_test
	rm -f ./vova_test
	rm -f ./suite_main
	rm -f ./suite_1
	rm -f ./suite_2
	rm -f ./suite_3
	rm -f ./suite_4

rebuild: clean all

extended_test_rebuild: extended_test_clean extended_test
