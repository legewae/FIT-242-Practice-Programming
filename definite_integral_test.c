#include "definite_integral.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

double eps = 1e-4;

int equals(double a, double b) {
    return fabs(a - b) < eps;
}

double linear_function(double x) {
    return x + 3;
}

double quadratic_function(double x) {
    return x * x;
}

void test_0_steps() {
    double result = definite_integral(linear_function, -3, 3, 0);
    assert(equals(result, 0));
}

void test_linear_2_steps() {
    double result = definite_integral(linear_function, -3, 3, 2);
    assert(equals(result, 18));
}

void test_linear_1000_steps() {
    double result = definite_integral(linear_function, -3, 3, 1000);
    assert(equals(result, 18));
}

void test_quadratic_low_steps() {
    double result = definite_integral(quadratic_function, -3, 3, 100);

    assert(!equals(result,18));
}

void test_quadratic_many_steps() {
    double result = definite_integral(quadratic_function, -3, 3, 10000);
    assert(equals(result, 18));
}

int main() {
    test_0_steps();
    test_linear_2_steps();
    test_linear_1000_steps();
    test_quadratic_low_steps();
    test_quadratic_many_steps();

    return 0;
}
