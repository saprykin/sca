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

#include <scamisc.h>

#ifndef HAVE_TRUNC_DECL
#  include <math.h>
#  include <float.h>

double
trunc (double x)
{
	return (x >= 0.0) ? floor (x) : ceil (x);
}
#endif

int
sca_misc_interpolate_three (double	x[3],
			    double	y[3],
			    double	xval,
			    double	*y_out)
{
	double	factor;
	/* First degree diffs */
	double	diff_a, diff_b;
	/* Second degree diff */
	double	diff_c;
	double	norm;

	if (x == NULL || y == NULL || y_out == NULL)
		return -1;

	if (xval <= x[0] || xval >= x[2]) {
		SCA_WARNING ("SCAMisc", "Interpolating value is out of range.");
		return -1;
	}

	/* Find central abscissae value */
	norm  = fabs (x[1] - x[0]) > 1.0 ? fabs (x[1] - x[0]) : 1.0;
	factor = (xval - x[1]) / norm;

	if (factor > 0.5)
		SCA_WARNING ("SCAMisc", "Bad interpolating factor, results may have low accuracy");

	/* Perform interpolation */
	diff_a = y[1] - y[0];
	diff_b = y[2] - y[1];
	diff_c = diff_b - diff_a;

	*y_out = y[1] + (factor / 2) * (diff_a + diff_b + factor * diff_c);

	return 0;
}

int
sca_misc_interpolate_five (double	x[5],
			   double	y[5],
			   double	xval,
			   double	*y_out)
{
	double	factor;
	/* First degree diffs */
	double	diff_a, diff_b, diff_c, diff_d;
	/* Second degree diffs */
	double	diff_e, diff_f, diff_g;
	/* Third degree diffs */
	double	diff_h, diff_j;
	/* Forth degree diff */
	double	diff_k;
	double	norm;

	if (x == NULL || y == NULL || y_out == NULL)
		return -1;

	if (xval <= x[0] || xval >= x[4]) {
		SCA_WARNING ("SCAMisc", "Interpolating value is out of range.");
		return -1;
	}

	/* Find central value */
	norm = fabs (x[1] - x[0]) > 1.0 ? fabs (x[1] - x[0]) : 1.0;
	factor = (xval - x[2]) / norm;


	if (factor > 0.5)
		SCA_WARNING ("SCAMisc", "Bad interpolating factor, results may have low accuracy");

	/* Perform interpolation */
	diff_a = y[1] - y[0];
	diff_b = y[2] - y[1];
	diff_c = y[3] - y[2];
	diff_d = y[4] - y[3];

	diff_e = diff_b - diff_a;
	diff_f = diff_c - diff_b;
	diff_g = diff_d - diff_c;

	diff_h = diff_f - diff_e;
	diff_j = diff_g - diff_f;

	diff_k = diff_j - diff_h;

	*y_out = y[2] + factor * ((diff_b + diff_c) / 2 - (diff_h + diff_j) / 12)
			    + factor * factor * (diff_f / 2 - diff_k / 24)
			    + factor * factor * factor * ((diff_h + diff_j) / 12)
			    + factor * factor * factor * factor * (diff_k / 24);

	return 0;
}
