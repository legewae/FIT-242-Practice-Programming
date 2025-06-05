clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

fmt_mac:
	find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -style=LLVM -i

#/-----dynamic_array-----/#
linear_allocator.o: linear_allocator.c linear_allocator.h
	gcc -g -c linear_allocator.c -o linear_allocator.o

linear_allocator.a: linear_allocator.o
	ar rc linear_allocator.a linear_allocator.o

dynamic_array.o: dynamic_array.c dynamic_array.h linear_allocator.h
	gcc -g -c dynamic_array.c -o dynamic_array.o

dynamic_array.a: dynamic_array.o linear_allocator.o
	ar rc dynamic_array.a dynamic_array.o linear_allocator.o

dynamic_array_test.o: dynamic_array_test.c dynamic_array.h linear_allocator.h
	gcc -g -c dynamic_array_test.c -o dynamic_array_test.o

dynamic_array_test: dynamic_array_test.o dynamic_array.a linear_allocator.a
	gcc -g -o dynamic_array_test dynamic_array_test.o dynamic_array.a linear_allocator.a -lm
#/-----dynamic_array-----/#

test: dynamic_array_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "Running $$test"; \
		         ./$$test || exit 1; \
		echo ""; \
	done
