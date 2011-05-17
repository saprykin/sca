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
 * @file scaplanetdata.h
 * @brief Planet data required for position computations
 * @author Alexander Saprykin
 *
 */

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCAPLANETDATA_H__
#define __SCAPLANETDATA_H__

#include <scamacros.h>
#include <scaangle.h>

SCA_BEGIN_DECLS

/** Typedef for Solar system's planets. */
typedef enum _SCAPlanet {
	SCA_PLANET_MERCURY	= 1,	/**< Mercury	*/
	SCA_PLANET_VENUS	= 2,	/**< Venus	*/
	SCA_PLANET_EARTH	= 3,	/**< Earth	*/
	SCA_PLANET_MARS		= 4,	/**< Mars	*/
	SCA_PLANET_JUPITER	= 5,	/**< Jupiter	*/
	SCA_PLANET_SATURN	= 6,	/**< Saturn	*/
	SCA_PLANET_URANUS	= 7,	/**< Uranus	*/
	SCA_PLANET_NEPTUNE	= 8	/**< Neptune	*/
} SCAPlanet;

/**
 * @brief Calculates heliocentric planet position and distance to the Sun
 * using VSOP87 planet theory.
 * @param planet Target planet.
 * @param jd Julian Day corresponding to instance of time.
 * @param lon Output heliocentric longitude, may be NULL.
 * @param lat Output heliocentric latitude, may be NULL.
 * @param dst Output distance to the Sun in Astronomical Units, may be NULL.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
int sca_planet_data_get (SCAPlanet planet, double jd, SCAAngle *lon, SCAAngle *lat, double *dst);

SCA_END_DECLS

#endif /* __SCAPLANETDATA_H__ */

