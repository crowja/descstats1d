#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include "descstats1d.h"
#include "tinytest.h"
#include "tinyhelp.h"

static void
test_cmean(void)
{
   double      x[9] = { 4, 3, 2, 1, 0, -1, -2, -3, -4 };
   double      y[8] = { 4, 3, 2, 1, -1, -2, -3, -4 };
   double      z[8] = { 1, -2, 3, -4, 4, -3, 2, -1 };
   double     *wrk = malloc(9 * sizeof(double));
   double      mean, var;

   fprintf_test_info(stdout, "test_cmean", NULL);
   descstats1d_cmean(9, x, wrk, &mean, &var);
   ASSERT_DOUBLE_EQUALS(0.0, mean);
   ASSERT_DOUBLE_EQUALS(28.0 / 7, var);
   descstats1d_cmean(8, y, wrk, &mean, &var);
   ASSERT_DOUBLE_EQUALS(0.0, mean);
   ASSERT_DOUBLE_EQUALS(28.0 / 6, var);
   descstats1d_cmean(8, z, wrk, &mean, &var);
   ASSERT_DOUBLE_EQUALS(0.0, mean);
   ASSERT_DOUBLE_EQUALS(28.0 / 6, var);
   free(wrk);
}

static void
test_mean(void)
{
   double      x[9] = { 4, 3, 2, 1, 0, -1, -2, -3, -4 };
   double      y[8] = { 4, 3, 2, 1, -1, -2, -3, -4 };
   double      mean, var;

   fprintf_test_info(stdout, "test_mean", NULL);
   descstats1d_mean(9, x, &mean, &var);
   ASSERT_DOUBLE_EQUALS(0.0, mean);
   ASSERT_DOUBLE_EQUALS(60.0 / 8, var);
   descstats1d_mean(8, y, &mean, &var);
   ASSERT_DOUBLE_EQUALS(0.0, mean);
   ASSERT_DOUBLE_EQUALS(60.0 / 7, var);
}

static void
test_median(void)
{
   double      x[9] = { 4, 3, 2, 1, 0, -1, -2, -3, -4 };
   double      y[8] = { 4, 3, 2, 1, -1, -2, -3, -4 };
   double      median, mad;
   double     *wrk = malloc(9 * sizeof(double));

   fprintf_test_info(stdout, "test_median", NULL);
   descstats1d_median(9, x, wrk, &median, &mad, 0);
   ASSERT_DOUBLE_EQUALS(0.0, median);
   ASSERT_DOUBLE_EQUALS(2.0, mad);
   descstats1d_median(8, y, wrk, &median, &mad, 0);
   ASSERT_DOUBLE_EQUALS(0.0, median);
   ASSERT_DOUBLE_EQUALS(2.5, mad);
   free(wrk);
}

static void
test_min_max(void)
{
   int         i;
   double     *x = malloc(sizeof(double) * 10000);
   double      max, min;

   fprintf_test_info(stdout, "test_min_max", NULL);
   for (i = 0; i < 10000; i++)
      x[i] = 0.5 * (i % 5 - 2);
   descstats1d_min_max(10000, x, &min, &max);
   ASSERT_EQUALS(-1.0, min);
   ASSERT_EQUALS(1.0, max);
   free(x);
}

static void
test_order(void)
{
   double      x[9] = { 4, 3, 2, 1, 0, -1, -2, -3, -4 };

   fprintf_test_info(stdout, "test_order", NULL);
   descstats1d_order(9, x);
   ASSERT_DOUBLE_EQUALS(-4.0, x[0]);
   ASSERT_DOUBLE_EQUALS(0.0, x[4]);
   ASSERT_DOUBLE_EQUALS(4.0, x[8]);
}

#if 0                                            /* 10 yy */
static void
test_stub(void)
{
   int         i;
   double      x[9] = { 4, 3, 2, 1, 0, -1, -2, -3, -4 };

   fprintf_test_info(stderr, "test_order", NULL);
   descstats1d_order(9, x);
   ASSERT_DOUBLE_EQUALS(-4.0, x[0]);
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
