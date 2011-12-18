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
 * @file scaangle.h
 * @brief Работа с углами
 * @author Сапрыкин Александр
 *
 * Углы могут быть представлены различными способами: градусы/минуты/секунды,
 * часы/минуты/секунды, радианы и т.д.
 * #SCAAngle используется для унификации представления углов. Внутренне
 * значение угла хранится в виде числа с плавающей точкой в градусах. Можно создавать #SCAAngle из
 * любых форм представления, упомянутых выше, и преобразовывать из одной формы
 * представления в другую.
 * Следует учесть, что при задании отрицательных углов знак берётся из первого ненулевого
 * компонента. Это же правило действует и при получении компонентов углов (для отрицательного
 * угла первый ненулевой компонент будет отрицательным). Например, для угла -30'34'' часовая
 * составляющая будет равна 0, а минутная составляющая будет равна -30.
 * Все углы автоматически приводятся к 360 градусам перед использованием, например угол в 365°
 * будет приведён к 5°.
 *
 * Создание угла 57°34'24.25'':
 * @code
 * SCAAngle ang = sca_angle_from_degrees (57, 34, 24, 250);
 * @endcode
 * Последний параметр используется для миллисекундной составляющей.
 *
 * Создание угла 19ч:22м:35.123с:
 * @code
 * SCAAngle ang = sca_angle_from_hours (19, 22, 35, 123);
 * @endcode
 *
 * Создание угла 43°.5326:
 * @code
 * SCAAngle ang = sca_angle_from_decimal_degrees (43.5326);
 * @endcode
 *
 * Создание угла -34'20'':
 * @code
 * SCAAngle ang = sca_angle_from_degrees (0, -34, 20, 0);
 * @endcode
 *
 * Для преобразования #SCAAngle в/из радиан можно использовать функции sca_angle_to_radians()
 * и sca_angle_from_radians(). Или умножить угол на значения, определённые макросами
 * #SCA_ANGLE_DEG_TO_RAD и #SCA_ANGLE_RAD_TO_DEG соответственно.
 *
 * Углы можно складывать и вычитать, а также делить и умножать на число:
 * @code
 * SCAAngle a, b;
 * 
 * a = sca_angle_from_decimal_degrees (23.145);
 * b = sca_angle_from_decimal_degrees (14.356);
 * 
 * a += b;
 * b *= 2.0;
 *
 * printf ("%f, %f\n", a, b);
 * @endcode
 *
 * Как видно, #SCAAngle можно выводить в поток используя модификатор \%f.
 *
 * Для получения компонент угла в различных представлениях имеется семейство функций
 * sca_angle_get_*.
 *
 * Не следует использовать #SCAAngle напрямую как число - лучше использовать представленные
 * ниже функции.
 */
#else
/**
 * @file scaangle.h
 * @brief Angle routines
 * @author Alexander Saprykin
 *
 * Angles can be represented in different ways: degs/arcmins/arcsecs,
 * hours/mins/secs, radians and so on.
 * #SCAAngle is used to handle angle in generic way. Actually angle is
 * stored as decimal degree value. You can create #SCAAngle from
 * different forms mentioned above, and you can also freely convert
 * them from one to another.
 * Note that negative angles use first non-zero member to hold the sign.
 * This rule is used when while getting angle portions (for the negative
 * angle portion of the first non-zero member will be negative). For
 * example, for angle -30'34'' hours portion will be 0, and minutes
 * portion will be -30.
 * All angles are automaticaly reduced before taking any operation,
 * i.e. 365° will be reduced to 5°.
 *
 * Create 57°34'24.25'' angle:
 * @code
 * SCAAngle ang = sca_angle_from_degrees (57, 34, 24, 250);
 * @endcode
 * Note that last parameter is used for milliarcseconds portion.
 *
 * Create 19h:22m:35.123s angle:
 * @code
 * SCAAngle ang = sca_angle_from_hours (19, 22, 35, 123);
 * @endcode
 *
 * Create 43°.5326 angle:
 * @code
 * SCAAngle ang = sca_angle_from_decimal_degrees (43.5326);
 * @endcode
 *
 * Create -34'20'' angle:
 * @code
 * SCAAngle ang = sca_angle_from_degrees (0, -34, 20, 0);
 * @endcode
 *
 * To convert #SCAAngle to or from radians use sca_angle_to_radians()
 * and sca_angle_from_radians(). Or you can multiply angle by
 * #SCA_ANGLE_DEG_TO_RAD or #SCA_ANGLE_RAD_TO_DEG macros.
 *
 * Angles can be added or substracked from each other, and
 * multiplied or divided by any decimal number:
 * @code
 * SCAAngle a, b;
 * 
 * a = sca_angle_from_decimal_degrees (23.145);
 * b = sca_angle_from_decimal_degrees (14.356);
 * 
 * a += b;
 * b *= 2.0;
 *
 * printf ("%f, %f\n", a, b);
 * @endcode
 *
 * As you can see, #SCAAngle can be outputed to stream using \%f
 * modifier.
 *
 * To get portions of angle in different notations use
 * sca_angle_get_* family of functions.
 *
 * Try no to use #SCAAngle directly as decimal value - consider
 * using routines described below.
 */
#endif

#if !defined (__SCALIB_H_INSIDE__) && !defined (SCALIB_COMPILATION)
#  error "Header files shouldn't be included directly, consider using <scalib.h> instead."
#endif

#ifndef __SCAANGLE_H__
#define __SCAANGLE_H__

#include <math.h>
#include <sys/types.h>
#include <scamacros.h>

SCA_BEGIN_DECLS

#ifdef DOXYGEN_RUSSIAN
/** Коэффициент перевода градусов в радианы. */
#else
/** Degrees->radians conversion coefficient. */
#endif
#define SCA_ANGLE_DEG_TO_RAD	(M_PI / 180.0)

#ifdef DOXYGEN_RUSSIAN
/** Коэффициент перевода радиан в градусы. */
#else
/** Radians->degrees conversion coefficient. */
#endif
#define SCA_ANGLE_RAD_TO_DEG	(180.0 / M_PI)

#ifdef DOXYGEN_RUSSIAN
/** Определение типа для угла в градусах. */
#else
/** Typedef for degree angle. */
#endif
typedef double SCAAngle;

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Сокращает угол при имеющейся возможности. Например, 480°
 * могут быть сокращены до 120°, или -480° до -120°.
 * @param angle Указатель на угол для сокращения.
 * @since 0.0.1
 */
#else
/**
 * @brief Reduces angle to minimal value if can. For example, 480°
 * can be reduced to 120°, or -480° to -120°.
 * @param angle Angle pointer to reduce.
 * @since 0.0.1
 */
#endif
void		sca_angle_reduce	(SCAAngle *angle);


#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Создаёт #SCAAngle из градусов/минут/секунд.
 * @param degrees Составляющая угла в градусах (от 0 до 360).
 * @param arcmins Составляющая угла в минутах дуги. 1 минута дуги = 1/60 градуса.
 * @param arcsecs Составляющая угла в секундах дуги. 1 секунда дуги = 1/60 минуты дуги.
 * @param marcsecs Составляющая угла в миллисекундах дуги. 1 миллисекунда дуги = 1/1000 секунды дуги.
 * @return #SCAAngle с соответствующим значением.
 * @since 0.0.1
 *
 * Отрицательный угол задаётся путём использования отрицательного значения у первого
 * ненулевого компонента. Например, угол -30° 23' 50'' может быть задан используя
 * параметры (-30, 23, 50, 0). А угол -24' 34'' может быть задан используя параметры
 * (0, -24, 34, 0). Знаки всех остальных компонент будут игнорироваться (использоваться
 * как положительные).
 */
#else
/**
 * @brief Creates #SCAAngle from degs/arcmins/arcsecs.
 * @param degrees Degrees value (from 0 to 360).
 * @param arcmins Arcminutes value. 1 arcminute = 1/60 degree.
 * @param arcsecs Arcseconds value. 1 arcsecond = 1/60 arcminute.
 * @param marcsecs Milliarcseconds value. 1 milliarcsecond = 1/1000 arcsecond.
 * @return #SCAAngle with corresponding value.
 * @since 0.0.1
 *
 * Negative angle can be specified by negative value for the first
 * non-zero parameter. For example, -30° 23' 50'' angle can be specified
 * using (-30, 23, 50, 0) parameters. And -24' 34'' angle can be specified
 * using (0, -24, 34, 0) parameters. All other negative parameters will
 * be ignored (used as positive).
 */
 #endif
SCAAngle	sca_angle_from_degrees	(int degrees, int arcmins, int arcsecs, double marcsecs);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Создаёт #SCAAngle из часов/минут/секунд.
 * @param hours Составляющая угла в часах (от 0 до 24). 1 час = 15 градусов.
 * @param mins Составляющая угла в минутах. 1 минута = 1/60 часа.
 * @param secs Составляющая угла в секундах. 1 секунда = 1/60 минуты.
 * @param msecs Составляющая угла в миллисекундах. 1 миллисекунда = 1/1000 секунды.
 * @return #SCAAngle с соответствующим значением.
 * @since 0.0.1
 *
 * Отрицательный угол задаётся путём использования отрицательного значения у первого
 * ненулевого компонента. Например, угол -12ч 23м 50с может быть задан используя
 * параметры (-12, 23, 50, 0). А угол -20м 34с может быть задан используя параметры
 * (0, -20, 34, 0). Знаки всех остальных компонент будут игнорироваться (использоваться
 * как положительные).
 */
#else
/**
 * @brief Creates #SCAAngle from hours/mins/secs.
 * @param hours Hours value (from 0 to 24). 1 hour = 15 degrees.
 * @param mins Minutes value. 1 minute = 1/60 hour.
 * @param secs Seconds value. 1 second = 1/60 minute.
 * @param msecs Milliseconds value. 1 millisecond = 1/1000 second.
 * @return #SCAAngle with corresponding value.
 * @since 0.0.1
 *
 * Negative angle can be specified by negative value for the first
 * non-zero parameter. For example, -12h 23m 50s angle can be specified
 * using (-12, 23, 50, 0) parameters. And -20m 34s angle can be specified
 * using (0, -20, 34, 0) parameters. All other negative parameters will
 * be ignored (used as positive).
 */
#endif
SCAAngle	sca_angle_from_hours	(int hours, int mins, int secs, double msecs);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Создаёт #SCAAngle из радиан.
 * @param rads Значение в радианах.
 * @return #SCAAngle с соответствующим значением.
 * @since 0.0.1
 */
#else
/**
 * @brief Creates #SCAAngle from radians.
 * @param rads Radians value.
 * @return #SCAAngle with corresponding value.
 * @since 0.0.1
 */
#endif
SCAAngle	sca_angle_from_radians	(double rads);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Представляет #SCAAngle в виде числа с плавающей точкой в градусах (double).
 * @param angle Угол для представления.
 * @return Угол в градусах.
 * @since 0.0.1
 */
#else
/**
 * @brief Represents #SCAAngle in degrees as a decimal (double).
 * @param angle Angle to represent.
 * @return Angle in degrees.
 * @since 0.0.1
 */
#endif
double		sca_angle_to_degrees	(SCAAngle angle);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Представляет #SCAAngle в виде числа с плавающей точкой в часах (double).
 * @param angle Угол для представления.
 * @return Угол в часах.
 * @since 0.0.1
 */
#else
/**
 * @brief Represents #SCAAngle in hours as a decimal (double).
 * @param angle Angle to represent.
 * @return Angle in hours.
 * @since 0.0.1
 */
#endif
double		sca_angle_to_hours	(SCAAngle angle);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Представляет #SCAAngle в радианах.
 * @param angle Угол для представления.
 * @return Угол в радианах.
 * @since 0.0.1
 */
#else
/**
 * @brief Represents #SCAAngle in radians.
 * @param angle Angle to represent.
 * @return Angle in radians.
 * @since 0.0.1
 */
#endif
double		sca_angle_to_radians	(SCAAngle angle);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Получает градусную составляющую угла.
 * @param angle Угол для получения градусной составляющей.
 * @return Градусную составляющую угла @a angle.
 * @since 0.0.1
 */
#else
/**
 * @brief Gets degrees portion of the angle.
 * @param angle Angle to get portion from.
 * @return Degrees portion of the @a angle.
 * @since 0.0.1
 */
#endif
int		sca_angle_get_degrees	(SCAAngle angle);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Получает минутную (дуги) составляющую угла.
 * @param angle Угол для получения минутной составляющей.
 * @return Минутную составляющую угла @a angle.
 * @since 0.0.1
 */
#else
/**
 * @brief Gets arcminutes portion of the angle.
 * @param angle Angle to get portion from.
 * @return Arcminutes portion of the @a angle.
 * @since 0.0.1
 */
#endif
int		sca_angle_get_arcmins	(SCAAngle angle);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Получает секундную (дуги) составляющую угла.
 * @param angle Угол для получения секундной составляющей.
 * @return Секундную составляющую угла @a angle.
 * @since 0.0.1
 */
#else
/**
 * @brief Gets arcseconds portion of the angle.
 * @param angle Angle to get portion from.
 * @return Arcseconds portion of the @a angle.
 * @since 0.0.1
 */
#endif
int		sca_angle_get_arcsecs	(SCAAngle angle);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Получает миллисекундную (дуги) составляющую угла.
 * @param angle Угол для получения миллисекундной составляющей.
 * @return Миллисекундную составляющую угла @a angle.
 * @since 0.0.1
 */
#else
/**
 * @brief Gets milliarcesonds portion of the angle.
 * @param angle Angle to get portion from.
 * @return Milliarcseconds portion of the @a angle.
 * @since 0.0.1
 */
#endif
double		sca_angle_get_marcsecs	(SCAAngle angle);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Получает часовую составляющую угла.
 * @param angle Угол для получения часовой составляющей.
 * @return Часовую составляющую угла @a angle.
 * @since 0.0.1
 */
#else
/**
 * @brief Gets hours portion of the angle.
 * @param angle Angle to get portion from.
 * @return Hours portion of the @a angle.
 * @since 0.0.1
 */
#endif
int		sca_angle_get_hours	(SCAAngle angle);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Получает минутную составляющую угла.
 * @param angle Угол для получения минутной составляющей.
 * @return Минутную составляющую угла @a angle.
 * @since 0.0.1
 */
#else
/**
 * @brief Gets minutes portion of the angle.
 * @param angle Angle to get portion from.
 * @return Minutes portion of the @a angle.
 * @since 0.0.1
 */
#endif
int		sca_angle_get_mins	(SCAAngle angle);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Получает секундную составляющую угла.
 * @param angle Угол для получения секундной составляющей.
 * @return Секундную составляющую угла @a angle.
 * @since 0.0.1
 */
#else
/**
 * @brief Gets seconds portion of the angle.
 * @param angle Angle to get portion from.
 * @return Seconds portion of the @a angle.
 * @since 0.0.1
 */
#endif
int		sca_angle_get_secs	(SCAAngle angle);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Получает миллисекундную составляющую угла.
 * @param angle Угол для получения миллисекундной составляющей.
 * @return Миллисекундную составляющую угла @a angle.
 * @since 0.0.1
 */
#else
/**
 * @brief Gets milleseconds portion of the angle.
 * @param angle Angle to get portion from.
 * @return Milliseconds portion of the @a angle.
 * @since 0.0.1
 */
#endif
double		sca_angle_get_msecs	(SCAAngle angle);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает синус угла.
 * @param angle Угол для расчёта синуса.
 * @return Синус угла @a angle.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates angle's Sine.
 * @param angle Angle to calculate Sine for.
 * @return Sine of the @a angle.
 * @since 0.0.1
 */
#endif
double		sca_angle_get_sin	(SCAAngle angle);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает косинус угла.
 * @param angle Угол для расчёта косинуса.
 * @return Косинус угла @a angle.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates angle's Cosine.
 * @param angle Angle to calculate Cosine for.
 * @return Cosine of the @a angle.
 * @since 0.0.1
 */
#endif
double		sca_angle_get_cos	(SCAAngle angle);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Рассчитывает синус и косинус угла.
 * @param angle Угол для расчёта синуса и косинуса.
 * @param sin_out Выходное значение для синуса, может быть NULL.
 * @param cos_out Выходное значение для косинуса, может быть NULL.
 * @since 0.0.1
 */
#else
/**
 * @brief Calculates both angle's Sine and Cosine.
 * @param angle Angle to calculate Sine and Cosine for.
 * @param sin_out Output Sine value, may be NULL.
 * @param cos_out Output Cosine value, may be NULL.
 * @since 0.0.1
 */
#endif
void		sca_angle_get_sincos	(SCAAngle angle, double *sin_out, double *cos_out);

#ifdef DOXYGEN_RUSSIAN
/**
 * @brief Создаёт #SCAAngle из градусов, представленных в виде числа с плавающей точкой.
 * @param val Значение в градусах (например, 56°.23).
 * @return Созданную структуру #SCAAngle.
 * @since 0.0.1
 */
#else
/**
 * @brief Creates #SCAAngle from the degrees, represented by single
 * decimal value.
 * @param val Degree value in decimal (i.e. 56°.23).
 * @return Newly created #SCAAngle structure.
 * @since 0.0.1
 */
#endif
SCAAngle	sca_angle_from_decimal_degrees	(double	val);

SCA_END_DECLS

#endif /* __SCAANGLE_H__ */

