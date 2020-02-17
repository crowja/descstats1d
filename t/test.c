#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "descstats1d.h"
#include "tinytest.h"


#ifdef COLOR_CODE
#undef COLOR_CODE
#endif
#define COLOR_CODE      0x1B
#ifdef COLOR_RED
#undef COLOR_RED
#endif
#define COLOR_RED       "[1;31m"
#ifdef COLOR_GREEN
#undef COLOR_GREEN
#endif
#define COLOR_GREEN     "[1;32m"
#ifdef COLOR_YELLOW
#undef COLOR_YELLOW
#endif
#define COLOR_YELLOW    "[1;33m"
#ifdef COLOR_RESET
#undef COLOR_RESET
#endif
#define COLOR_RESET     "[0m"

static void
printf_test_name(char *name, char *info)
{
   printf("%c%s%s%c%s", COLOR_CODE, COLOR_YELLOW, name, COLOR_CODE, COLOR_RESET);

   if (NULL != info)
      printf(" [%s]\n", info);
   else
      printf("\n");
}

static void
test_cmean(void)
{
   double      x[9] = { 4, 3, 2, 1, 0, -1, -2, -3, -4 };
   double      y[8] = { 4, 3, 2, 1, -1, -2, -3, -4 };
   double      z[8] = { 1, -2, 3, -4, 4, -3, 2, -1 };
   double     *wrk = malloc(9 * sizeof(double));
   double      mean, var;

   printf_test_name("test_cmean()", NULL);

   descstats1d_cmean(9, x, wrk, &mean, &var);
   ASSERT("cmean x test mean", fabs(mean - 0.0) < 4 * DBL_EPSILON);
   ASSERT("cmean x test var ", fabs(var - 28.0 / 7) < 4 * DBL_EPSILON);

   descstats1d_cmean(8, y, wrk, &mean, &var);
   ASSERT("cmean y test mean", fabs(mean - 0.0) < 4 * DBL_EPSILON);
   ASSERT("cmean y test var ", fabs(var - 28.0 / 6) < 4 * DBL_EPSILON);

   descstats1d_cmean(8, z, wrk, &mean, &var);
   ASSERT("cmean shuffled y test mean", fabs(mean - 0.0) < 4 * DBL_EPSILON);
   ASSERT("cmean shuffled y test var ", fabs(var - 28.0 / 6) < 4 * DBL_EPSILON);

   free(wrk);
}

static void
test_mean(void)
{
   double      x[9] = { 4, 3, 2, 1, 0, -1, -2, -3, -4 };
   double      y[8] = { 4, 3, 2, 1, -1, -2, -3, -4 };
   double      mean, var;

   printf_test_name("test_mean()", NULL);

   descstats1d_mean(9, x, &mean, &var);
   ASSERT("mean x test mean", fabs(mean - 0.0) < 4 * DBL_EPSILON);
   ASSERT("mean x test var ", fabs(var - 60.0 / 8) < 4 * DBL_EPSILON);

   descstats1d_mean(8, y, &mean, &var);
   ASSERT("mean y test mean", fabs(mean - 0.0) < 4 * DBL_EPSILON);
   ASSERT("mean y test var ", fabs(var - 60.0 / 7) < 4 * DBL_EPSILON);
}

static void
test_median(void)
{
   double      x[9] = { 4, 3, 2, 1, 0, -1, -2, -3, -4 };
   double      y[8] = { 4, 3, 2, 1, -1, -2, -3, -4 };
   double      median, mad;
   double     *wrk = malloc(9 * sizeof(double));

   printf_test_name("test_median()", NULL);

   descstats1d_median(9, x, wrk, &median, &mad, 0);
   ASSERT("median x test median", fabs(median - 0.0) < 4 * DBL_EPSILON);
   ASSERT("median x test mad   ", fabs(mad - 2.0) < 4 * DBL_EPSILON);

   descstats1d_median(8, y, wrk, &median, &mad, 0);
   ASSERT("median y test median", fabs(median - 0.0) < 4 * DBL_EPSILON);
   ASSERT("median y test mad   ", fabs(mad - 2.5) < 4 * DBL_EPSILON);

   free(wrk);
}

static void
test_min_max(void)
{
   int         i;
   double     *x = malloc(sizeof(double) * 10000);
   double      max, min;

   printf_test_name("test_min_max()", NULL);

   for (i = 0; i < 10000; i++)
      x[i] = 0.5 * (i % 5 - 2);

   descstats1d_min_max(10000, x, &min, &max);

   ASSERT(0, (min == -1) && (max == 1));

   free(x);
}

static void
test_order(void)
{
   double      x[9] = { 4, 3, 2, 1, 0, -1, -2, -3, -4 };

   printf_test_name("test_order()", NULL);

   descstats1d_order(9, x);

#if 0
   {
      int         i;
      for (i = 0; i < 9; i++)
         printf("\t%f\n", x[i]);
   }
#endif

   ASSERT_EQUALS(-4, x[0]);
   ASSERT_EQUALS(0, x[4]);
   ASSERT_EQUALS(4, x[8]);
}

#if 0                                            /* 12 yy */
static void
test_stub(void)
{
   int         i;
   double      x[9] = { 4, 3, 2, 1, 0, -1, -2, -3, -4 };

   printf_test_name("test_order()", NULL);

   descstats1d_order(9, x);

   ASSERT_EQUALS(-4, x[0]);
}
#endif

int
main(void)
{
   printf("%s\n", descstats1d_version());

   RUN(test_cmean);
   RUN(test_mean);
   RUN(test_median);
   RUN(test_min_max);
   RUN(test_order);

   return TEST_REPORT();
}
