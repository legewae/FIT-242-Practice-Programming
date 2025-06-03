#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "quadratic_solver.h"

int quadratic_solver(double a, double b, double c, double eps, double **roots){

   if(fabs(a)<eps) {
      if(roots) *roots = NULL;
	  return NOT_QUADRATIC_EQUATION;
   }

  
   b = b / a;
   c = c / a;

   double disc = b * b - 4 * c;
   if(disc < -eps) {
	  *roots = NULL;
	  return NO_ROOTS;
   } else if(fabs(disc) <= eps) {
	  *roots = (double *)malloc(1  *sizeof(double));
	  (*roots)[0] = -b / 2;
	  return ONE_ROOT;
   } else {
	  *roots = (double *)malloc(2 * sizeof(double));

	  (*roots)[0] = (-b - sqrt(disc)) / 2;
	  (*roots)[1] = (-b + sqrt(disc)) / 2;
	  return TWO_ROOTS;
   }
}
