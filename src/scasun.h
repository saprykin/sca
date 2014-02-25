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
 * @file scasun.h
 * @brief Представление Солнца
 * @author Александр Сапрыкин
 *
 * #SCASun используется для представления Солнца в экваториальных координатах.
 * Положение Солнца может быть рассчитано с точностью примерно 3'' на заданный
 * момент времени. Для примера рассчитаем положение Солнца на 15 июня 2011 года
 * в 13:54 UT для Санкт-Петербурга в Российской Федерации (E 30°32'41'', N 60°16'31''):
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
 * Теперь переменная @a A содержит азимут (положительный на запад от юга, а не на
 * восток от севера!), а переменная @a h содержит высоту над горизонтом с учётом
 * рефракции. Также следует обратить внимание, что восточная долгота отрицательна
 * (в то время как западная - положительна).
 */
#else
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
#endif

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

#ifdef DOXYGEN_RUSSIAN
/** Определение типа для объекта Солнца. */
#else
/** Typedef for the Sun object. */
#endif
typedef struct _SCASun {
#ifdef DOXYGEN_RUSSIAN
	/** Текущее прямое восхождение.				*/
#else
	/** Current right ascension.				*/
#endif
	SCAAngle	ra;

#ifdef DOXYGEN_RUSSIAN
	/** Текущее склонение.					*/
#else
	/** Current declination.				*/
#endif
	SCAAngle	dec;

#ifdef DOXYGEN_RUSSIAN
	/** Дата текущего положения (в юлианских днях).		*/
#else
	/** Date corresponding to current position (in JD).	*/
#endif
	double		jd;

#ifdef DOXYGEN_RUSSIAN
	/** Текущее расстояние до Земли (в АЕ).			*/
#else
	/** Current distance to the Earth (in AUs).		*/
#endif
	double		dst;
} SCASun;

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает геометрическую среднюю долготу Солнца на заданный
 * момент времени.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param[out] L Геометрическая средняя долгота Солнца.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates Sun's geometric mean longitude for given instance of time.
 * @param jd Julian Day corresponding to calculation instance.
 * @param[out] L Geometric mean longitude of the Sun.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int	sca_sun_get_mean_longitude	(double jd, SCAAngle *L);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает геометрическую истинную долготу Солнца на заданный
 * момент времени.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param[out] T Геометрическая истинная долгота Солнца.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates Sun's geometric true longitude for given instance of time.
 * @param jd Julian Day corresponding to calculation instance.
 * @param[out] T Geometric true longitude of the Sun.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int	sca_sun_get_true_longitude	(double jd, SCAAngle *T);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает среднюю аномалию Солнца на заданный момент времени.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param[out] M Средняя аномалия Солнца.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates Sun's mean anomaly for given instance of time.
 * @param jd Julian Day corresponding to calculation instance.
 * @param[out] M Mean anomaly of the Sun.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int	sca_sun_get_mean_anomaly	(double jd, SCAAngle *M);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает положение Солнца на заданный момент времени.
 * @param[out] sun Объект #SCASun для обновления.
 * @param date Дата в UT для выполнения расчёта.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates Sun's position for given date.
 * @param[out] s #SCASun object for updating.
 * @param date Date in UT to perform calculation for.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int	sca_sun_update_date		(SCASun *s, SCADate *date);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает местные координаты Солнца с учётом параллакса.
 * @param sun Объект #SCASun.
 * @param loc Положение наблюдателя.
 * @param[out] A Азимут (положительный на запад от юга), может быть NULL.
 * @param[out] h Высота над горизонтом, может быть NULL.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 * @note Для учёта рефракции используйте функцию sca_earth_get_refraction().
 */
#else
/**
 * @brief Calculates local coordinates of the Sun including parallax corrections.
 * @param s #SCASun object.
 * @param loc Observer location.
 * @param[out] A Azimuth (positive westward from south), may be NULL.
 * @param[out] h Altitude above horizon, may be NULL.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 * @note To take in account refraction use sca_earth_get_refraction() routine.
 */
#endif
int	sca_sun_get_local_coordinates	(SCASun *s, SCAGeoLocation *loc, SCAAngle *A, SCAAngle *h);

SCA_END_DECLS

#endif /* __SCASUN_H__ */
