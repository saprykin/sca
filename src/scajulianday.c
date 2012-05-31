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

#include <math.h>
#include <stdlib.h>

#include <scajulianday.h>
#include <scaearth.h>
#include <scamisc.h>

static int
_sca_jd_is_gregorian_date (SCADate	*date)
{
	if (date->year > 1582)
		return 1;
	else if (date->year < 1582)
		return 0;
	else if (date->month > SCA_MONTH_OCTOBER)
		return 1;
	else if (date->month < SCA_MONTH_OCTOBER)
		return 0;
	else if (date->day >= 15.0)
		return 1;
	else
		return 0;
}

double
sca_jd_from_calendar_date (SCADate	*date)
{
	int	Y, M;
	int	A, B;
	double	D;

	if (date == NULL)
		return -1;

	if (date->year < -4712)
		return 0;

	D = date->day;

	if (date->month <= SCA_MONTH_FEBRUARY) {
		Y = date->year - 1;
		M = date->month + 12;
	} else {
		Y = date->year;
		M = date->month;
	}

	B = 0;
	if (_sca_jd_is_gregorian_date (date)) {
		A = Y / 100;
		B = 2 - A + (A / 4);
	}

	return trunc (365.25 * (Y + 4716.0)) + trunc (30.6001 * (M + 1)) + D + B - 1524.5;
}

int
sca_jd_to_calendar_date (double		jd,
			 SCADate	*date)
{
	double	A, B, C, D, E, F;
	int	alpha, Z;

	if (date == NULL || jd < 0)
		return -1;

	jd += 0.5;
	Z = (int)(trunc (jd) + 0.1);
	F = jd - Z;

	if (Z < 2299161)
		A = Z;
	else {
		alpha = (int) (trunc ((Z - 1867216.25) / 36524.25) + 0.1);
		A = Z + 1 + alpha - trunc (alpha / 4);
	}

	B = A + 1524.0;
	C = trunc ((B - 122.1) / 365.25);
	D = trunc (365.25 * C);
	E = trunc ((B - D) / 30.6001);

	date->day = B - D - trunc (30.6001 * E) + F;

	if (E < 14)
		date->month = (SCAMonth) ((int) E - 1);
	else
		date->month = (SCAMonth) ((int) E - 13);

	if (date->month > SCA_MONTH_FEBRUARY)
		date->year = (int) C - 4716;
	else
		date->year = (int) C - 4715;

	return 0;
}

int
sca_jd_get_weekday (double	jd,
		    SCAWeekDay	*weekday)
{
	if (jd < 0 || weekday == NULL)
		return -1;

	jd += 1.5;
	
	*weekday = (SCAWeekDay) (jd - trunc (jd / 7.0) * 7.0);

	return 0;
}

int
sca_jd_get_day_of_year (double	jd)
{
	SCADate		date;
	int		K;

	if (jd < 0)
		return -1;

	sca_jd_to_calendar_date (jd, &date);

	if ((date.year % 400 != 0) && (date.year % 4 == 0))
		K = 1;
	else
		K = 2;

	return (int) (trunc (275.0 * (int) date.month / 9.0) - K * trunc (((int) date.month + 9.0) / 12.0) + date.day - 30.0);
}

double
sca_jd_from_day_of_year (int	year,
			 int	num)
{
	SCADate		date;
	int		K;

	if (num <= 0 || year < -4712)
		return -1;

	if ((year % 400 != 0) && (year % 4 == 0))
		K = 1;
	else
		K = 2;

	if (num < 32)
		date.month = (SCAMonth) 1;
	else
		date.month = (SCAMonth) (9.0 * (K + num) / 275.0 + 0.98);

	date.day	= num - trunc (275.0 * (int) date.month / 9.0) + K * trunc (((int) date.month + 9.0) / 12.0) + 30.0;
	date.year	= year;

	return sca_jd_from_calendar_date (&date);
}

int
sca_jd_get_sidereal_time (double jd, SCAAngle *sidereal)
{
	double		t;
	SCAAngle	theta0, nut = 0, obl = 0;

	if (jd < 0 || sidereal == NULL)
		return -1;

	t	= sca_jd_get_centuries_2000 (jd);
	theta0	= sca_angle_from_decimal_degrees (280.46061837 + 360.98564736629 * (jd - SCA_JD_EPOCH_2000)
						 + 0.000387933 * t * t - (t * t * t) / 38710000.0);

	sca_earth_get_nutation (jd, &nut, NULL);
	sca_earth_get_ecliptic_obliquity (jd, &obl);
	
	*sidereal = theta0 + sca_angle_from_degrees (0, 0, 0, nut * 3600.0 * sca_angle_get_cos (obl) * 1000.0);
	sca_angle_reduce (sidereal);

	return 0;
}

double
sca_jd_get_centuries_2000 (double jd)
{
	return (jd - SCA_JD_EPOCH_2000) / 36525.0;
}

double
sca_jd_get_millenia_2000 (double jd)
{
	return (jd - SCA_JD_EPOCH_2000) / 365250.0;
}

double
sca_jd_get_dynamic_time (double jd)
{
	/* Stephenson and Houlden approximation formulae */
	 return (-15 + (jd - 2382148.0) * (jd - 2382148.0) / 41048480.0) / SCA_SECS_IN_DAY;
}

