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

#ifdef DOXYGEN_RUSSIAN
/**
 * @file scaplanetdata.h
 * @brief Данные для расчёта положения планет
 * @author Александр Сапрыкин
 */
#else
/**
 * @file scaplanetdata.h
 * @brief Planet data required for position computations
 * @author Alexander Saprykin
 */
#endif

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCAPLANETDATA_H__
#define __SCAPLANETDATA_H__

#include <scamacros.h>
#include <scaangle.h>

SCA_BEGIN_DECLS

#ifdef DOXYGEN_RUSSIAN
/** Перечисление планет Солнечной системы. */
#else
/** Typedef for Solar system's planets. */
#endif
typedef enum _SCAPlanet {
#ifdef DOXYGEN_RUSSIAN
	/** Меркурий	*/
#else
	/** Mercury	*/
#endif
	SCA_PLANET_MERCURY	= 1,

#ifdef DOXYGEN_RUSSIAN
	/** Венера	*/
#else
	/** Venus	*/
#endif
	SCA_PLANET_VENUS	= 2,

#ifdef DOXYGEN_RUSSIAN
	/** Земля	*/
#else
	/** Earth	*/
#endif
	SCA_PLANET_EARTH	= 3,

#ifdef DOXYGEN_RUSSIAN
	/** Марс	*/
#else
	/** Mars	*/
#endif
	SCA_PLANET_MARS		= 4,

#ifdef DOXYGEN_RUSSIAN
	/** Юпитер	*/
#else
	/** Jupiter	*/
#endif
	SCA_PLANET_JUPITER	= 5,

#ifdef DOXYGEN_RUSSIAN
	/** Сатурн	*/
#else
	/** Saturn	*/
#endif
	SCA_PLANET_SATURN	= 6,

#ifdef DOXYGEN_RUSSIAN
	/** Уран	*/
#else
	/** Uranus	*/
#endif
	SCA_PLANET_URANUS	= 7,

#ifdef DOXYGEN_RUSSIAN
	/** Нептун	*/
#else
	/** Neptune	*/
#endif
	SCA_PLANET_NEPTUNE	= 8
} SCAPlanet;

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает гелиоцентрическое положение планеты и расстояние до Солнца
 * с помощью планетарной теории VSOP87.
 * @param planet Целевая планета.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param[out] lon Гелиоцентрическая долгота, может быть NULL.
 * @param[out] lat Гелиоцентрическая широта, может быть NULL.
 * @param[out] dst Расстояние до Солнца в АЕ, может быть NULL.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates heliocentric planet position and distance to the Sun
 * using VSOP87 planet theory.
 * @param planet Target planet.
 * @param jd Julian Day corresponding to calculation instance.
 * @param[out] lon Heliocentric longitude, may be NULL.
 * @param[out] lat Heliocentric latitude, may be NULL.
 * @param[out] dst Distance to the Sun in AUs, may be NULL.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int sca_planet_data_get (SCAPlanet planet, double jd, SCAAngle *lon, SCAAngle *lat, double *dst);

SCA_END_DECLS

#endif /* __SCAPLANETDATA_H__ */

