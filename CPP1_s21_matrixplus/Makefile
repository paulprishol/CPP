CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -I.
GTEST_FLAGS = -lgtest -lgtest_main -pthread

TEST_FILES := tests/*.cc
BUILD_DIR := build

all: clean s21_matrix_oop.a

s21_matrix_oop.a:
	$(CXX) $(CXXFLAGS) -c s21_matrix_oop.cc
	ar rcs s21_matrix_oop.a *.o
	rm *.o

test: s21_matrix_oop.a
	$(CXX) $(CXXFLAGS) s21_*.cc ./s21_matrix_oop.a $(TEST_FILES) $(GTEST_FLAGS) -o test
	./test

gcov_report: s21_matrix_oop.a
	$(CXX) $(CXXFLAGS) --coverage -O0 -g s21_*.cc ./s21_matrix_oop.a $(TEST_FILES) $(GTEST_FLAGS) -o gcov_test
	./gcov_test
	lcov -t "gcov-test" -o report.txt -c -d . --ignore-errors mismatch
	lcov --remove report.txt '/usr/*' -o report_filtered.txt
	genhtml -o report report_filtered.txt
	open ./report/index.html

clean:
	rm -rf *.a *.gch *.o *.gcno *.gcda gcov_test report*.txt report test

reduild:
	make clean
	make all

style_n:
	cp -n ../materials/linters/.clang-format .

	clang-format -style=Google -n *.cc
	clang-format -style=Google -n *.h

	clang-format -style=Google -n tests/*.cc
	clang-format -style=Google -n tests/*.h

style_i:
	cp -n ../materials/linters/.clang-format .

	clang-format -style=Google -i s21_*.cc
	clang-format -style=Google -i s21_*.h

	clang-format -style=Google -i tests/*.cc
	clang-format -style=Google -i tests/*.h

leaks:
	leaks --atExit -- ./test

val:
	valgrind --tool=memcheck --leak-check=yes ./test

cpp:
	cppcheck --language=c++ --enable=all --suppress=missingIncludeSystem *.cc tests/*.cc
