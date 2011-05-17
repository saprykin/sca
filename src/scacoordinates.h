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
 * @file scacoordinates.h
 * @brief Coordinates transformation routines
 * @author Alexander Saprykin
 *
 * SCALib stores almost all object's coordinates as equatorial. To convert
 * them into ecliptical or local horizontal consider using
 * sca_coordinates_equatorial_to_ecliptic() and sca_coordinates_equatorial_to_local()
 * routines. Note that sca_coordinates_equatorial_to_local() function doesn't take in
 * account different corrections corresponding to the Earth (atmosphere refraction,
 * parallax). If you want to take them into account consider using *_get_local_coordinates()
 * functions for respective sky object.
 */

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCACOORDINATES_H__
#define __SCACOORDINATES_H__

#include <math.h>

#include <scamacros.h>
#include <scaangle.h>
#include <scaearth.h>

SCA_BEGIN_DECLS

/**
 * @brief Transforms equatorial coordinates to ecliptical.
 * @param jd Julian Day corresponding to transformation.
 * @param ra Right ascension in equatorial coordinates.
 * @param dec Declination in equatorial coordinates.
 * @param lon Ecliptical longitude (measured from vernal equinox), output, may be NULL.
 * @param lat Ecliptical latitude (positive north of ecliptic, negative south), output, may be NULL.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
int sca_coordinates_equatorial_to_ecliptic	(double jd, SCAAngle ra, SCAAngle dec, SCAAngle *lon, SCAAngle *lat);

/**
 * @brief Transforms ecliptical coordinates to equatorial.
 * @param jd Julian Day corresponding to transformation.
 * @param lon Ecliptical longitude (measured from vernal equinox).
 * @param lat Ecliptical latitude (positive north of ecliptic, negative south).
 * @param ra Right ascension in equatorial coordinates, output, may be NULL.
 * @param dec Declination in equatorial coordinates, output, may be NULL.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
int sca_coordinates_ecliptic_to_equatorial	(double jd, SCAAngle lon, SCAAngle lat, SCAAngle *ra, SCAAngle *dec);

/**
 * @brief Transforms equatorial coordinates to local (azimuth and altitude).
 * @param jd Julian Day corresponding to transformation.
 * @param loc Location of the observer.
 * @param ra Right ascension in equatorial coordinates.
 * @param dec Declination in equatorial coordinates.
 * @param A Output azimuth (positive westwards from south), may be NULL.
 * @param h Output altitude above horizon, may be NULL.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
int sca_coordinates_equatorial_to_local		(double jd, SCAGeoLocation *loc, SCAAngle ra, SCAAngle dec, SCAAngle *A, SCAAngle *h);

SCA_END_DECLS

#endif /* __SCACOORDINATES_H_ */

