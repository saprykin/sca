/*
 * Copyright (C) 2011 Alexander Saprykin <xelfium@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA.
 */

/**
 * @file scamisc.h
 * @brief Miscellaneous functions
 * @author Alexander Saprykin
 *
 */

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCAMISC_H__
#define __SCAMISC_H__

#include <math.h>

#include <scamacros.h>

SCA_BEGIN_DECLS

/**
 * @brief Interpolates the function by three other values.
 * @param x Abscissae (function arguments) values. These values
 * MUST be EQUALLY spaced, or results may be incorrect (with low accuracy).
 * The x[1] value is considered to be the interpolation center.
 * @param y Function values.
 * @param xval Abscissae value for which function should be interpolated.
 * @param y_out Output interpolated result.
 * @return 0 in case of success, -1 otherwise.
 * @note All the @a x and the corresponding @a y values MUST
 * be sorted in inscreasing order.
 * @since 0.0.1
 */
int
sca_misc_interpolate_three (double	x[3],
			    double	y[3],
			    double	xval,
			    double	*y_out);

/**
 * @brief Interpolates the function by five other values.
 * @param x Abscissae (function arguments) values. These values
 * MUST be EQUALLY spaced, or results may be incorrect (with low accuracy).
 * The x[2] value is considered to be the interpolation center.
 * @param y Function values.
 * @param xval Abscissae value for which function should be interpolated.
 * @param y_out Output interpolated result.
 * @return 0 in case of success, -1 otherwise.
 * @note All the @a x and the corresponding @a y values MUST
 * be sorted in inscreasing order.
 * @since 0.0.1
 */
int
sca_misc_interpolate_five (double	x[5],
			   double	y[5],
			   double	xval,
			   double	*y_out);

SCA_END_DECLS

#endif /* __SCAMISC_H__ */

