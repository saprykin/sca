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
 * @file scastar.h
 * @brief Представление звезды в виде точки
 * @author Александр Сапрыкин
 *
 * #SCAStar используется для представления звезды в виде точечного объекта. Положение
 * звезды в любой момент времени определяется четырьями параметрами: прямое восхождние (RA)
 * и склонение (Dec) на эпоху J2000, годовое собственное движение (PM) для прямого
 * восхождения склонения. Эти параметры используются для инициализации объекта #SCAStar.
 * Рассмотрим пример расчёта положения звезды Денеб (Альфа Лебедя) на 13 октября 2011 года
 * в 12:00 UT (данные по Денебу на эпоху J2000: RA = 20ч:41м:25.9с, Dec = 45°16'49'',
 * PM RA = 1.99 миллисекунд дуги за год, PM Dec = 1.95 миллисекунд дуги за год):
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
 * Теперь можно использовать sca_star_get_local_coordinates() для получения азимута и
 * высоты для конкретного географического положения наблюдателя, а sca_earth_get_refraction()
 * для получения поправки по высоте с учётом рефракции (просто добавить возвращаемое значение
 * к полученной высоте).
 */
#else
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
#endif

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

#ifdef DOXYGEN_RUSSIAN
/** Определение типа для объекта звезды. */
#else
/** Typedef for star object. */
#endif
typedef struct _SCAStar {
#ifdef DOXYGEN_RUSSIAN
	/** Прямое восхождение на J2000.		*/
#else
	/** J2000 right ascension.			*/
#endif
	SCAAngle	ra2000;

#ifdef DOXYGEN_RUSSIAN
	/** Склонение на J2000.				*/
#else
	/** J2000 declination.				*/
#endif
	SCAAngle	dec2000;

#ifdef DOXYGEN_RUSSIAN
	/** Текущее прямое восхождение.			*/
#else
	/** Current right ascension.			*/
#endif
	SCAAngle	ra;

#ifdef DOXYGEN_RUSSIAN
	/** Текущее склонение.				*/
#else
	/** Current declination.			*/
#endif
	SCAAngle	dec;

#ifdef DOXYGEN_RUSSIAN
	/** Годовое собственное движение RA.		*/
#else
	/** Annual proper motion of RA.			*/
#endif
	SCAAngle	ra_motion;

#ifdef DOXYGEN_RUSSIAN
	/** Годовое собственное движение Dec.		*/
#else
	/** Annual proper motion of Dec.		*/
#endif
	SCAAngle	dec_motion;

#ifdef DOXYGEN_RUSSIAN
	/** Юлианский день, соответствующий положению.	*/
#else
	/** Julian day corresponding to position.	*/
#endif
	double		jd;
} SCAStar;

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Инициализиует объект #SCAStar.
 * @param[out] star Структура #SCAStar для инициализации.
 * @param ra2000 Прямое восхождение на эпоху J2000.
 * @param dec2000 Склонение на эпоху J2000.
 * @param ra_motion Годовое собственное движение прямого восхождения.
 * @param dec_motion Годовое собственное движение склонения.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Initializes #SCAStar object.
 * @param[out] star #SCAStar structure to initialize.
 * @param ra2000 Right ascension for J2000 epoch.
 * @param dec2000 Declination for J2000 epoch.
 * @param ra_motion Annual proper motion of right ascension.
 * @param dec_motion Annual proper motion of declination.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int		sca_star_new			(SCAStar	*star,
						 SCAAngle	ra2000,
						 SCAAngle	dec2000,
						 SCAAngle	ra_motion,
						 SCAAngle	dec_motion);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Обновляет положение звезды на заданный момент времени.
 * @param[in,out] star Объект #SCAStar для обновления положения.
 * @param date Дата в UT для выполнения расчёта.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 * @note Перед вызовом данной функции необходимо проинициализировать объект
 * @a star функцией sca_star_new().
 */
#else
/**
 * @brief Updates coordinates of the star to corresponding date.
 * @param[in,out] star #SCAStar to update coordinates.
 * @param date Date in UT to perform calculation for.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 * @note You must initialize @a star object with sca_star_new() routine
 * before calling this one.
 */
#endif
int		sca_star_update_date		(SCAStar *star, SCADate *date);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает местные координаты звезды.
 * @param star Объект #SCAStar.
 * @param loc Положение наблюдателя.
 * @param[out] A Азимут (положительный на запад от юга), может быть NULL.
 * @param[out] h Высота над горизонтом, может быть NULL.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 * @note Для учёта рефракции используйте функцию sca_earth_get_refraction().
 * Данная функция должна вызываться только после хотя бы одного вызова функции
 * sca_star_update_date() для того же объекта #SCAStar, иначе результат неопределён.
 */
#else
/**
 * @brief Calculates local coordinates of the star.
 * @param star #SCAStar object.
 * @param loc Observer location.
 * @param[out] A Azimuth (positive westward from south), may be NULL.
 * @param[out] h Altitude above horizon, may be NULL.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 * @note To take in account refraction use sca_earth_get_refraction() routine.
 * This function must be called only after at least one call of sca_star_update_date()
 * for the same #SCAStar object or result is undefined.
 */
#endif
int		sca_star_get_local_coordinates	(SCAStar *star, SCAGeoLocation *loc, SCAAngle *A, SCAAngle *h);

SCA_END_DECLS

#endif /* __SCASTAR_H__ */
