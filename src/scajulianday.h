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
 * @file scajulianday.h
 * @brief Работа с юлианскими днями
 * @author Alexander Saprykin
 *
 * Юлианский день (JD) - это непрерывный отсчёт дней (и их частей) от начала
 * -4712 года. Исторические года до нашей эры начинаются с 0 астрономического
 * года и продолжаются в отрицательную сторону. Библиотека SCALib использует
 * астрономическое исчисление лет. Например, 1, 5 и 9 года до нашей эры соответствуют
 * 0, -4 и -8 астрономическим годам соответственно. Високосные года могут быть
 * проверены делением на 4 (остаток должен быть 0). Библиотека SCALib устанавливает
 * 15 октября 1582 года в качестве начала григорианского календаря, хотя календарная
 * реформа была проведена в разных странах в разные года. Все даты используются во
 * всемирном времени (UT). Юлианский день не может быть отрицательным.
 *
 * Для установки времени дня используется макрос #SCA_DAYS_FROM_TIME:
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
 * Данный код получает юлианский день для 14 февраля 2011 года в 12:35:20 UT. 
 */
#else
/**
 * @file scajulianday.h
 * @brief Julian Day utilities
 * @author Alexander Saprykin
 *
 * The Julian Day (JD) is a continuous count of the days (and its fractions)
 * from the beginning of the -4712 year. Historical B.C. years start from the
 * 0 astronomical year and goes negative. SCALib library uses astronomical years
 * notation. For example, 1, 5 and 9 B.C. years corresponds to 0, -4 and -8
 * astronomical years respectively. Leap years can be checked by division of
 * 4 (remainder must be 0). SCALib library sets October 15, 1582 as the beginning of 
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
 */
#endif

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCAJULIANDAY_H__
#define __SCAJULIANDAY_H__

#include <scamacros.h>
#include <scaangle.h>

SCA_BEGIN_DECLS

#ifdef DOXYGEN_RUSSIAN
/** Юлианский день для эпохи J2000. */
#else
/** Julian Day for J2000 epoch. */
#endif
#define SCA_JD_EPOCH_2000 2451545.0

#ifdef DOXYGEN_RUSSIAN
/** Перечисление месяцев. */
#else
/** Months enumeration. */
#endif
typedef enum _SCAMonth {
#ifdef DOXYGEN_RUSSIAN
	/** Январь	*/
#else
	/** January	*/
#endif
	SCA_MONTH_JANUARY	= 1,

#ifdef DOXYGEN_RUSSIAN
	/** Февраль	*/
#else
	/** February	*/
#endif
	SCA_MONTH_FEBRUARY	= 2,

#ifdef DOXYGEN_RUSSIAN
	/** Март	*/
#else
	/** March	*/
#endif
	SCA_MONTH_MARCH		= 3,

#ifdef DOXYGEN_RUSSIAN
	/** Апрель	*/
#else
	/** April	*/
#endif
	SCA_MONTH_APRIL		= 4,

#ifdef DOXYGEN_RUSSIAN
	/** Май		*/
#else
	/** May		*/
#endif
	SCA_MONTH_MAY		= 5,

#ifdef DOXYGEN_RUSSIAN
	/** Июнь	*/
#else
	/** June	*/
#endif
	SCA_MONTH_JUNE		= 6,

#ifdef DOXYGEN_RUSSIAN
	/** Июль	*/
#else
	/** July	*/
#endif
	SCA_MONTH_JULY		= 7,

#ifdef DOXYGEN_RUSSIAN
	/** Август	*/
#else
	/** August	*/
#endif
	SCA_MONTH_AUGUST	= 8,

#ifdef DOXYGEN_RUSSIAN
	/** Сентябрь	*/
#else
	/** September	*/
#endif
	SCA_MONTH_SEPTEMBER	= 9,

#ifdef DOXYGEN_RUSSIAN
	/** Октябрь	*/
#else
	/** October	*/
#endif
	SCA_MONTH_OCTOBER	= 10,

#ifdef DOXYGEN_RUSSIAN
	/** Ноябрь	*/
#else
	/** November	*/
#endif
	SCA_MONTH_NOVEMBER	= 11,

#ifdef DOXYGEN_RUSSIAN
	/** Декабрь	*/
#else
	/** December	*/
#endif
	SCA_MONTH_DECEMBER	= 12
} SCAMonth;

#ifdef DOXYGEN_RUSSIAN
/** Перечисление дней недели. */
#else
/** Week days enumeration. */
#endif
typedef enum _SCAWeekDay {
#ifdef DOXYGEN_RUSSIAN
	/** Воскресенье	*/
#else
	/** Sunday	*/
#endif
	SCA_WEEKDAY_SUNDAY	= 0,

#ifdef DOXYGEN_RUSSIAN
	/** Понедельник	*/
#else
	/** Monday	*/
#endif
	SCA_WEEKDAY_MONDAY	= 1,

#ifdef DOXYGEN_RUSSIAN
	/** Вторник	*/
#else
	/** Tuesday	*/
#endif
	SCA_WEEKDAY_TUESDAY	= 2,

#ifdef DOXYGEN_RUSSIAN
	/** Среда	*/
#else
	/** Wednesday	*/
#endif
	SCA_WEEKDAY_WEDNESDAY	= 3,

#ifdef DOXYGEN_RUSSIAN
	/** Четверг	*/
#else
	/** Thursday	*/
#endif
	SCA_WEEKDAY_THURSDAY	= 4,

#ifdef DOXYGEN_RUSSIAN
	/** Пятница	*/
#else
	/** Friday	*/
#endif
	SCA_WEEKDAY_FRIDAY	= 5,

#ifdef DOXYGEN_RUSSIAN
	/** Суббота	*/
#else
	/** Saturday	*/
#endif
	SCA_WEEKDAY_SATURDAY	= 6
} SCAWeekDay;

#ifdef DOXYGEN_RUSSIAN
/** Структура с календарной датой. */
#else
/** Calendar date structure. */
#endif
typedef struct _SCADate {
#ifdef DOXYGEN_RUSSIAN
	/** Календарный год, года д.н.э. начинаются с 0 и продолжаются в
	 *  отрицательную сторону. */
#else
	/** Calendar year, B.C. starts from the 0 and goes negative. */
#endif
	int		year;

#ifdef DOXYGEN_RUSSIAN
	/** Календарный месяц. */
#else
	/** Calendar month. */
#endif
	SCAMonth	month;

#ifdef DOXYGEN_RUSSIAN
	/** Календарный день (включая суточное время), начинается с 1.0. */
#else
	/** Calendar day (including time), starts from 1.0. */
#endif
	double		day;
} SCADate;

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает юлианский день из календарной даты.
 * @param date Дата для преобразования.
 * @return Значение в юлианских днях или отрицательное число, если @a date равна NULL.
 * @since 0.0.1
 *
 * Если необходимо преобразовать дату с учетом суточного времени, то надо
 * установить поле @a day в #SCADate с учётом дробной части. Для этого лучше использовать
 * макрос #SCA_DAYS_FROM_TIME, который преобразует время из формата чч:мм:сс (24-часовая
 * запись) в соответствующую часть дня.
 */
#else
/**
 * @brief Calculates Julian Day from calendar date.
 * @param date Date to convert.
 * @return Value of Julian Days, or negative value if @a date is NULL.
 * @since 0.0.1
 *
 * If you need to convert date with corresponding time, you should
 * set @a day field in #SCADate with decimals. Consider using #SCA_DAYS_FROM_TIME
 * macros to convert time from hh:mm:ss (24h notation) format to the
 * days value.
 */
#endif
double		sca_jd_from_calendar_date	(const SCADate *date);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Преобразует юлианский день в каледарную дату.
 * @param jd Юлианский день для преобразования.
 * @param[out] date Структура #SCADate для выходного результата.
 * @return 0 в случае успеха, -1, если @a date равен NULL, или @a jd
 * отрицателен.
 * @since 0.0.1
 *
 * Данная функция преобразует юлианский день в дату григорианского календаря.
 */
#else
/**
 * @brief Converts Julian Day to calendar date.
 * @param jd Julian Day to convert.
 * @param[out] date #SCADate structure to hold the result.
 * @return 0 in case of success, -1 if @a date is NULL or @a jd
 * is negative.
 * @since 0.0.1
 *
 * This function converts Julian Day to Gregorian calendar date.
 */
#endif
int		sca_jd_to_calendar_date		(double jd, SCADate *date);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Определяет день недели, на который приходится юлианский день.
 * @param jd Юлианский день для определения дня недели.
 * @param[out] weekday День недели.
 * @return 0 в случае успеха, -1, если @a weekday равен NULL, или @a jd
 * отрицателен.
 * @since 0.0.1
 */
#else
/**
 * @brief Determines the week day of the given Julian Day.
 * @param jd Julian Day to get week day for.
 * @param[out] weekday Day of the week.
 * @return 0 in case of success, -1 if @a weekday is NULL or @a jd
 * is negative.
 * @since 0.0.1
 */
#endif
int		sca_jd_get_weekday		(double jd, SCAWeekDay *weekday);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает номер дня в году.
 * @param jd Юлианский день для расчёта номера дня в году.
 * @return Номер дня в году (от 1 до 365 или 366 для високосных годов)
 * в случае успеха, -1, если @a jd отрицателен.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates the number of the day in the year.
 * @param jd Julian Day to calculate number in the year for.
 * @return Number of the day in the year (from 1 to 365 or 366 for leap years)
 * in case of success, -1 if @a jd is negative.
 * @since 0.0.1
 */
#endif
int		sca_jd_get_day_of_year		(double jd);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает юлианский день по году и номеру дня в году.
 * @param year Год для расчёта.
 * @param num Номер дня в году @a year. Начинается от 1 и до 365 или
 * 366 (для високосных годов).
 * @return Юлианский день для соответствующего года и дня в году в случае
 * успеха, отрицательное число, если @a num <= 0 или @a year < -4712.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates Julian Day by given year and number of the day in it.
 * @param year Year to calculate for.
 * @param num Number of the day in the @a year. Starts from 1 to 365 or
 * 366 (for leap years).
 * @return Julian Day for corresponding year and day number in case of
 * success, negative value if @a num <= 0 or @a year < -4712.
 * @since 0.0.1
 */
#endif
double		sca_jd_from_day_of_year		(int year, int num);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает гринвичское истинное звёздное время.
 * @param jd Юлианский день для расчёта.
 * @param[out] sidereal Звёздное время.
 * @return 0 в случае успеха, иначе -1.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates apparent sidereal at Greenwich.
 * @param jd Julian Day for calculation.
 * @param[out] sidereal Sidereal time.
 * @return 0 in case of success, -1 otherwise.
 * @since 0.0.1
 */
#endif
int		sca_jd_get_sidereal_time	(double jd, SCAAngle *sidereal);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает количество столетий от эпохи J2000.
 * @param jd Текущая эпоха в юлианских днях.
 * @return Количество столетий от эпохи J2000.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates centuries since J2000 epoch.
 * @param jd Current epoch in Julian Days.
 * @return Centuries since J2000 epoch.
 * @since 0.0.1
 */
#endif
double		sca_jd_get_centuries_2000	(double jd);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает количество тысячелетий от эпохи J2000.
 * @param jd Текущая эпоха в юлианских днях.
 * @return Количество тысячелетий от эпохи J2000.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates millenniums since J2000 epoch.
 * @param jd Current epoch in Julian Days.
 * @return Millenniums since J2000 epoch.
 * @since 0.0.1
 */
#endif
double		sca_jd_get_millenia_2000	(double jd);	

SCA_END_DECLS

#endif /* __SCAJULIANDAY_H__ */

