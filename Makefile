clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

fmt_mac:
	find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -style=LLVM -i

#/-----hashtable-----/#
pool_allocator.o: pool_allocator.c pool_allocator.h
	gcc -g -c pool_allocator.c -o pool_allocator.o

pool_allocator.a: pool_allocator.o
	ar rc pool_allocator.a pool_allocator.o

hashtable.o: hashtable.c hashtable.h pool_allocator.h
	gcc -g -c hashtable.c -o hashtable.o

hashtable.a: hashtable.o pool_allocator.o
	ar rc hashtable.a hashtable.o pool_allocator.o

hashtable_test.o: hashtable_test.c hashtable.h pool_allocator.h
	gcc -g -c hashtable_test.c -o hashtable_test.o

hashtable_test: hashtable_test.o hashtable.a pool_allocator.a
	gcc -g -o hashtable_test hashtable_test.o hashtable.a pool_allocator.a -lm
#/-----hashtable-----/#

test: hashtable_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "Running $$test"; \
		         ./$$test || exit 1; \
		echo ""; \
	done
