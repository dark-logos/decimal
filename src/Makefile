CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c11
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
CHECK_LIBS = -lcheck -lsubunit -lrt -lpthread -lm

TEST_DIR = tests

SOURCES = $(wildcard *.c)
STATIC_LIB = ./s21_decimal.a

TEST_EXECUTABLES = $(patsubst $(TEST_DIR)/test_%.c, $(TEST_DIR)/test_%, $(wildcard $(TEST_DIR)/test_*.c))


all: $(STATIC_LIB) tests

$(STATIC_LIB): clean
	$(CC) $(CFLAGS) -c $(SOURCES)
	ar rcs s21_decimal.a *.o
	ranlib s21_decimal.a

$(TEST_DIR)/test_%: $(TEST_DIR)/test_%.c $(STATIC_LIB)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SOURCES) $^ -o $@ $(CHECK_LIBS)

tests: $(TEST_EXECUTABLES)
	@for test in $(TEST_EXECUTABLES); do \
		./$$test || exit 1; \
	done
	
gcov_report: tests
	lcov --capture --directory . --output-file coverage.info --exclude "*s21_some_func.c*"
	genhtml coverage.info --output-directory ./coverage_report
	@xdg-open ./coverage_report/index.html

clean:
	rm -f *.o
	rm -f $(STATIC_LIB) $(TEST_EXECUTABLES) $(OBJ_DIR)/*.o coverage.info
	rm -f $(TEST_DIR)/*.gcno $(TEST_DIR)/*.gcda 
	rm -f *.gcno *.gcda $(STATIC_LIB_GCOV)
	rm -rf $(OBJ_DIR) coverage_report

.PHONY: all tests gcov_report clean
