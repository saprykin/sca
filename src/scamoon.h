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
 * @file scamoon.h
 * @brief Представление Луны
 * @author Александр Сапрыкин
 *
 * #SCAMoon используется для представления Луны в экваториальных координатах.
 * Позиция Луны может быть рассчитана с точностью примерно 10'' по долготе и
 * 4'' по широте для заданного момента времени. Для примера рассчитаем
 * позицию на 22 мая 2011 года в 03:20 UT для Санкт-Петербурга в Российской
 * Федерации (E 30°32'41'', N 60°16'31''):
 * @code
 * SCAMoon		moon;
 * SCADate		date;
 * SCAGeoLocation	loc;
 * SCAAngle		A, h;
 *
 * loc.longitude	= sca_angle_from_degrees (-30, 32, 41, 0.0);
 * loc.latitude		= sca_angle_from_degrees (60, 16, 31, 0.0);
 *
 * date.year	= 2011;
 * date.month	= SCA_MONTH_MAY;
 * date.day	= 22 + SCA_DAYS_FROM_TIME (3, 20, 0);
 *
 * sca_moon_update_date (&moon, &date);
 * sca_moon_get_local_coordinates (&moon, &loc, &A, &h);
 * h += sca_earth_get_refraction (h);
 * @endcode
 * Теперь переменная @a A содержит азимут (положительный на запад от юга, а не на
 * восток от севера!), а переменная @a h содержит высоту над горизонтом с учётом
 * рефракции. Также следует обратить внимание, что восточная долгота отрицательна
 * (в то время как западная - положительна).
 */
#else
/**
 * @file scamoon.h
 * @brief Representation of the Moon
 * @author Alexander Saprykin
 *
 * #SCAMoon is used to represent a Moon with equatorial coordinates. Moon's
 * position can be retrieved with accuracy of about 10'' in longitude and
 * 4'' in latitude for given date. Let's calculate it's position for
 * May 22, 2011 at 03:20 UT for Saint Petersburg in Russian Federation
 * (E 30°32'41'', N 60°16'31''):
 * @code
 * SCAMoon		moon;
 * SCADate		date;
 * SCAGeoLocation	loc;
 * SCAAngle		A, h;
 *
 * loc.longitude	= sca_angle_from_degrees (-30, 32, 41, 0.0);
 * loc.latitude		= sca_angle_from_degrees (60, 16, 31, 0.0);
 *
 * date.year	= 2011;
 * date.month	= SCA_MONTH_MAY;
 * date.day	= 22 + SCA_DAYS_FROM_TIME (3, 20, 0);
 *
 * sca_moon_update_date (&moon, &date);
 * sca_moon_get_local_coordinates (&moon, &loc, &A, &h);
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

#ifndef __SCAMOON_H__
#define __SCAMOON_H__

#include <scamacros.h>
#include <scaangle.h>
#include <scajulianday.h>
#include <scaearth.h>

SCA_BEGIN_DECLS

#ifdef DOXYGEN_RUSSIAN
/** Определение типа для объекта Луны. */
#else
/** Typedef for the Moon object. */
#endif
typedef struct _SCAMoon {
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
	/** Current distance to the Earth (in AU).		*/
#endif
	double		dst;	/**< 		*/
} SCAMoon;


#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает среднюю элонгацию между Луной и Солнцем.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param elong Средняя элонгация, выходной.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates mean elongation of the Moon from the Sun.
 * @param jd Julian Day corresponding to calculation instance of time.
 * @param elong Output mean elongation.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int	sca_moon_get_mean_elongation_from_sun	(double jd, SCAAngle *elong);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает среднюю аномалию Луны.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param anom Средняя аномалия, выходной.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates mean anomaly of the Moon.
 * @param jd Julian Day corresponding to calculation instance of time.
 * @param anom Output mean anomaly.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int	sca_moon_get_mean_anomaly		(double jd, SCAAngle *anom);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает среднюю долготу Луны.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param lon Средняя долгота, выходной.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates mean longitude of the Moon.
 * @param jd Julian Day corresponding to calculation instance of time.
 * @param lon Output mean longitude.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int	sca_moon_get_mean_longitude		(double jd, SCAAngle *lon);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает аргумент широты Луны.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param arg Аргумент широты, выходной.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates argument of the latitude of the Moon.
 * @param jd Julian Day corresponding to calculation instance of time.
 * @param arg Output argument of latitude.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int	sca_moon_get_latitude_argument		(double jd, SCAAngle *arg);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает среднюю долготу восходящего узла Луны.
 * @param jd Юлианский день, соответствующий времени расчёта.
 * @param lon Средняя долгота восходящего узла, выходной.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates mean longitude of the Moon's ascending node.
 * @param jd Julian Day corresponding to calculation instance of time.
 * @param lon Output mean longitude of the ascending node.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int	sca_moon_get_mean_longitude_of_ascnode	(double jd, SCAAngle *lon);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает положение Луны на заданный момент времени.
 * @param moon Объект #SCAMoon для обновления данных.
 * @param date Дата в UT для выполнения расчёта.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 *
 * Данная функция обновляет информацию о положении Луны в объекте @a moon,
 * поэтому ее можно вызывать последовательно с новой датой.
 */
#else
/**
 * @brief Calculates Moon's position for given date.
 * @param moon #SCAMoon object for updating.
 * @param date Date in UT to perform calculation for.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 *
 * This function updates internal data in @a moon object, so you can
 * call it continuously with the new dates.
 */
#endif
int	sca_moon_update_date			(SCAMoon *moon, SCADate *date);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает местные координаты Луны с учётом параллакса.
 * @param moon Объект #SCAMoon.
 * @param loc Положение наблюдателя.
 * @param A Выходной азимут (положительный на запад от юга), может быть NULL.
 * @param h Выходная высота над горизонтом, может быть NULL.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 * @note Для учёта рефракции используйте функцию sca_earth_get_refraction().
 * Данная функция должна вызываться только после хотя бы одного вызова функции
 * sca_moon_update_date() для того же объекта #SCAMoon, иначе результат неопределён.
 */
#else
/**
 * @brief Calculates local coordinates of the Moon including parallax corrections.
 * @param moon #SCAMoon object.
 * @param loc Observer location.
 * @param A Output azimuth (positive westward from south), may be NULL.
 * @param h Output altitude above horizon, may be NULL.
 * @return 0 in case if success, -1 otherwise.
 * @since 0.0.1
 * @note To take in account refraction use sca_earth_get_refraction() routine.
 * This function must be called only after at least one call of sca_moon_update_date()
 * for the same #SCAMoon object or result is undefined.
 */
#endif
int	sca_moon_get_local_coordinates		(SCAMoon *moon, SCAGeoLocation *loc, SCAAngle *A, SCAAngle *h);

SCA_END_DECLS

#endif /* __SCAMOON_H__ */
