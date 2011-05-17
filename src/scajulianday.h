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
 * @file scajulianday.h
 * @brief Julian Day utilities
 * @author Alexander Saprykin
 *
 * The Julian Day (JD) is a continuous count of the days (and its fractions)
 * from the beginning of the -4712 year. Historical B.C. years start from the
 * 0 astronomical year and goes negative. SCA library uses astronomical years
 * notation. For example, 1, 5 and 9 B.C. years corresponds to 0, -4 and -8
 * astronomical years respectively. Leap years can be checked by division of
 * 4 (remainder must be 0). SCA library sets October 15, 1582 as the begining of 
 * Gregorian calendar, though reform was taken at different years in different
 * countries. All dates are specified in Universal Time (UT).
 * JD can't be negative.
 *
 * To set up time of the day use #SCA_DAYS_FROM_TIME macros:
 * @code
 * SCADate	date;
 * double	jd;
 *
 * date.year	= 2011;
 * date.month	= SCA_MONTH_FEBRUARY;
 * date.day	= 14 + SCA_DAYS_FROM_TIME (12, 35, 20);
 *
 * jd = sca_jd_from_calendar_date (&date);
 * @endcode
 * This code gets Julian Day for February 14, 2011 at 12:35:20 UT. 
 *
 */

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCAJULIANDAY_H__
#define __SCAJULIANDAY_H__

#include <scamacros.h>
#include <scaangle.h>

SCA_BEGIN_DECLS

/** Julian Day for J2000 epoch. */
#define SCA_JD_EPOCH_2000 2451545.0

/** Monthes enumeration. */
typedef enum _SCAMonth {
	SCA_MONTH_JANUARY	= 1,	/**< January	*/
	SCA_MONTH_FEBRUARY	= 2,	/**< February	*/
	SCA_MONTH_MARCH		= 3,	/**< March	*/
	SCA_MONTH_APRIL		= 4,	/**< April	*/
	SCA_MONTH_MAY		= 5,	/**< May	*/
	SCA_MONTH_JUNE		= 6,	/**< June	*/
	SCA_MONTH_JULY		= 7,	/**< July	*/
	SCA_MONTH_AUGUST	= 8,	/**< August	*/
	SCA_MONTH_SEPTEMBER	= 9,	/**< September	*/
	SCA_MONTH_OCTOBER	= 10,	/**< October	*/
	SCA_MONTH_NOVEMBER	= 11,	/**< November	*/
	SCA_MONTH_DECEMBER	= 12	/**< December	*/
} SCAMonth;

/** Week days enumeration. */
typedef enum _SCAWeekDay {
	SCA_WEEKDAY_SUNDAY	= 0,	/**< Sunday	*/
	SCA_WEEKDAY_MONDAY	= 1,	/**< Monday	*/
	SCA_WEEKDAY_TUESDAY	= 2,	/**< Tuesday	*/
	SCA_WEEKDAY_WEDNESDAY	= 3,	/**< Wednesday	*/
	SCA_WEEKDAY_THURSDAY	= 4,	/**< Thursday	*/
	SCA_WEEKDAY_FRIDAY	= 5,	/**< Friday	*/
	SCA_WEEKDAY_SATURDAY	= 6	/**< Saturday	*/
} SCAWeekDay;

/** Date structure. */
typedef struct _SCADate {
	int		year;		/**< Calendar year, B.C. starts from the 0 and goes negative. */
	SCAMonth	month;		/**< Calendar month. */
	double		day;		/**< Calendar day (including time), starts from 1.0. */
} SCADate;

/**
 * @brief Calculates Julian Day from calendar date.
 * @param date Date to convert.
 * @return Value of Julian Days, or negative value if @a date is NULL.
 * @since 0.0.1
 *
 * If you need to convert date with corresponding time, you should
 * set #SCADate.day field with decimals. Consider using #SCA_DAYS_FROM_TIME
 * macros to convert time from hh:mm:ss (24h notation) format to the
 * days value.
 */
double		sca_jd_from_calendar_date	(SCADate *date);

/**
 * @brief Converts Julian Day to calendar date.
 * @param jd Julian Day to convert.
 * @param date #SCADate structure to hold the result.
 * @return 0 in case of success, -1 if @a date is NULL or @a jd
 * is negative.
 * @since 0.0.1
 *
 * This function converts Julian Day to Gregorian calendar date.
 */
int		sca_jd_to_calendar_date		(double jd, SCADate *date);

/**
 * @brief Determines the week day of the given Julian Day.
 * @param jd Julian Day to get week day for.
 * @param weekday Output parameter for holding the result.
 * @return 0 in case of success, -1 if @a weekday is NULL or @a jd
 * is negative.
 * @since 0.0.1
 */
int		sca_jd_get_weekday		(double jd, SCAWeekDay *weekday);

/**
 * @brief Calculates the number of the day in the year.
 * @param jd Julian Day to calculate number in the year for.
 * @return Number of the day in the year (from 1 to 365 or 366 for leap years)
 * in case of success, -1 if @a jd is negative.
 * @since 0.0.1
 */
int		sca_jd_get_day_of_year		(double jd);

/**
 * @brief Calculates Julian Day by given year and number of the day in it.
 * @param year Year to calculate for.
 * @param num Number of the day in the @a year. Starts from 1 to 365 or
 * 366 (for leap years).
 * @return Julian Day for corresponding year and day number in case of
 * success, negative value if @a num <= 0 or @a year < -4712.
 * @since 0.0.1
 */
double		sca_jd_from_day_of_year		(int year, int num);

/**
 * @brief Calculates apparent sidereal at Greenwich.
 * @param jd Julian Day for calculation.
 * @param sidereal Output sidereal time.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
int		sca_jd_get_sidereal_time	(double jd, SCAAngle *sidereal);

/**
 * @brief Calculates centuries since J2000 epoch.
 * @param jd Current epoch.
 * @return Centuries since J2000 epoch.
 * @since 0.0.1
 */
double		sca_jd_get_centuries_2000	(double jd);

/**
 * @brief Calculates millenniums since J2000 epoch.
 * @param jd Current epoch.
 * @return Millenniums since J2000 epoch.
 * @since 0.0.1
 */
double		sca_jd_get_millenia_2000	(double jd);	

SCA_END_DECLS

#endif /* __SCAJULIANDAY_H__ */

