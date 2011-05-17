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
 * @file scasun.h
 * @brief Representation of the Sun
 * @author Alexander Saprykin
 *
 * #SCASun is used to represent a Sun with equatorial coordinates. Sun's
 * position can be retrieved with accuracy of about 3'' for given date. Let's
 * calculate it's position for June 15, 2011 at 13:54 UT for Saint Petersburg
 * in Russian Federation (E 30°32'41'', N 60°16'31''):
 * @code
 * SCASun		sun;
 * SCADate		date;
 * SCAGeoLocation	loc;
 * SCAAngle		A, h;
 *
 * loc.longitude	= sca_angle_from_degrees (-30, 32, 41, 0.0);
 * loc.latitude		= sca_angle_from_degrees (60, 16, 31, 0.0);
 *
 * date.year	= 2011;
 * date.month	= SCA_MONTH_JUNE;
 * date.day	= 15 + SCA_DAYS_FROM_TIME (13, 54, 0);
 *
 * sca_sun_update_date (&sun, &date);
 * sca_sun_get_local_coordinates (&sun, &loc, &A, &h);
 * h += sca_earth_get_refraction (h);
 * @endcode
 * Now variable @a A stores azimuth (positive westward from south, not eastward
 * from north!), and variable @a h stores altitude above the horizon with refraction
 * corrections. Also note that east longitude is negative (while west is positive).
 */

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCASUN_H__
#define __SCASUN_H__

#include <math.h>

#include <scamacros.h>
#include <scaangle.h>
#include <scajulianday.h>
#include <scacoordinates.h>

SCA_BEGIN_DECLS

/** Typedef for the Sun object. */
typedef struct _SCASun {
	SCAAngle	ra;	/**< Current right ascension.			*/
	SCAAngle	dec;	/**< Current declination.			*/
	double		jd;	/**< Date corresponding to current position.	*/
	double		dst;	/**< Current distance to the Earth.		*/
} SCASun;

/**
 * @brief Calculates Sun's geometric mean longirude for given instance of time.
 * @param jd Julian Day corresponding to calculation instance.
 * @param L Output geometric mean longitude of the Sun.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */	
int	sca_sun_get_mean_longitude	(double jd, SCAAngle *L);

/**
 * @brief Calculates Sun's geometric true longirude for given instance of time.
 * @param jd Julian Day corresponding to calculation instance.
 * @param T Output geometric true longitude of the Sun.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
int	sca_sun_get_true_longitude	(double jd, SCAAngle *T);

/**
 * @brief Calculates Sun's mean anomaly for given instance of time.
 * @param jd Julian Day corresponding to calculation instance.
 * @param M Output mean anomaly of the Sun.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */	
int	sca_sun_get_mean_anomaly	(double jd, SCAAngle *M);

/**
 * @brief Calculates Sun's position for given date.
 * @param sun #SCASun object for updating.
 * @param date Date in UT to perform calculation for.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
int	sca_sun_update_date		(SCASun *sun, SCADate *date);

/**
 * @brief Calculates local coordinates of the Sun parallax corrections.
 * @param sun #SCASun object.
 * @param loc Observer location.
 * @param A Output azimuth (positive westward from south), may be NULL.
 * @param h Output altitude above horizon, may be NULL.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 * @note To take in account refraction use sca_earth_get_refraction() routine.
 */
int	sca_sun_get_local_coordinates	(SCASun *sun, SCAGeoLocation *loc, SCAAngle *A, SCAAngle *h);

SCA_END_DECLS

#endif /* __SCASUN_H__ */

