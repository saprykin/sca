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
 * @file scaearth.h
 * @brief Miscellaneous routines related to the Earth
 * @author Alexander Saprykin
 *
 */

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCAEARTH_H__
#define __SCAEARTH_H__

#include <math.h>

#include <scamacros.h>
#include <scaangle.h>

SCA_BEGIN_DECLS

/** Typedef for geolocation. */
typedef struct _SCAGeoLocation {
	SCAAngle	longitude;	/**< Location longitude, positive westward from Greenwich.	*/
	SCAAngle	latitude;	/**< Location latitude, positive north from equator.		*/
} SCAGeoLocation;

/**
 * @brief Calculates the obliquity of the ecliptic.
 * @param jd Julian Day corresponding to calculation instance.
 * @param obl Output obliquity.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
int		sca_earth_get_ecliptic_obliquity	(double jd, SCAAngle *obl);

/**
 * @brief Calculates Earth's nutation in longitude and obliquity.
 * @param jd Julian Day corresponding to calculation instance.
 * @param nut Output nutation in longitude, may be NULL.
 * @param obl Output nutation in obliquity, may be NULL.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 */
int		sca_earth_get_nutation			(double jd, SCAAngle *nut, SCAAngle *obl);

/**
 * @brief Calculates atmospheric refraction. Add returned value to the altitude.
 * @param h Altitude of the celestial body above horizon.
 * @return Altitude correction angle.
 * @since 0.0.1
 */
SCAAngle	sca_earth_get_refraction		(SCAAngle h);

/**
 * @brief Calculates parallax in equatorial coordinates for observer on the Earth.
 * Add output values respectively to coordinates of the sky object.
 * @param jd Julian Day corresponding to calculation instance.
 * @param dst Geocentric distance of the object in AU.
 * @param loc Location of the observer.
 * @param ra Object's right ascension.
 * @param dec Object's declination.
 * @param d_ra Output right ascension parallax, may be NULL.
 * @param d_dec Output declination parallax, may be NULL.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 */
int		sca_earth_get_parallax_equatorial	(double		jd,
							 double		dst,
							 SCAGeoLocation	*loc,
							 SCAAngle	ra,
							 SCAAngle	dec,
							 SCAAngle	*d_ra,
							 SCAAngle	*d_dec);

/**
 * @brief Calculates Earth's orbit eccentricity for given instance of time.
 * @param jd Julian Day corresponding to calculation instance.
 * @param e Output eccentricity.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
int		sca_earth_get_orbit_eccentricity	(double jd, double *e);

/**
 * @brief Returns aberration costant.
 * @return #SCAAngle structure with aberration constant.
 * @since 0.0.1
 */
SCAAngle	sca_earth_get_aberration_constant	(void);

/**
 * @brief Calculates Earth's orbit perihelion longitude for
 * given instance of time.
 * @param jd Julian Day corresponding to calculation instance.
 * @param pi Output perihelion.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
int		sca_earth_get_perihelion_longitude	(double jd, SCAAngle *pi);

SCA_END_DECLS

#endif /* __SCAEARTH_H_ */

