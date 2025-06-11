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

#/----definite-integral----/#
definite_integral.o: definite_integral.c definite_integral.h
	gcc -g -c definite_integral.c -o definite_integral.o

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
definite_integral.a: definite_integral.o
	ar rc definite_integral.a definite_integral.o

definite_integral_test.o: definite_integral_test.c definite_integral.h
	gcc -g -c definite_integral_test.c -o definite_integral_test.o

definite_integral_test: definite_integral_test.o definite_integral.a
	gcc -g -o definite_integral_test definite_integral_test.o definite_integral.a -lm

#/-----quadratic-----/#
quadratic_solver.o: quadratic_solver.c quadratic_solver.h
	gcc -g -c quadratic_solver.c -o quadratic_solver.o

quadratic_solver.a: quadratic_solver.o
	ar rc quadratic_solver.a quadratic_solver.o

quadratic_solver_test.o: quadratic_solver_test.c quadratic_solver.h
	gcc -g -c quadratic_solver_test.c -o quadratic_solver_test.o

quadratic_solver_test: quadratic_solver_test.o quadratic_solver.a
	gcc -g -o quadratic_solver_test quadratic_solver_test.o quadratic_solver.a -lm
#/--------------------/#

test: quadratic_solver_test definite_integral_test linked_list_test linear_allocator_test
	@for test in $(shell find . -maxdepth 1 -type f -regex '.*_test$$'); do \
		echo "Running $$test"; \
		         ./$$test || exit 1; \
		echo ""; \
	done
