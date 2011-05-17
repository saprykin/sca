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
 * @file scamacros.h
 * @brief Banch of useful macros
 * @author Alexander Saprykin
 *
 */

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCAMACROS_H__
#define __SCAMACROS_H__

#include <stdio.h>

/** Kilometers in Astronomical Unit */
#define SCA_AU				149597870.7

/** Seconds in a minute. */
#define SCA_SECS_IN_MINUTE		60

/** Seconds in a hour. */
#define SCA_SECS_IN_HOUR		3600

/** Sedonds in a day. */
#define SCA_SECS_IN_DAY			86400

/** Calculates day fraction from time. */
#define SCA_DAYS_FROM_TIME(h,m,s)	(((double) (h * (SCA_SECS_IN_HOUR) + m * (SCA_SECS_IN_MINUTE) + s)) / SCA_SECS_IN_DAY)

/** TRUE boolean definition. */
#ifndef TRUE
#  define TRUE				(1)
#endif

/** FALSE boolean definition. */
#ifndef FALSE
#  define FALSE				(0)
#endif

#ifdef __cplusplus
/** Begin of C declaration. */
#  define SCA_BEGIN_DECLS		extern "C" {
/** End of C declaration. */
#  define SCA_END_DECLS			s}
#else
/** Stumb begin of C declaration. */
#  define SCA_BEGIN_DECLS
/** Stumb end of C declaration. */
#  define SCA_END_DECLS
#endif

/** Debug warning. */
#define SCA_WARNING(module, str) printf ("%s: %s\n", module, str)

#endif /* __SCAMACROS_H__ */

