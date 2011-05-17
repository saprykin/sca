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
 * @file scamoon.h
 * @brief Representation of the Moon
 * @author Alexander Saprykin
 *
 * #SCAMoon is used to represent a Moon with equatorial coordinates. Moon's
 * position can be retrieved with accuracy of about 10'' in longitude and
 * 4'' in latitude for given date. Let's calculate it's position for
 * May 22, 2011 at 03:20 UT for Saint Petersburg in Russian Federation
 * (E 30°32'41'', N 60°16'31''):
 * @code
 * SCAMoon		moon;
 * SCADate		date;
 * SCAGeoLocation	loc;
 * SCAAngle		A, h;
 *
 * loc.longitude	= sca_angle_from_degrees (-30, 32, 41, 0.0);
 * loc.latitude		= sca_angle_from_degrees (60, 16, 31, 0.0);
 *
 * date.year	= 2011;
 * date.month	= SCA_MONTH_MAY;
 * date.day	= 22 + SCA_DAYS_FROM_TIME (3, 20, 0);
 *
 * sca_moon_update_date (&moon, &date);
 * sca_moon_get_local_coordinates (&moon, &loc, &A, &h);
 * h += sca_earth_get_refraction (h);
 * @endcode
 * Now variable @a A stores azimuth (positive westward from south, not eastward
 * from north!), and variable @a h stores altitude above the horizon with refraction
 * corrections. Also note that east longitude is negative (while west is positive).
 */

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCAMOON_H__
#define __SCAMOON_H__

#include <scamacros.h>
#include <scaangle.h>
#include <scajulianday.h>
#include <scaearth.h>

SCA_BEGIN_DECLS

/** Typedef for the Moon object. */
typedef struct _SCAMoon {
	SCAAngle	ra;	/**< Current right ascension.			*/
	SCAAngle	dec;	/**< Current declination.			*/
	double		jd;	/**< Date corresponding to current position.	*/
	double		dst;	/**< Current distance to the Earth.		*/
} SCAMoon;

/**
 * @brief Calculates mean elongation of the Moon from the Sun.
 * @param jd Julian Day corresponding to calculation instance of time.
 * @param elong Output mean elongation.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 */
int	sca_moon_get_mean_elongation_from_sun	(double jd, SCAAngle *elong);

/**
 * @brief Calculates mean anomaly of the Moon.
 * @param jd Julian Day corresponding to calculation instance of time.
 * @param anom Output mean anomaly.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 */
int	sca_moon_get_mean_anomaly		(double jd, SCAAngle *anom);

/**
 * @brief Calculates mean longitude of the Moon.
 * @param jd Julian Day corresponding to calculation instance of time.
 * @param lon Output mean longitude.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 */
int	sca_moon_get_mean_longitude		(double jd, SCAAngle *lon);

/**
 * @brief Calculates argument of the latitude of the Moon.
 * @param jd Julian Day corresponding to calculation instance of time.
 * @param arg Output argument of latitude.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 */
int	sca_moon_get_latitude_argument		(double jd, SCAAngle *arg);

/**
 * @brief Calculates mean longitude of the Moon's ascending node.
 * @param jd Julian Day corresponding to calculation instance of time.
 * @param lon Output mean longitude of the ascending node.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 */
int	sca_moon_get_mean_longitude_of_ascnode	(double jd, SCAAngle *lon);

/**
 * @brief Calculates Moon's position for given date.
 * @param moon #SCAMoon object for updating.
 * @param date Date in UT to perform calculation for.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
int	sca_moon_update_date			(SCAMoon *moon, SCADate *date);

/**
 * @brief Calculates local coordinates of the Moon including parallax corrections.
 * @param moon #SCAMoon object.
 * @param loc Observer location.
 * @param A Output azimuth (positive westward from south), may be NULL.
 * @param h Output altitude above horizon, may be NULL.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 * @note To take in account refraction use sca_earth_get_refraction() routine.
 */
int	sca_moon_get_local_coordinates		(SCAMoon *moon, SCAGeoLocation *loc, SCAAngle *A, SCAAngle *h);

SCA_END_DECLS

#endif /* __SCAMOON_H__ */
