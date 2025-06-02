#include "quadratic_solver.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

double eps = 1e-14; //10^-14, 14 после запятой

void test_zero(){
	double *roots = NULL;
	int result = quadratic_solver(0, 1, 1, eps, &roots);
	
	assert(result == NOT_QUADRATIC_EQUATION);
	free(roots);
}

void test_two_roots(){
	double *roots = NULL;
	int result = quadratic_solver(1, 0, -1, eps, &roots);

	assert(result == TWO_ROOTS);
	free(roots);
}

void test_one_root(){
	double *roots = NULL;
	int result = quadratic_solver(1, 0, 0, eps, &roots);
	
	assert(result == ONE_ROOT);
	free(roots);
}

void test_no_roots(){
	double *roots = NULL;
	int result = quadratic_solver(1, 0, 1, eps, &roots);
	assert(result==NO_ROOTS);
	free(roots);
}

void test_4_precision(){
	double* roots = NULL;
	eps = 1e-7;

	int result = quadratic_solver(1, 0, -1e-7, eps, &roots);
	assert(result == TWO_ROOTS);
}

void test_11_precision(){
	double* roots = NULL;
	eps = 1e-11;

	int result = quadratic_solver(1, -1e+10,-1, eps, &roots);
	assert(result == TWO_ROOTS);
}

void test_7_precision(){
	double* roots = NULL;
	eps = 1e-7;

	int result = quadratic_solver(1, 0, -1e-8, eps, &roots);
	assert(result == ONE_ROOT);
}

int main(){
	test_zero();
	test_two_roots();
	test_one_root();
	test_no_roots();
	test_4_precision();
	test_11_precision();
	test_7_precision();
	return 0;
}