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
 * @file scacoordinates.h
 * @brief Преобразование координат
 * @author Александр Сапрыкин
 *
 * SCALib использует практически для всех объектов экваториальные координаты. Для их
 * преобразования в эклиптические или местные горизонтальные можно воспользоваться функциями
 * sca_coordinates_equatorial_to_ecliptic() и sca_coordinates_equatorial_to_local().
 * Причём функция sca_coordinates_equatorial_to_local() не учитывает различные коррекции, связанные
 * с Землёй (например, параллакс). Если нужно учесть их, то следует воспользоваться
 * функцией *_get_local_coordinates() для соответствующего небесного тела. Рефракция
 * рассчитывается отдельно функцией sca_earth_get_refraction().
 */
#else
/**
 * @file scacoordinates.h
 * @brief Coordinates transformation routines
 * @author Alexander Saprykin
 *
 * SCALib stores almost all object's coordinates as equatorial. To convert
 * them into ecliptical or local horizontal consider using
 * sca_coordinates_equatorial_to_ecliptic() and sca_coordinates_equatorial_to_local()
 * routines. Note that sca_coordinates_equatorial_to_local() function doesn't take in
 * account different corrections corresponding to the Earth (i.e. parallax).
 * If you want to take them into account consider using *_get_local_coordinates()
 * functions for respective sky object. Refraction can be calculated explicitly using
 * sca_earth_get_refraction() routine.
 */
#endif

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

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Преобразует экваториальные координаты в эклиптические.
 * @param jd Юлианский день, соответствующий времени преобразования.
 * @param ra Прямое восхождение в экваториальных координатах.
 * @param dec Склонение в экваториальных координатах.
 * @param[out] lon Эклиптическая долгота (от точки весеннего равноденствия) может быть NULL.
 * @param[out] lat Эклиптическая широта (положительная на север от эклиптики, отрицательная на юг),
 * может быть NULL.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Transforms equatorial coordinates to ecliptical.
 * @param jd Julian Day corresponding to transformation.
 * @param ra Right ascension in equatorial coordinates.
 * @param dec Declination in equatorial coordinates.
 * @param[out] lon Ecliptical longitude (measured from vernal equinox), may be NULL.
 * @param[out] lat Ecliptical latitude (positive north of ecliptic, negative south), may be NULL.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int sca_coordinates_equatorial_to_ecliptic	(double jd, SCAAngle ra, SCAAngle dec, SCAAngle *lon, SCAAngle *lat);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Преобразует эклиптические координаты в экваториальные.
 * @param jd Юлианский день, соответствующий времени преобразования.
 * @param lon Эклиптическая долгота (от точки весеннего равноденствия).
 * @param lat Эклиптическая широта (положительная на север от эклиптики, отрицательная на юг).
 * @param[out] ra Прямое восхождение в экваториальных координатах, может быть NULL.
 * @param[out] dec Склонение в экваториальных координатах, может быть NULL.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Transforms ecliptical coordinates to equatorial.
 * @param jd Julian Day corresponding to transformation.
 * @param lon Ecliptical longitude (measured from vernal equinox).
 * @param lat Ecliptical latitude (positive north of ecliptic, negative south).
 * @param[out] ra Right ascension in equatorial coordinates, may be NULL.
 * @param[out] dec Declination in equatorial coordinates, may be NULL.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int sca_coordinates_ecliptic_to_equatorial	(double jd, SCAAngle lon, SCAAngle lat, SCAAngle *ra, SCAAngle *dec);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Преобразует экваториальные координаты в местные (азимут и высота).
 * @param jd Юлианский день, соответствующий времени преобразования.
 * @param loc Положение наблюдателя.
 * @param ra Прямое восхождение в экваториальных координатах.
 * @param dec Склонение в экваториальных координатах.
 * @param[out] A Азимут (положительный на запад от юга), может быть NULL.
 * @param[out] h Высота над горизонтом, может быть NULL.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Transforms equatorial coordinates to local (azimuth and altitude).
 * @param jd Julian Day corresponding to transformation.
 * @param loc Location of the observer.
 * @param ra Right ascension in equatorial coordinates.
 * @param dec Declination in equatorial coordinates.
 * @param[out] A Azimuth (positive westwards from south), may be NULL.
 * @param[out] h Altitude above horizon, may be NULL.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int sca_coordinates_equatorial_to_local		(double jd, SCAGeoLocation *loc, SCAAngle ra, SCAAngle dec, SCAAngle *A, SCAAngle *h);

SCA_END_DECLS

#endif /* __SCACOORDINATES_H_ */

