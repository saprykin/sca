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
 * @file scastar.h
 * @brief Representation of star as a sky point object
 * @author Alexander Saprykin
 *
 * #SCAStar is used to represent a star in the sky. It's position is to be
 * identified at any moment of time by four parameters: right ascension (RA) and
 * declination (Dec) for J2000 epoch, and annual proper motion (PM) for right ascension
 * and declination. Use these parameters to initialize #SCAStar object with.
 * For example let's calculate position of the Deneb (Cygnus Alpha) for
 * October 13, 2011 at 12:00 UT (data for Deneb at J2000: RA = 20h:41m:25.9s,
 * Dec = 45°16'49'', PM RA = 1.99 milliarcseconds/year, PM Dec = 1.95 millarcseconds/year):
 * @code
 * SCAStar	star;
 * SCAAngle	ra2000, dec2000, pmra, pmdec;
 * SCADate	date;
 *
 * ra2000	= sca_angle_from_hours (20, 41, 25, 900.0);
 * dec2000	= sca_angle_from_degrees (45, 16, 49, 0.0);
 * pmra		= sca_angle_from_degrees (0, 0, 0, 1.99);
 * pmdec	= sca_angle_from_degrees (0, 0, 0, 1.95);
 *
 * date.year	= 2011;
 * date.month	= SCA_MONTH_OCTOBER;
 * date.day	= 13 + SCA_DAYS_FROM_TIME (12, 0, 0);
 *
 * sca_star_new (&star, ra2000, dec2000, pmra, pmdec);
 * sca_star_update_date (&star, &date);
 * @endcode
 * Now you can use sca_star_get_local_coordinates() to get azimuth and altitude
 * for specific geolocation, and sca_earth_get_refraction() to get refraction
 * correction for the altitude (just add a returned value to the altitude).
 */

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCASTAR_H__
#define __SCASTAR_H__

#include <math.h>

#include <scamacros.h>
#include <scaangle.h>
#include <scajulianday.h>
#include <scacoordinates.h>

SCA_BEGIN_DECLS

/** Typedef for star object. */
typedef struct _SCAStar {
	SCAAngle	ra2000;		/**< J2000 right ascension.		*/
	SCAAngle	dec2000;	/**< J2000 declination.			*/
	SCAAngle	ra;		/**< Current right ascension.		*/
	SCAAngle	dec;		/**< Current declination.		*/
	SCAAngle	ra_motion;	/**< Annual proper motion of RA.	*/
	SCAAngle	dec_motion;	/**< Annual proper motion of Dec.	*/
	double		jd;		/**< Julian day for to position.	*/
} SCAStar;

/**
 * @brief Initializes #SCAStar object.
 * @param star #SCAStar structure to initialize.
 * @param ra2000 Right ascension for J2000 epoch.
 * @param dec2000 Declination for J2000 epoch.
 * @param ra_motion Annual proper motion of right ascension.
 * @param dec_motion Annual proper motion of declination.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
int		sca_star_new			(SCAStar	*star,
						 SCAAngle	ra2000,
						 SCAAngle	dec2000,
						 SCAAngle	ra_motion,
						 SCAAngle	dec_motion);

/**
 * @brief Updates coordinates of the star to corresponding date.
 * @param star #SCAStar to update coordinates.
 * @param date Date in UT to set for the @a star.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
int		sca_star_update_date		(SCAStar *star, SCADate *date);

/**
 * @brief Calculates local coordinates of the star.
 * @param star #SCAStar object.
 * @param loc Observer location.
 * @param A Output azimuth (positive westward from south), may be NULL.
 * @param h Output altitude above horizon, may be NULL.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 * @note To take in account refraction use sca_earth_get_refraction() routine.
 */
int		sca_star_get_local_coordinates	(SCAStar *star, SCAGeoLocation *loc, SCAAngle *A, SCAAngle *h);

SCA_END_DECLS

#endif /* __SCASTAR_H__ */

