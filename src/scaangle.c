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

#include "config.h"

#include <stdlib.h>
#include <math.h>

#include "scaangle.h"

void
sca_angle_reduce (SCAAngle *angle)
{
	if (angle == NULL)
		return;

	*angle -= 360.0 * trunc (*angle / 360.0);
}

SCAAngle
sca_angle_from_degrees (int	degrees,
			int	arcmins,
			int	arcsecs,
			double	marcsecs)
{
	SCAAngle ret;

	ret = (double) abs (degrees)
	       + ((double) abs (arcmins) + ((double) abs (arcsecs)
	       + (double) fabs (marcsecs) / 1000.0) / 60.0) / 60.0;

	if (degrees < 0 || arcmins < 0 || arcsecs < 0 || marcsecs < 0)
		ret = - (ret);

	return ret;
}

SCAAngle
sca_angle_from_hours (int	hours,
		      int	mins,
		      int	secs,
		      double	msecs)
{
	SCAAngle ret;

	ret = 15.0 * ((double) abs (hours)
		      + ((double) abs (mins) + ((double) abs (secs)
		      + (double) fabs (msecs) / 1000.0) / 60.0) / 60.0);

	if (hours < 0 || mins < 0 || secs < 0 || msecs < 0)
		ret = - (ret);

	return ret;
}

SCAAngle
sca_angle_from_radians (double rads)
{
	return rads * SCA_ANGLE_RAD_TO_DEG;
}

double
sca_angle_to_degrees (SCAAngle angle)
{
	sca_angle_reduce (&angle);

	return angle;
}

double
sca_angle_to_hours (SCAAngle angle)
{
	sca_angle_reduce (&angle);

	return angle / 15.0;
}

double
sca_angle_to_radians (SCAAngle angle)
{
	sca_angle_reduce (&angle);

	return angle * SCA_ANGLE_DEG_TO_RAD;
}

int
sca_angle_get_degrees (SCAAngle angle)
{
	sca_angle_reduce (&angle);

	return (int) angle;
}

int
sca_angle_get_arcmins (SCAAngle angle)
{
	int	ret;

	ret = (int) ((fabs (angle) - abs (sca_angle_get_degrees (angle))) * 60.0);

	if (angle < 0.0 && angle > -1.0)
		ret = - (ret);

	return ret;
}

int
sca_angle_get_arcsecs (SCAAngle angle)
{
	int	ret, d, m;

	d = abs (sca_angle_get_degrees (angle));
	m = abs (sca_angle_get_arcmins (angle));

	ret = (int) (60.0 * (60.0 * ((fabs) (angle) - d) - m));

	if (d == 0 && m == 0 && angle < 0.0)
		ret = - (ret);

	return ret;
}

double sca_angle_get_marcsecs (SCAAngle angle)
{
	int	d, m, s;
	double	ret;

	d = abs (sca_angle_get_degrees (angle));
	m = abs (sca_angle_get_arcmins (angle));
	s = abs (sca_angle_get_arcsecs (angle));

	ret = (1000.0 * (60.0 * (60.0 * (fabs (angle) - d) - m) - s));

	if (d == 0 && m == 0 && s == 0 && angle < 0.0)
		ret = - (ret);

	return ret;
}

int
sca_angle_get_hours (SCAAngle angle)
{
	sca_angle_reduce (&angle);

	return (int) (sca_angle_get_degrees (angle) / 15.0);
}

int
sca_angle_get_mins (SCAAngle angle)
{
	int	ret, h;
	double	hs;

	h	= abs (sca_angle_get_hours (angle));
	hs	= fabs (sca_angle_to_hours (angle));

	ret = (int) (60.0 * (hs - h));

	if (hs < 0.0 && hs > -1.0)
		ret = - (ret);

	return ret;
}

int
sca_angle_get_secs (SCAAngle angle)
{
	int	ret, h, m;
	double	hs;

	h	= abs (sca_angle_get_hours (angle));
	hs	= fabs (sca_angle_to_hours (angle));
	m	= abs (sca_angle_get_mins (angle));

	ret = (int) (60.0 * (60.0 * (hs - h) - m));

	if (h == 0 && m == 0 && angle < 0.0)
		ret = - (ret);

	return ret;
}

double
sca_angle_get_msecs (SCAAngle angle)
{
	int	h, m, s;
	double	ret, hs;

	h	= abs (sca_angle_get_hours (angle));
	hs	= fabs (sca_angle_to_hours (angle));
	m	= abs (sca_angle_get_mins (angle));
	s	= abs (sca_angle_get_secs (angle));

	ret = (1000.0 * (60.0 * (60.0 * (hs - h) - m) - s));

	if (h == 0 && m == 0 && s == 0 && angle < 0.0)
		ret = - (ret);

	return ret;
}

double
sca_angle_get_sin (SCAAngle angle)
{
	sca_angle_reduce (&angle);

	return sin (sca_angle_to_radians (angle));
}

double
sca_angle_get_cos (SCAAngle angle)
{
	sca_angle_reduce (&angle);

	return cos (sca_angle_to_radians (angle));
}

void
sca_angle_get_sincos (SCAAngle		angle,
		      double		*sin_out,
		      double		*cos_out)
{
	double rads;

	sca_angle_reduce (&angle);
	rads = sca_angle_to_radians (angle);

	if (sin_out != NULL)
		*sin_out = sin (rads);

	if (cos_out != NULL)
		*cos_out = cos (rads);
}

SCAAngle
sca_angle_from_decimal_degrees	(double	val)
{
	return val;
}


