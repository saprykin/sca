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
 * @file scamacros.h
 * @brief Полезные макросы
 * @author Александр Сапрыкин
 */
#else
/**
 * @file scamacros.h
 * @brief Bunch of useful macros
 * @author Alexander Saprykin
 */
#endif

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCAMACROS_H__
#define __SCAMACROS_H__

#include <stdio.h>

#ifdef DOXYGEN_RUSSIAN
/** Километров в астрономической единице. */
#else
/** Kilometers in Astronomical Unit. */
#endif
#define SCA_AU				149597870.7

#ifdef DOXYGEN_RUSSIAN
/** Секунд в минуте.*/
#else
/** Seconds in a minute. */
#endif
#define SCA_SECS_IN_MINUTE		60

#ifdef DOXYGEN_RUSSIAN
/** Секунд в часе. */
#else
/** Seconds in a hour. */
#endif
#define SCA_SECS_IN_HOUR		3600

#ifdef DOXYGEN_RUSSIAN
/** Секунд в дне. */
#else
/** Sedonds in a day. */
#endif
#define SCA_SECS_IN_DAY			86400

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает часть дня по суточному времени (24-часовая запись).
 * @param h Часы.
 * @param m Минуты.
 * @param s Секунды.
 */
#else
/**
 * @brief Calculates day fraction from time (24h notation).
 * @param h Hours.
 * @param m Minutes.
 * @param s Seconds.
 */
#endif
#define SCA_DAYS_FROM_TIME(h,m,s)	(((double) (h * (SCA_SECS_IN_HOUR) + m * (SCA_SECS_IN_MINUTE) + s)) / SCA_SECS_IN_DAY)

#ifdef DOXYGEN_RUSSIAN
/** Определение TRUE для булевого типа. */
#else
/** TRUE boolean definition. */
#endif
#ifndef TRUE
#  define TRUE				(1)
#endif

#ifdef DOXYGEN_RUSSIAN
/** Определение FALSE для булевого типа. */
#else
/** FALSE boolean definition. */
#endif
#ifndef FALSE
#  define FALSE				(0)
#endif

#ifdef __cplusplus

#ifdef DOXYGEN_RUSSIAN
/** Начало деклараций C. */
#else
/** Begin of C declarations. */
#endif
#  define SCA_BEGIN_DECLS		extern "C" {

#ifdef DOXYGEN_RUSSIAN
/** Завершение деклараций C. */
#else
/** End of C declarations. */
#endif
#  define SCA_END_DECLS			}

#else

#ifdef DOXYGEN_RUSSIAN
/** Заглушка начала деклараций C. */
#else
/** Begin stub for C declarations. */
#endif
#  define SCA_BEGIN_DECLS

#ifdef DOXYGEN_RUSSIAN
/** Заглушка завершения деклараций C. */
#else
/** End stub for C declarations. */
#endif
#  define SCA_END_DECLS

#endif

#ifdef DOXYGEN_RUSSIAN
/** Отладочное предупреждение. */
#else
/** Debug warning. */
#endif
#define SCA_WARNING(module, str) printf ("%s: %s\n", module, str)

#endif /* __SCAMACROS_H__ */

