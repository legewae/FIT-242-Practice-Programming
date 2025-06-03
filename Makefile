clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

fmt_mac:
	find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -style=LLVM -i
#/----definite-integral----/#
definite_integral.o: definite_integral.c definite_integral.h
	gcc -g -c definite_integral.c -o definite_integral.o

definite_integral.a: definite_integral.o
	ar rc definite_integral.a definite_integral.o

definite_integral_test.o: definite_integral_test.c definite_integral.h
	gcc -g -c definite_integral_test.c -o definite_integral_test.o

definite_integral_test: definite_integral_test.o definite_integral.a
	gcc -g -o definite_integral_test definite_integral_test.o definite_integral.a -lm
#/--------------------------/#
test: definite_integral_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "Running $$test"; \
		         ./$$test || exit 1; \
		echo ""; \
	done
