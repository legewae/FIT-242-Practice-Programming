clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

fmt_mac:
	find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -style=LLVM -i
#/-----linear_allocator-----/#
linear_allocator.o: linear_allocator.c linear_allocator.h
	gcc -g -c linear_allocator.c -o linear_allocator.o

linear_allocator.a: linear_allocator.o
	ar rc linear_allocator.a linear_allocator.o

linear_allocator_test.o: linear_allocator_test.c linear_allocator.h
	gcc -g -c linear_allocator_test.c -o linear_allocator_test.o

linear_allocator_test: linear_allocator_test.o linear_allocator.a
	gcc -g -o linear_allocator_test linear_allocator_test.o linear_allocator.a -lm
#/-----linear_allocator-----/#

test: linear_allocator_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "Running $$test"; \
		         ./$$test || exit 1; \
		echo ""; \
	done
