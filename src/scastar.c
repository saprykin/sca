/*
 * Copyright (C) 2011-2013 Alexander Saprykin <xelfium@gmail.com>
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

#include "scastar.h"
#include "scaearth.h"
#include "scaprivate.h"
#include "scasun.h"

/**
 * @brief Performs precession in equatorial coordinates.
 * @param star Star for precession.
 * @param jd Julian Day corresponding to calculation instance.
 * @since 0.0.1
 */
static void
_sca_star_precess (SCAStar *star, double jd)
{
	double		t;
	double		A, B, C;
	double		sin_theta, cos_theta;
	double		sin_dec0, cos_dec0;
	double		ra, dec;
	SCAAngle	zeta, z, theta;

	/* Julian years between epoches */
	t = sca_jd_get_centuries_2000 (jd) * 100.0;
	
	/* 1. Calculate proper motion */
	star->ra	+= t * star->ra_motion;
	star->dec	+= t * star->dec_motion;

	sca_angle_reduce (&star->ra);
	sca_angle_reduce (&star->dec);

	/* Centuries since J2000 epoch */
	t /= 100.0;

	/* 2. Reduce epoch to given date */
	zeta	= sca_angle_from_degrees (0, 0, 0, (2306.2181 * t + 0.30188 * t * t + 0.017998 * t * t * t) * 1000.0);
	z	= sca_angle_from_degrees (0, 0, 0, (2306.2181 * t + 1.09468 * t * t + 0.018203 * t * t * t) * 1000.0);
	theta	= sca_angle_from_degrees (0, 0, 0, (2004.3109 * t - 0.42665 * t * t - 0.041833 * t * t * t) * 1000.0);

	sca_angle_get_sincos (theta, &sin_theta, &cos_theta);
	sca_angle_get_sincos (star->dec, &sin_dec0, &cos_dec0);

	A = cos_dec0 * sca_angle_get_sin (star->ra + zeta);
	B = cos_theta * cos_dec0 * sca_angle_get_cos (star->ra + zeta) - sin_theta * sin_dec0;
	C = sin_theta * cos_dec0 * sca_angle_get_cos (star->ra + zeta) + cos_theta * sin_dec0;

	ra = atan2 (A, B) * SCA_ANGLE_RAD_TO_DEG + z;

	/* If star is close to celestial pole */
	if (fabs (star->dec2000) > 80.0)
		dec = acos (sqrt (A * A + B * B)) * SCA_ANGLE_RAD_TO_DEG;
	else
		dec = asin (C) * SCA_ANGLE_RAD_TO_DEG;

	star->ra	= ra;
	star->dec	= dec;
}

/**
 * @brief Calculates aberration (in ecliptical coordinates).
 * @param star Star to perform calculation for.
 * @param jd Julian Day corresponding to calculation instance.
 * @param abr_lon Output aberration in ecliptical longitude.
 * @param abr_lat Output aberration in ecliptical latitude.
 * @since 0.0.1
 */
static void
_sca_star_get_aberration_ecliptic (SCAStar *star, double jd, SCAAngle *abr_lon, SCAAngle *abr_lat)
{
	double		t, e;
	SCAAngle	K, theta;
	SCAAngle	lon, lat;
	SCAAngle	pi;

	K = sca_earth_get_aberration_constant ();
	t = sca_jd_get_centuries_2000 (jd);

	sca_earth_get_orbit_eccentricity (jd, &e);
	sca_earth_get_perihelion_longitude (jd, &pi);
	sca_sun_get_true_longitude (jd, &theta);

	sca_coordinates_equatorial_to_ecliptic (jd, star->ra, star->dec, &lon, &lat);

	if (abr_lon != NULL)
		*abr_lon = ((-K) * sca_angle_get_cos (theta - lon)
			   + e * K * sca_angle_get_cos (pi - lon)) / sca_angle_get_cos (lat);

	if (abr_lat != NULL)
		*abr_lat = (-K) * sca_angle_get_sin (lat) * (sca_angle_get_sin (theta - lon)
		- e * sca_angle_get_sin (pi - lon));
}

/**
 * @brief Calculates aberration (in equatorial coordinates).
 * @param star Star to perform calculation for.
 * @param jd Julian Day corresponding to calculation instance.
 * @param abr_ra Output aberration in right ascension.
 * @param abr_dec Output aberration in declination.
 * @since 0.0.1
 */
static void
_sca_star_get_aberration_equatorial (SCAStar *star, double jd, SCAAngle *abr_ra, SCAAngle *abr_dec)
{
	double		t, e;
	SCAAngle	K, theta;
	SCAAngle	pi;
	SCAAngle	obl;
	double		cos_ra, sin_ra, cos_dec, sin_dec;
	double		cos_pi, sin_pi, cos_theta, sin_theta;
	double		cos_obl;

	sca_earth_get_ecliptic_obliquity (jd, &obl);

	cos_obl	= sca_angle_get_cos (obl);
	K	= sca_earth_get_aberration_constant ();
	t	= sca_jd_get_centuries_2000 (jd);

	sca_sun_get_true_longitude (jd, &theta);
	sca_earth_get_orbit_eccentricity (jd, &e);
	sca_earth_get_perihelion_longitude (jd, &pi);

	sca_angle_get_sincos (star->ra, &sin_ra, &cos_ra);
	sca_angle_get_sincos (star->dec, &sin_dec, &cos_dec);
	sca_angle_get_sincos (pi, &sin_pi, &cos_pi);
	sca_angle_get_sincos (theta, &sin_theta, &cos_theta);

	if (abr_ra != NULL)
		*abr_ra = (-K) * (cos_ra * cos_theta * cos_obl + sin_ra * sin_theta) / cos_dec
			   + e * K * (cos_ra * cos_pi * cos_obl + sin_ra * sin_pi) / cos_dec;

	if (abr_dec != NULL)
		*abr_dec = (-K) * (cos_theta * cos_obl * (tan (sca_angle_to_radians (obl)) * cos_dec - sin_ra * sin_dec)
				   + cos_ra * sin_dec * sin_theta)
			    + e * K * (cos_pi * cos_obl * (tan (sca_angle_to_radians (obl)) * cos_dec - sin_ra * sin_dec)
				       + cos_ra * sin_dec * sin_pi);
}

/**
 * @brief Calculates nutation in ecliptical coordinates.
 * @param star Star to perform calculation for.
 * @param jd Julian Day corresponding to calculation instance.
 * @param nut_lon Output nutation in longitude.
 * @param nut_lat Output nutation in latitude.
 * @since 0.0.1
 */
static void
_sca_star_get_nutation_ecliptic (SCAStar *star, double jd, SCAAngle *nut_lon, SCAAngle *nut_lat)
{
	if (nut_lon != NULL)
		sca_earth_get_nutation (jd, nut_lon, NULL);

	if (nut_lat != NULL)
		*nut_lat = 0.0;
}

/**
 * @brief Calculates nutation in equatorial coordinates.
 * @param star Star to perform calculation for.
 * @param jd Julian Day corresponding to calculation instance.
 * @param nut_ra Output nutation in right ascension.
 * @param nut_dec Output nutation in declination.
 * @since 0.0.1
 */
static void
_sca_star_get_nutation_equatorial (SCAStar *star, double jd, SCAAngle *nut_ra, SCAAngle *nut_dec)
{
	SCAAngle	obl;
	SCAAngle	d_nut, d_obl;
	double		cos_obl, sin_obl;
	double		cos_ra, sin_ra;
	double		tan_dec;

	sca_earth_get_nutation (jd, &d_nut, &d_obl);
	sca_earth_get_ecliptic_obliquity (jd, &obl);

	sca_angle_get_sincos (obl, &sin_obl, &cos_obl);
	sca_angle_get_sincos (star->ra, &sin_ra, &cos_ra);
	tan_dec = tan (sca_angle_to_radians (star->dec));
	
	if (nut_ra != NULL)
		*nut_ra	= (cos_obl + sin_obl * sin_ra * tan_dec) * d_nut - (cos_ra * tan_dec) * d_obl;
	
	if (nut_dec != NULL)	
		*nut_dec = (sin_obl * cos_ra) * d_nut + sin_ra * d_obl; 
}

int
sca_star_new (SCAStar	*star,
	      SCAAngle	ra2000,
	      SCAAngle	dec2000,
	      SCAAngle	ra_motion,
	      SCAAngle	dec_motion)
{
	if (star == NULL)
		return -1;

	star->ra2000		= ra2000;
	star->dec2000		= dec2000;

	sca_angle_reduce (&star->ra2000);
	sca_angle_reduce (&star->dec2000);

	star->ra_motion		= ra_motion;
	star->dec_motion	= dec_motion;
	star->ra		= star->ra2000;
	star->dec		= star->dec2000;

	sca_angle_reduce (&star->ra_motion);
	sca_angle_reduce (&star->dec_motion);

	star->jd		= SCA_JD_EPOCH_2000;

	return 0;
}

int
sca_star_update_date (SCAStar	*star,
		      SCADate	*date)
{
	double		jd;
	SCAAngle	abr_ra, abr_dec;
	SCAAngle	nut_ra, nut_dec;


	if (star == NULL || date == NULL)
		return -1;

	jd = sca_jd_from_calendar_date (date);
	jd += sca_jd_get_dynamic_time (jd);

	star->ra	= star->ra2000;
	star->dec	= star->dec2000;

	_sca_star_precess (star, jd);
	_sca_star_get_aberration_equatorial (star, jd, &abr_ra, &abr_dec);
	_sca_star_get_nutation_equatorial (star, jd, &nut_ra, &nut_dec);

	star->ra	+= (abr_ra + nut_ra);
	star->dec	+= (abr_dec + nut_dec);

	star->jd	= jd;

	return 0;
}

int
sca_star_get_local_coordinates	(SCAStar	*star,
				 SCAGeoLocation	*loc,
				 SCAAngle	*A,
				 SCAAngle	*h)
{
	if (star == NULL || loc == NULL)
		return -1;

	sca_coordinates_equatorial_to_local (star->jd, loc, star->ra, star->dec, A, h);

	return 0;
}
