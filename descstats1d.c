/**
 *  @file descstats1d.c
 *  @version 0.1.0-dev0
 *  @date Thu Jan  2 19:54:30 CST 2020
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#include <stdlib.h>
#include <stdio.h>                               /* FIXME */
#include <math.h>
#include <float.h>
#include "descstats1d.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

/* Comparator used by descstats1d_order() */

static int
_compare_d(const void *x, const void *y)
{
   if (*(double *) x == *(double *) y)
      return 0;
   else
      return *(double *) x < *(double *) y ? -1 : 1;
}

static int
_median(const unsigned len, double *x, double *median)
{
   unsigned    j1, j2;

   if (len < 1)
      return 1;

   descstats1d_order(len, x);

   j1 = (len - 1) / 2;
   j2 = len / 2;

   *median = (x[j1] + x[j2]) / 2;

   return 0;
}

/*** descstats1d_cmean() ***/

int
descstats1d_cmean(unsigned len, double *x, double *wrk, double *mean, double *var)
{
   unsigned    i;
   unsigned    j2 = (0.90 + DBL_EPSILON) * len;
   unsigned    j1 = len - j2;
   double      sum0 = 0;
   double      sum1 = 0;
   double      sum2 = 0;

   for (i = 0; i < len; i++)
      wrk[i] = x[i];

   descstats1d_order(len, wrk);

   for (i = j1; i < j2; i++) {
      sum0 += 1;
      sum1 += wrk[i];
   }

   *mean = sum1 / (j2 - j1);

   for (i = j1; i < j2; i++)
      sum2 += pow(wrk[i] - *mean, 2);

   *var = sum2 / (j2 - j1);

   return 0;
}

/*** descstats1d_mean() ***/

int
descstats1d_mean(unsigned len, double *x, double *mean, double *var)
{
   unsigned    i;
   double      sum1 = 0;
   double      sum2 = 0;
   double      den = len < 2 ? 1 : len - 1;

   if (len < 1)
      return 0;

   for (i = 0; i < len; i++)
      sum1 += x[i];

   *mean = sum1 / len;

   for (i = 0; i < len; i++)
      sum2 += pow(x[i] - *mean, 2);

   *var = sum2 / den;

   return 0;
}

/*** descstats1d_median() ***/

int
descstats1d_median(unsigned len, double *x, double *wrk, double *median, double *mad,
                   int scale_mad)
{
   unsigned    i;

   if (len < 1)
      return 1;

   for (i = 0; i < len; i++)
      wrk[i] = x[i];

   _median(len, wrk, median);

   for (i = 0; i < len; i++)
      wrk[i] = fabs(x[i] - *median);

   _median(len, wrk, mad);

   if (scale_mad)
      *mad /= 0.6744897501960817e-00;

   return 0;
}

/*** descstats1d_min_max() ***/

int
descstats1d_min_max(const unsigned len, const double *x, double *min, double *max)
{
   unsigned    i;

   *max = -DBL_MAX;
   *min = +DBL_MAX;

   for (i = 0; i < len; i++) {
      *max = x[i] > *max ? x[i] : *max;
      *min = x[i] < *min ? x[i] : *min;
   }

   return 0;
}

/*** descstats1d_order() ***/

void
descstats1d_order(const unsigned len, double *x)
{
   qsort(x, len, sizeof(double), _compare_d);
}

/*** descstats1d_version() ***/

const char *
descstats1d_version(void)
{
   return "0.1.0-dev0";
}


#undef _IS_NULL
#undef _FREE
