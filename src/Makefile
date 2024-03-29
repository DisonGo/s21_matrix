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
Flags 			= -std=c11 -Werror -Wall -Wextra
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
	$(gcc) $(ADD_LIB) -I${LIB_INC_DIR} -I${ADD_INC_DIR} $< -c -o $@

$(ADD_O_DIR)/%.o: $(ADD_SRC_DIR)/%.c
	$(gcc) $(ADD_LIB) -I${LIB_INC_DIR} -I${ADD_INC_DIR} $< -c -o $@

clear:
	clear

clean:
	rm -rf $(BUILD_DIR)/$(PROJECT_NAME).a test *.out
	rm -rf $(ODIR)/*.o $(ODIR)/*.gc*
	rm -rf $(ODIR)/*/*.o $(ODIR)/*/*.gc*
	rm -rf $(ODIR)/*/*/*.o $(ODIR)/*/*/*.gc*
	rm -rf ./gcov/*.o ./gcov/*.gc*
	rm -rf ./*.gc*
	rm -rf ./*.dSYM
	rm -rf report*

obj: $(LIB_OBJ) $(ADD_OBJ)

no_warns:
	$(eval gcc = gcc)

clang:
	clang-format --style=Google -n ${LIB_SRC_DIR}/*.c ${ADD_SRC_DIR}/*.c ${LIB_INC_DIR}/*.h ${ADD_INC_DIR}/*.h

clang-replace:
	clang-format --style=Google -i ${LIB_SRC_DIR}/*.c ${ADD_SRC_DIR}/*.c ${LIB_INC_DIR}/*.h ${ADD_INC_DIR}/*.h

$(BUILD_DIR)/$(PROJECT_NAME).a: obj
	ar rcs $@ $(LIB_O_DIR)/*.o $(ADD_O_DIR)/*.o
$(PROJECT_NAME).a: $(BUILD_DIR)/$(PROJECT_NAME).a
set_debug_gcc:
	$(eval gcc += -g)
	@echo $(PROJECT_NAME):Debug build

set_report_gcc:
	$(eval gcc += -fprofile-arcs -ftest-coverage -fPIC)
	@echo $(PROJECT_NAME):Check build

test: $(TEST_SRC) $(BUILD_DIR)/$(PROJECT_NAME).a
	$(gcc) -g -I${LIB_INC_DIR} -I${ADD_INC_DIR} $^ -o $@ $(TEST_CHECK_F) $(ADD_LIB)
	./test
gcov_report: clean set_report_gcc test
	./test
	gcov *.c ${LIB_SRC_DIR}/*.c -o $(ODIR)/*
	mv *.gc* ./gcov
	mv $(ODIR)/*/*.gc* $(ODIR)/*/*/*.gc*  ./gcov
	lcov -t ./gcov -o report.info -c -d ./gcov
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html

.PHONY: clean obj clear $(PROJECT_NAME) test clang-replace all $(BUILD_DIR)/$(PROJECT_NAME).a set_debug_gcc set_report_gcc gcov_report