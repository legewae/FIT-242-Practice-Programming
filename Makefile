clear:
	rm -rf *.o *.a *_test

check_fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"` --dry-run --Werror

fmt:
	clang-format -style=LLVM -i `find -regex ".+\.[ch]"`

fmt_mac:
	find . -type f \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -style=LLVM -i

#/-----linked_list-----/#
linked_list.o: linked_list.c linked_list.h
	gcc -g -c linked_list.c -o linked_list.o

linked_list.a: linked_list.o
	ar rc linked_list.a linked_list.o

linked_list_test.o: linked_list_test.c linked_list.h
	gcc -g -c linked_list_test.c -o linked_list_test.o

linked_list_test: linked_list_test.o linked_list.a
	gcc -g -o linked_list_test linked_list_test.o linked_list.a -lm
#/---------------------/#

test: linked_list_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "Running $$test"; \
		         ./$$test || exit 1; \
		echo ""; \
	done
