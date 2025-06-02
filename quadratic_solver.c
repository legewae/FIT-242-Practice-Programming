#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "quadratic_solver.h"

int quadratic_solver(double a, double b, double c, double eps, double **roots){

   if(fabs(a)<eps) {
      if(roots) *roots = NULL;
	  return NOT_QUADRATIC_EQUATION; //Не является квадратичным уравнением
   }

   //Каждый коэффициент делим для легкости вычисления
   b = b / a;
   c = c / a;

   double disc = b * b - 4 * c; //Дискриминант
   if(disc < -eps) {
	  *roots = NULL;
	  return NO_ROOTS; //Нет корней
   } else if(fabs(disc) <= eps) { //Дискриминант равен(почти) нулю
	  *roots = (double *)malloc(1  *sizeof(double)); //Корень 1, выделяем память на 1
	  (*roots)[0] = -b / 2; //Один корень
	  return ONE_ROOT;
   } else {
	  *roots = (double *)malloc(2 * sizeof(double)); //Корня 2, выделяем память на 2

	  (*roots)[0] = (-b - sqrt(disc)) / 2; //Первый корень
	  (*roots)[1] = (-b + sqrt(disc)) / 2; //Второй корень
	  //Корни по возрастанию
	  return TWO_ROOTS;
   }
}