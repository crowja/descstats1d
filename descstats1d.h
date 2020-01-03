/**
 *  @file descstats1d.h
 *  @version 0.2.0-dev0
 *  @date Thu Jan  2 19:54:30 CST 2020
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#ifndef _DESCSTATS_H_
#define _DESCSTATS_H_

#ifdef  _PACKAGE_NAME
#undef  _PACKAGE_NAME
#endif
#define _PACKAGE_NAME "descstats1d"


/**
 *  @brief FIXME Example function.
 *  @details FIXME longer description here ...
 *  @param cp [in] Pointer to a string.
 */

/**
 *  @brief FIXME Example function.
 *  @details FIXME longer description here ...
 *  @param cp [in] Pointer to a string.
 */

int         descstats1d_cmean(unsigned len, double *x, double *wrk, double *mean,
                              double *var);

/**
 *  @brief FIXME Example function.
 *  @details FIXME longer description here ...
 *  @param cp [in] Pointer to a string.
 */
int         descstats1d_min_max(const unsigned len, const double *x, double *min,
                                double *max);

/**
 *  @brief FIXME Example function.
 *  @details FIXME longer description here ...
 *  @param cp [in] Pointer to a string.
 */
void        descstats1d_order(const unsigned len, double *x);

/**
 *  @brief FIXME Example function.
 *  @details FIXME longer description here ...
 *  @param cp [in] Pointer to a string.
 */
int         descstats1d_mean(unsigned len, double *x, double *mean, double *var);

/**
 *  @brief FIXME Example function.
 *  @details FIXME longer description here ...
 *  @param median [out] Sample median.
 *  @param mad [out] Sample median absolute deviation (MAD).
 *  @param scale_mad [in] 0 for no scaling of MAD, otherwise scale by 0.67... to
 *  make it comparable to unity when the input is standard normal.
 */

int         descstats1d_median(unsigned len, double *x, double *wrk, double *median,
                               double *mad, int scale_mad);
/**
 *  @brief Return the version of this package.
 *  @details FIXME longer description here ...
 */

const char *descstats1d_version(void);

#endif
