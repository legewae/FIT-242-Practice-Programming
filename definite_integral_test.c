#include "definite_integral.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

double eps = 1e-4; //Точность до 4 знаков после запятой

int equals(double a, double b) {
    return fabs(a - b) < eps;
}

double linear_function(double x) {
    return x + 3;
}

double quadratic_function(double x) {
    return x * x;
}

void test_0() {
    double result = definite_integral(linear_function, -3, 3, 0);
    assert(equals(result, 0));
}

void test_1() {
    double result = definite_integral(linear_function, -3, 3, 2);
    assert(equals(result, 18));
}

void test_2() {
    double result = definite_integral(linear_function, -3, 3, 1000);
    assert(equals(result, 18));
}

void test_3() {
    double result = definite_integral(quadratic_function, -3, 3, 100); //Недостаточно шагов для получения точного результата

    assert(!equals(result,18));
}

void test_4() {
    double result = definite_integral(quadratic_function, -3, 3, 10000);
    assert(equals(result, 18));
}

int main() {
    test_0();
    test_1();
    test_2();
    test_3();
    test_4();

    return 0;
}