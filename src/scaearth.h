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
 * @file scaearth.h
 * @brief Функции для работы с Землёй
 * @author Александр Сапрыкин
 */
#else
/**
 * @file scaearth.h
 * @brief Miscellaneous routines related to the Earth
 * @author Alexander Saprykin
 */
#endif

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCAEARTH_H__
#define __SCAEARTH_H__

#include <math.h>

#include <scamacros.h>
#include <scaangle.h>

SCA_BEGIN_DECLS

#ifdef DOXYGEN_RUSSIAN
/** Определение типа для географического положения. */
#else
/** Typedef for geolocation. */
#endif
typedef struct _SCAGeoLocation {
#ifdef DOXYGEN_RUSSIAN
	/** Долгота, положительная на запад от Гринвича. */
#else
	/** Location longitude, positive westward from Greenwich. */
#endif
	SCAAngle	longitude;

#ifdef DOXYGEN_RUSSIAN
	/** Широта, положительная к северу от экватора.  */
#else
	/** Location latitude, positive north from equator. */
#endif
	SCAAngle	latitude;
} SCAGeoLocation;

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает угол наклона эклиптики.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param obl Наклон эклиптики, выходной.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates the obliquity of the ecliptic.
 * @param jd Julian Day corresponding to calculation instance.
 * @param obl Output obliquity.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int		sca_earth_get_ecliptic_obliquity	(double jd, SCAAngle *obl);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает нутацию Земли по долготе и наклону эклиптики.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param nut Нутация по долготе, выходной, может быть NULL.
 * @param obl Нутация по наклону эклиптики, выходной, может быть NULL.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates Earth's nutation in longitude and obliquity.
 * @param jd Julian Day corresponding to calculation instance.
 * @param nut Output nutation in longitude, may be NULL.
 * @param obl Output nutation in obliquity, may be NULL.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int		sca_earth_get_nutation			(double jd, SCAAngle *nut, SCAAngle *obl);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает атмосферную рефракцию. Возвращаемое значение добавляется
 * к высоте объекта.
 * @param h Высота небесного тела над горизонтом.
 * @return Угол коррекции по высоте.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates atmospheric refraction. Add returned value to the altitude.
 * @param h Altitude of the celestial body above horizon.
 * @return Altitude correction angle.
 * @since 0.0.1
 */
#endif
SCAAngle	sca_earth_get_refraction		(SCAAngle h);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает параллакс в экваториальных координатах для наблюдателя на Земле.
 * Возвращаемые значения добавляются к соответствующим координатам небесного тела.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param dst Геоцентрическое расстояние до объекта в АЕ.
 * @param loc Положение наблюдателя.
 * @param ra Прямое восхождение объекта.
 * @param dec Склонение объекта.
 * @param d_ra Параллакс прямого восхождения, выходной, может быть NULL.
 * @param d_dec Параллакс склонения, выходной, может быть NULL.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
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
#endif
int		sca_earth_get_parallax_equatorial	(double		jd,
							 double		dst,
							 SCAGeoLocation	*loc,
							 SCAAngle	ra,
							 SCAAngle	dec,
							 SCAAngle	*d_ra,
							 SCAAngle	*d_dec);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает эксцентриситет орбиты Земли для заданного момента времени.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param e Эксцентриситет, выходной.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates Earth's orbit eccentricity for given instance of time.
 * @param jd Julian Day corresponding to calculation instance.
 * @param e Output eccentricity.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int		sca_earth_get_orbit_eccentricity	(double jd, double *e);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Возвращает константу аберрации.
 * @return Структуру #SCAAngle с константой аберрации.
 * @since 0.0.1
 */
#else
/**
 * @brief Returns aberration costant.
 * @return #SCAAngle structure with aberration constant.
 * @since 0.0.1
 */
#endif
SCAAngle	sca_earth_get_aberration_constant	(void);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает аргумент перицентра орбиты Земли для заданного момента
 * времени.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param pi Аргумент перицентра, выходной.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates Earth's orbit perihelion longitude for
 * given instance of time.
 * @param jd Julian Day corresponding to calculation instance.
 * @param pi Output perihelion.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int		sca_earth_get_perihelion_longitude	(double jd, SCAAngle *pi);

SCA_END_DECLS

#endif /* __SCAEARTH_H_ */

