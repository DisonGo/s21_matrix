PROJECT_NAME	=s21_matrix
ODIR 			= obj
LIB_INC_DIR		= include
LIB_SRC_DIR		= source
LIB_O_DIR		= $(ODIR)/$(LIB_SRC_DIR)
ADD_SRC_DIR		= other/source
ADD_INC_DIR		= other/include
ADD_O_DIR		= $(ODIR)/$(ADD_SRC_DIR)

TESTS_DIR		= tests
BUILD_DIR		= ../build
UNAME_S 		:= $(shell uname -s)
TEST_SRC		= $(TESTS_DIR)/${PROJECT_NAME}_test.c
# -Werror -Wall -Wextra 
Flags 			= -std=c11
gcc 			= gcc $(Flags)
LIB_SOURCES		= $(shell find $(LIB_SRC_DIR) -name '*.c')
ADD_SOURCES		= $(shell find $(ADD_SRC_DIR) -name '*.c')
REPORT_FILES	= $(shell find . -name '*.gcno') $(shell find . -name '*.gcda')
INC				:= $(shell find $(LIB_INC_DIR) -name '*.h')
LIB_OBJ 		= $(patsubst %.c,$(ODIR)/%.o, $(LIB_SOURCES))
ADD_OBJ 		= $(patsubst %.c,$(ODIR)/%.o, $(ADD_SOURCES))

ifeq ($(UNAME_S),Linux)
	TEST_CHECK_F= -lcheck
	OPEN_CMD = xdg-open
	ADD_LIB = -lm -lrt -lpthread
endif

ifeq ($(UNAME_S),Darwin)
	TEST_CHECK_F= $(shell pkg-config --cflags --libs check)
	OPEN_CMD = open
	ADD_LIB =
endif

all: clear $(BUILD_DIR)/$(PROJECT_NAME).a

$(LIB_O_DIR)/%.o: $(LIB_SRC_DIR)/%.c
	$(gcc) $(ADD_LIB) -I${LIB_INC_DIR} $< -c -o $@

$(ADD_O_DIR)/%.o: $(ADD_SRC_DIR)/%.c
	$(gcc) $(ADD_LIB) -I${ADD_INC_DIR} $< -c -o $@

tests: clean
	$(eval gcc = 1)
	@echo $(ADD_OBJ)

clear:
	clear

clean:
	rm -rf $(BUILD_DIR)/$(PROJECT_NAME).a test *.out
	rm -rf $(ODIR)/*.o $(ODIR)/*.gc*
	rm -rf $(ODIR)/*/*.o $(ODIR)/*/*.gc*
	rm -rf $(ODIR)/*/*/*.o $(ODIR)/*/*/*.gc*
	rm -rf ./gcov/*.o ./gcov/*.gc*
	rm -rf ./*.gc*
	rm -rf report*

obj: $(LIB_OBJ) $(ADD_OBJ)

no_warns:
	$(eval gcc = gcc)

clang:
	clang-format --style=Google -n ./*.c ./*.h ${LIB_SRC_DIR}/*.c

clang-replace:
	clang-format --style=Google -i *.c *.h ${LIB_SRC_DIR}/*.c

$(BUILD_DIR)/$(PROJECT_NAME).a: obj
	ar rcs $(BUILD_DIR)/$@ $(LIB_O_DIR)/*.o $(ADD_O_DIR)/*.o

set_debug_gcc:
	$(eval gcc += -g)
	@echo s21_math:Debug build

set_report_gcc:
	$(eval gcc += -fprofile-arcs -ftest-coverage -fPIC)
	@echo s21_math:Check build

test: $(TEST_SRC) $(BUILD_DIR)/$(PROJECT_NAME).a
	$(gcc) $^ -o $@ $(TEST_CHECK_F) $(ADD_LIB)

gcov_report: clean set_report_gcc test
	./test
	gcov *.c ${LIB_SRC_DIR}/*.c -o $(ODIR)/*
	mv *.gcov ./gcov
	mv ./*.gc* $(ODIR)/*/*.gc* ./gcov
	lcov -t ./gcov -o report.info -c -d ./gcov
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html

.PHONY: clean obj clear $(PROJECT_NAME) test clang-replace all $(BUILD_DIR)/$(PROJECT_NAME).a set_debug_gcc set_report_gcc gcov_report