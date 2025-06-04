clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

fmt_mac:
	find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -style=LLVM -i
#/-----pool_allocator-----/#
pool_allocator.o: pool_allocator.c pool_allocator.h
	gcc -g -c pool_allocator.c -o pool_allocator.o

pool_allocator.a: pool_allocator.o
	ar rc pool_allocator.a pool_allocator.o

pool_allocator_test.o: pool_allocator_test.c pool_allocator.h
	gcc -g -c pool_allocator_test.c -o pool_allocator_test.o

pool_allocator_test: pool_allocator_test.o pool_allocator.a
	gcc -g -o pool_allocator_test pool_allocator_test.o pool_allocator.a -lm
#/-----pool_allocator-----/#

test: pool_allocator_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "Running $$test"; \
		         ./$$test || exit 1; \
		echo ""; \
	done
