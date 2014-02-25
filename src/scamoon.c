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
 * Moon's position can be calculated as by sums of periodic terms.
 * First four coefficients are for Sine and Cosine arguments, the
 * next two are amplitudes for longitude and distance between Earth's
 * and Moon's centers (in kms) respectively. The same tactics is for
 * latitude (the next one data array of coefficients, use Sine).
 * Find the sums and then perform corrections as done below. For
 * example, the first line will make contribution to the sums of l
 * and r (respectively): 6.288774 * sin (dM) and -20905.355 * cos (dM).
 */

#include "scamoon.h"
#include "scasun.h"
#include "scajulianday.h"
#include "scaprivate.h"

#define SCA_MOON_MAX_COEFS	60

/* Periodic terms for ecliptic longitude and geocentral distance (in kms) */
static const double moon_data_lr[SCA_MOON_MAX_COEFS][6] = {
/* D, M, dM, F, l, r  coefficients */
{0.0,	 0.0,	 1.0,	 0.0,	 6.288774,	-20905.355},
{2.0,	 0.0,	-1.0,	 0.0,	 1.274027,	-3699.1110},
{2.0,	 0.0,	 0.0,	 0.0,	 0.658314,	-2955.9680},
{0.0,	 0.0,	 2.0,	 0.0,	 0.213618,	-569.92500},
{0.0,	 1.0,	 0.0,	 0.0,	-0.185116,	 48.888000},
{0.0,	 0.0,	 0.0,	 2.0,	-0.114332,	-3.1490000},
{2.0,	 0.0,	-2.0,	 0.0,	 0.058793,	 246.15800},
{2.0,	-1.0,	-1.0,	 0.0,	 0.057066,	-152.13800},
{2.0,	 0.0,	 1.0,	 0.0,	 0.053322,	-170.73300},
{2.0,	-1.0,	 0.0,	 0.0,	 0.045758,	-204.58600},
{0.0,	 1.0,	-1.0,	 0.0,	-0.040923,	-129.62000},
{1.0,	 0.0,	 0.0,	 0.0,	-0.034720,	 108.74300},
{0.0,	 1.0,	 1.0,	 0.0,	-0.030383,	 104.75500},
{2.0,	 0.0,	 0.0,	-2.0,	 0.015327,	 10.321000},
{0.0,	 0.0,	 1.0,	 2.0,	-0.012528,	 0.0000000},
{0.0,	 0.0,	 1.0,	-2.0,	 0.010980,	 79.661000},
{4.0,	 0.0,	-1.0,	 0.0,	 0.010675,	-34.782000},
{0.0,	 0.0,	 3.0,	 0.0,	 0.010034,	-23.210000},
{4.0,	 0.0,	-2.0,	 0.0,	 0.008548,	-21.636000},
{2.0,	 1.0,	-1.0,	 0.0,	-0.007888,	 24.208000},
{2.0,	 1.0,	 0.0,	 0.0,	-0.006766,	 30.824000},
{1.0,	 0.0,	-1.0,	 0.0,	-0.005163,	-8.3790000},
{1.0,	 1.0,	 0.0,	 0.0,	 0.004987,	-16.675000},
{2.0,	-1.0,	 1.0,	 0.0,	 0.004036,	-12.831000},
{2.0,	 0.0,	 2.0,	 0.0,	 0.003994,	-10.445000},
{4.0,	 0.0,	 0.0,	 0.0,	 0.003861,	-11.650000},
{2.0,	 0.0,	-3.0,	 0.0,	 0.003665,	 14.403000},
{0.0,	 1.0,	-2.0,	 0.0,	-0.002689,	-7.0030000},
{2.0,	 0.0,	-1.0,	 2.0,	-0.002602,	 0.0000000},
{2.0,	-1.0,	-2.0,	 0.0,	 0.002390,	 10.056000},
{1.0,	 0.0,	 1.0,	 0.0,	-0.002348,	 6.3220000},
{2.0,	-2.0,	 0.0,	 0.0,	 0.002236,	-9.8840000},
{0.0,	 1.0,	 2.0,	 0.0,	-0.002120,	 5.7510000},
{0.0,	 2.0,	 0.0,	 0.0,	-0.002069,	 0.0000000},
{2.0,	-2.0,	-1.0,	 0.0,	 0.002048,	-4.9500000},
{2.0,	 0.0,	 1.0,	-2.0,	-0.001773,	 4.1300000},
{2.0,	 0.0,	 0.0,	 2.0,	-0.001595,	 0.0000000},
{4.0,	-1.0,	-1.0,	 0.0,	 0.001215,	-3.9580000},
{0.0,	 0.0,	 2.0,	 2.0,	-0.001110,	 0.0000000},
{3.0,	 0.0,	-1.0,	 0.0,	-0.000892,	 3.2580000},
{2.0,	 1.0,	 1.0,	 0.0,	-0.000810,	 2.6160000},
{4.0,	-1.0,	-2.0,	 0.0,	 0.000759,	-1.8970000},
{0.0,	 2.0,	-1.0,	 0.0,	-0.000713,	-2.1170000},
{2.0,	 2.0,	-1.0,	 0.0,	-0.000700,	 2.3540000},
{2.0,	 1.0,	-2.0,	 0.0,	 0.000691,	 0.0000000},
{2.0,	-1.0,	 0.0,	-2.0,	 0.000596,	 0.0000000},
{4.0,	 0.0,	 1.0,	 0.0,	 0.000549,	-1.4230000},
{0.0,	 0.0,	 4.0,	 0.0,	 0.000537,	-1.1170000},
{4.0,	-1.0,	 0.0,	 0.0,	 0.000520,	-1.5710000},
{1.0,	 0.0,	-2.0,	 0.0,	-0.000487,	-1.7390000},
{2.0,	 1.0,	 0.0,	-2.0,	-0.000399,	 0.0000000},
{0.0,	 0.0,	 2.0,	-2.0,	-0.000381,	-4.4210000},
{1.0,	 1.0,	 1.0,	 0.0,	 0.000351,	 0.0000000},
{3.0,	 0.0,	-2.0,	 0.0,	-0.000340,	 0.0000000},
{4.0,	 0.0,	-3.0,	 0.0,	 0.000330,	 0.0000000},
{2.0,	-1.0,	 2.0,	 0.0,	 0.000327,	 0.0000000},
{0.0,	 2.0,	 1.0,	 0.0,	-0.000323,	 0.1650000},
{1.0,	 1.0,	-1.0,	 0.0,	 0.000299,	 0.0000000},
{2.0,	 0.0,	 3.0,	 0.0,	 0.000294,	 0.0000000},
{2.0,	 0.0,	-1.0,	-2.0,	 0.000000,	 8.7520000}
};

/* Periodic terms for ecliptic latitude */
static const double moon_data_b[SCA_MOON_MAX_COEFS][5] = {
/* D, M, dM, F, b  coefficients */
{0.0,	 0.0,	 0.0,	 1.0,	 5.128122},
{0.0,	 0.0,	 1.0,	 1.0,	 0.280602},
{0.0,	 0.0,	 1.0,	-1.0,	 0.277693},
{2.0,	 0.0,	 0.0,	-1.0,	 0.173237},
{2.0,	 0.0,	-1.0,	 1.0,	 0.055413},
{2.0,	 0.0,	-1.0,	-1.0,	 0.046271},
{2.0,	 0.0,	 0.0,	 1.0,	 0.032573},
{0.0,	 0.0,	 2.0,	 1.0,	 0.017198},
{2.0,	 0.0,	 1.0,	-1.0,	 0.009266},
{0.0,	 0.0,	 2.0,	-1.0,	 0.008822},
{2.0,	-1.0,	 0.0,	-1.0,	 0.008216},
{2.0,	 0.0,	-2.0,	-1.0,	 0.004324},
{2.0,	 0.0,	 1.0,	 1.0,	 0.004200},
{2.0,	 1.0,	 0.0,	-1.0,	-0.003359},
{2.0,	-1.0,	-1.0,	 1.0,	 0.002463},
{2.0,	-1.0,	 0.0,	 1.0,	 0.002211},
{2.0,	-1.0,	-1.0,	-1.0,	 0.002065},
{0.0,	 1.0,	-1.0,	-1.0,	-0.001870},
{4.0,	 0.0,	-1.0,	-1.0,	 0.001828},
{0.0,	 1.0,	 0.0,	 1.0,	-0.001794},
{0.0,	 0.0,	 0.0,	 3.0,	-0.001749},
{0.0,	 1.0,	-1.0,	 1.0,	-0.001565},
{1.0,	 0.0,	 0.0,	 1.0,	-0.001491},
{0.0,	 1.0,	 1.0,	 1.0,	-0.001475},
{0.0,	 1.0,	 1.0,	-1.0,	-0.001410},
{0.0,	 1.0,	 0.0,	-1.0,	-0.001344},
{1.0,	 0.0,	 0.0,	-1.0,	-0.001335},
{0.0,	 0.0,	 3.0,	 1.0,	 0.001107},
{4.0,	 0.0,	 0.0,	-1.0,	 0.001021},
{4.0,	 0.0,	-1.0,	 1.0,	 0.000833},
{0.0,	 0.0,	 1.0,	-3.0,	 0.000777},
{4.0,	 0.0,	-2.0,	 1.0,	 0.000671},
{2.0,	 0.0,	 0.0,	-3.0,	 0.000607},
{2.0,	 0.0,	 2.0,	-1.0,	 0.000596},
{2.0,	-1.0,	 1.0,	-1.0,	 0.000491},
{2.0,	 0.0,	-2.0,	 1.0,	-0.000451},
{0.0,	 0.0,	 3.0,	-1.0,	 0.000439},
{2.0,	 0.0,	 2.0,	 1.0,	 0.000422},
{2.0,	 0.0,	-3.0,	-1.0,	 0.000421},
{2.0,	 1.0,	-1.0,	 1.0,	-0.000366},
{2.0,	 1.0,	 0.0,	 1.0,	-0.000351},
{4.0,	 0.0,	 0.0,	 1.0,	 0.000331},
{2.0,	-1.0,	 1.0,	 1.0,	 0.000315},
{2.0,	-2.0,	 0.0,	-1.0,	 0.000302},
{0.0,	 0.0,	 1.0,	 3.0,	-0.000283},
{2.0,	 1.0,	 1.0,	-1.0,	-0.000229},
{1.0,	 1.0,	 0.0,	-1.0,	 0.000223},
{1.0,	 1.0,	 0.0,	 1.0,	 0.000223},
{0.0,	 1.0,	-2.0,	-1.0,	-0.000220},
{2.0,	 1.0,	-1.0,	-1.0,	-0.000220},
{1.0,	 0.0,	 1.0,	 1.0,	-0.000185},
{2.0,	-1.0,	-2.0,	-1.0,	 0.000181},
{0.0,	 1.0,	 2.0,	 1.0,	-0.000177},
{4.0,	 0.0,	-2.0,	-1.0,	 0.000176},
{4.0,	-1.0,	-1.0,	-1.0,	 0.000166},
{1.0,	 0.0,	 1.0,	-1.0,	-0.000164},
{4.0,	 0.0,	 1.0,	-1.0,	 0.000132},
{1.0,	 0.0,	-1.0,	-1.0,	-0.000119},
{4.0,	-1.0,	 0.0,	-1.0,	 0.000115},
{2.0,	-2.0,	 0.0,	 1.0,	 0.000107}
};

int
sca_moon_update_date (SCAMoon *moon, SCADate *date)
{
	double		jd, t;
	double		r, l, b, E, E_clr, E_cb;
	SCAAngle	dL, D, M, dM, F;
	SCAAngle	A1, A2, A3;
	SCAAngle	L, B;
	unsigned int	i, M_abs_lr, M_abs_b;
	
	if (moon == NULL || date == NULL)
		return -1;

	jd	= sca_jd_from_calendar_date (date);
	t	= sca_jd_get_centuries_2000 (jd);

	/* Moon's mean longitude, to take in account flattering of the Earth */
	sca_moon_get_mean_longitude (jd, &dL);
	sca_moon_get_mean_elongation_from_sun (jd, &D);
	sca_moon_get_mean_anomaly (jd, &dM);
	sca_moon_get_latitude_argument (jd, &F);
	sca_sun_get_mean_anomaly (jd, &M);

	/* Coefficient due to Earth's orbit eccentricity */
	E	= 1.0 - 0.002516 * t - 0.0000074 * t * t;

	/* Involving action of Venus */
	A1 = sca_angle_from_decimal_degrees (119.75 + 131.849 * t);

	/* Involving action of Jupiter */
	A2 = sca_angle_from_decimal_degrees (53.09 + 479264.290 * t);
	A3 = sca_angle_from_decimal_degrees (313.45 + 481266.484 * t);

	sca_angle_reduce (&A1);
	sca_angle_reduce (&A2);
	sca_angle_reduce (&A3);	

	r = l = b = 0.0;
	for (i = 0; i < SCA_MOON_MAX_COEFS; ++i) {
		M_abs_lr	= (unsigned int) fabs (moon_data_lr[i][1] + 0.5);
		M_abs_b		= (unsigned int) fabs (moon_data_b[i][1] + 0.5);
		
		/* Corrections for Earth's orbit eccentricity */
		E_clr = (M_abs_lr == 1) ? E : ((M_abs_lr == 2) ? E * E : 1.0);
		E_cb = (M_abs_b == 1) ? E : ((M_abs_b == 2) ? E * E : 1.0);

		l += moon_data_lr[i][4] * E_clr
		   * sca_angle_get_sin (moon_data_lr[i][0] * D + moon_data_lr[i][1] * M
				      + moon_data_lr[i][2] * dM + moon_data_lr[i][3] * F);
		r += moon_data_lr[i][5] * E_clr
		   * sca_angle_get_cos (moon_data_lr[i][0] * D + moon_data_lr[i][1] * M
				      + moon_data_lr[i][2] * dM + moon_data_lr[i][3] * F);

		b += moon_data_b[i][4] * E_cb
		   * sca_angle_get_sin (moon_data_b[i][0] * D + moon_data_b[i][1] * M
				      + moon_data_b[i][2] * dM + moon_data_b[i][3] * F);
	}

	l += (0.003958 * sca_angle_get_sin (A1) + 0.001962 * sca_angle_get_sin (dL - F)
	      + 0.000318 * sca_angle_get_sin (A2));

	b += (-0.002235 * sca_angle_get_sin (dL)
	      + 0.000382 * sca_angle_get_sin (A3)
	      + 0.000175 * sca_angle_get_sin (A1 - F)
	      + 0.000175 * sca_angle_get_sin (A1 + F)
	      + 0.000127 * sca_angle_get_sin (dL - dM)
	      - 0.000115 * sca_angle_get_sin (dL + dM));

	L = dL + sca_angle_from_decimal_degrees (l);
	B = sca_angle_from_decimal_degrees (b);

	sca_angle_reduce (&L);
	sca_angle_reduce (&B);
		
	sca_coordinates_ecliptic_to_equatorial (jd, L, B, &moon->ra, &moon->dec);

	moon->jd	= jd;
	moon->dst	= (385000.56 + r) / SCA_AU;

	return 0;
}

int
sca_moon_get_local_coordinates	(SCAMoon *moon, SCAGeoLocation *loc, SCAAngle *A, SCAAngle *h)
{
	SCAAngle d_ra, d_dec;

	if (moon == NULL || loc == NULL)
		return -1;

	/* Take parallax into account */
	sca_earth_get_parallax_equatorial (moon->jd, moon->dst, loc, moon->ra, moon->dec, &d_ra, &d_dec);
	
	moon->ra	+= d_ra;
	moon->dec	+= d_dec;

	sca_coordinates_equatorial_to_local (moon->jd, loc, moon->ra, moon->dec, A, h);

	return 0;
}

int
sca_moon_get_mean_elongation_from_sun (double jd, SCAAngle *elong)
{
	double	t;

	if (jd < 0 || elong == NULL)
		return -1;

	t = sca_jd_get_centuries_2000 (jd);

	*elong = sca_angle_from_decimal_degrees (297.8502042
						+ 445267.1115168 * t
						- 0.0016300 * t * t
						+ (t * t * t) / 545868.0
						- (t * t * t * t) / 113065000);
	sca_angle_reduce (elong);

	return 0;
}

int
sca_moon_get_mean_anomaly (double jd, SCAAngle *anom)
{
	double	t;

	if (jd < 0 || anom == NULL)
		return -1;

	t = sca_jd_get_centuries_2000 (jd);

	*anom = sca_angle_from_decimal_degrees (134.9634114
						+ 477198.8676313 * t
						+ 0.0089970 * t * t
						+ (t * t * t) / 69699.0
						- (t * t * t * t) / 14712000.0);
	sca_angle_reduce (anom);

	return 0;
}

int
sca_moon_get_latitude_argument (double jd, SCAAngle *arg)
{
	double	t;

	if (jd < 0 || arg == NULL)
		return -1;

	t = sca_jd_get_centuries_2000 (jd);

	*arg = sca_angle_from_decimal_degrees (93.2720993
					      + 483202.0175273 * t
					      - 0.0034029 * t * t
					      - (t * t * t) / 3526000.0
					      + (t * t * t * t) / 863310000.0);
	sca_angle_reduce (arg);

	return 0;
}

int
sca_moon_get_mean_longitude (double jd, SCAAngle *lon)
{
	double	t;

	if (jd < 0 || lon == NULL)
		return -1;

	t = sca_jd_get_centuries_2000 (jd);

	*lon= sca_angle_from_decimal_degrees (218.3164591
					      + 481267.88134236 * t
					      - 0.0013268 * t * t
					      + (t * t * t) / 538841.0
					      - (t * t * t * t) / 65194000.0);
	sca_angle_reduce (lon);

	return 0;
}

int
sca_moon_get_mean_longitude_of_ascnode	(double jd, SCAAngle *lon)
{
	double	t;

	if (jd < 0 || lon == NULL)
		return -1;

	t = sca_jd_get_centuries_2000 (jd);

	*lon= sca_angle_from_decimal_degrees (125.04452
					      - 1934.136261 * t
					      + 0.0020708 * t * t
					      + (t * t * t) / 450000.0);
	sca_angle_reduce (lon);

	return 0;
}
