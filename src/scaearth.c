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

#include "config.h"

#include "scaearth.h"
#include "scajulianday.h"
#include "scasun.h"
#include "scamoon.h"

#define SCA_EARTH_NUT_MAX_COEFS 63

/* Coefficients for long period terms summing */
static double nutation_data[SCA_EARTH_NUT_MAX_COEFS][9] = {
	{ 0.0,	 0.0,	 0.0,	 0.0,	1.0,	-17.1996,	-0.01742,	 9.2025,	 0.00089},
	{-2.0,	 0.0,	 0.0,	 2.0,	2.0,	-1.31870,	-0.00016,	 0.5736,	-0.00031},
	{ 0.0,	 0.0,	 0.0,	 2.0,	2.0,	-0.22740,	-0.00002,	 0.0977,	-0.00005},
	{ 0.0,	 0.0,	 0.0,	 0.0,	2.0,	 0.20620,	 0.00002,	-0.0895,	 0.00005},
	{ 0.0,	 1.0,	 0.0,	 0.0,	0.0,	 0.14260,	-0.00034,	 0.0054,	-0.00001},
	{ 0.0,	 0.0,	 1.0,	 0.0,	0.0,	 0.07120,	 0.00001,	-0.0007,	 0.00000},
	{-2.0,	 1.0,	 0.0,	 2.0,	2.0,	-0.05170,	 0.00012,	 0.0224,	-0.00006},
	{ 0.0,	 0.0,	 0.0,	 2.0,	1.0,	-0.03860,	-0.00004,	 0.0200,	 0.00000},
	{ 0.0,	 0.0,	 1.0,	 2.0,	2.0,	-0.03010,	 0.00000,	 0.0129,	-0.00001},
	{-2.0,	-1.0,	 0.0,	 2.0,	2.0,	 0.02170,	-0.00005,	-0.0095,	 0.00003},
	{-2.0,	 0.0,	 1.0,	 0.0,	0.0,	-0.01580,	 0.00000,	 0.0001,	 0.00000},
	{-2.0,	 0.0,	 0.0,	 2.0,	1.0,	 0.01290,	 0.00001,	-0.0070,	 0.00000},
	{ 0.0,	 0.0,	-1.0,	 2.0,	2.0,	 0.01230,	 0.00000,	-0.0053,	 0.00000},
	{ 2.0,	 0.0,	 0.0,	 0.0,	0.0,	 0.00630,	 0.00000,	 0.0001,	 0.00000},
	{ 0.0,	 0.0,	 1.0,	 0.0,	1.0,	 0.00630,	 0.00001,	-0.0033,	 0.00000},
	{ 2.0,	 0.0,	-1.0,	 2.0,	2.0,	-0.00590,	 0.00000,	 0.0026,	 0.00000},
	{ 0.0,	 0.0,	-1.0,	 0.0,	1.0,	-0.00580,	-0.00001,	 0.0032,	 0.00000},
	{ 0.0,	 0.0,	 1.0,	 2.0,	1.0,	-0.00510,	 0.00000,	 0.0027,	 0.00000},
	{-2.0,	 0.0,	 2.0,	 0.0,	0.0,	 0.00480,	 0.00000,	 0.0001,	 0.00000},
	{ 0.0,	 0.0,	-2.0,	 2.0,	1.0,	 0.00460,	 0.00000,	-0.0024,	 0.00000},
	{ 2.0,	 0.0,	 0.0,	 2.0,	2.0,	-0.00380,	 0.00000,	 0.0016,	 0.00000},
	{ 0.0,	 0.0,	 2.0,	 2.0,	2.0,	-0.00310,	 0.00000,	 0.0013,	 0.00000},
	{ 0.0,	 0.0,	 2.0,	 0.0,	0.0,	 0.00290,	 0.00000,	 0.0001,	 0.00000},
	{-2.0,	 0.0,	 1.0,	 2.0,	2.0,	 0.00290,	 0.00000,	-0.0012,	 0.00000},
	{ 0.0,	 0.0,	 0.0,	 2.0,	0.0,	 0.00260,	 0.00000,	 0.0001,	 0.00000},
	{-2.0,	 0.0,	 0.0,	 2.0,	0.0,	-0.00220,	 0.00000,	 0.0001,	 0.00000},
	{ 0.0,	 0.0,	-1.0,	 2.0,	1.0,	 0.00210,	 0.00000,	-0.0010,	 0.00000},
	{ 0.0,	 2.0,	 0.0,	 0.0,	0.0,	 0.00170,	-0.00001,	 0.0001,	 0.00000},
	{ 2.0,	 0.0,	-1.0,	 0.0,	1.0,	 0.00160,	 0.00000,	-0.0008,	 0.00000},
	{-2.0,	 2.0,	 0.0,	 2.0,	2.0,	-0.00160,	 0.00001,	 0.0007,	 0.00000},
	{ 0.0,	 1.0,	 0.0,	 0.0,	1.0,	-0.00150,	 0.00000,	 0.0009,	 0.00000},
	{-2.0,	 0.0,	 1.0,	 0.0,	1.0,	-0.00130,	 0.00000,	 0.0007,	 0.00000},
	{ 0.0,	-1.0,	 0.0,	 0.0,	1.0,	-0.00120,	 0.00000,	 0.0006,	 0.00000},
	{ 0.0,	 0.0,	 2.0,	-2.0,	0.0,	 0.00110,	 0.00000,	 0.0001,	 0.00000},
	{ 2.0,	 0.0,	-1.0,	 2.0,	1.0,	-0.00100,	 0.00000,	 0.0005,	 0.00000},
	{ 2.0,	 0.0,	 1.0,	 2.0,	2.0,	-0.00080,	 0.00000,	 0.0003,	 0.00000},
	{ 0.0,	 1.0,	 0.0,	 2.0,	2.0,	 0.00070,	 0.00000,	-0.0003,	 0.00000},
	{-2.0,	 1.0,	 1.0,	 0.0,	0.0,	-0.00070,	 0.00000,	 0.0001,	 0.00000},
	{ 0.0,	-1.0,	 0.0,	 2.0,	2.0,	-0.00070,	 0.00000,	 0.0003,	 0.00000},
	{ 2.0,	 0.0,	 0.0,	 2.0,	1.0,	-0.00070,	 0.00000,	 0.0003,	 0.00000},
	{ 2.0,	 0.0,	 1.0,	 0.0,	0.0,	 0.00060,	 0.00000,	 0.0001,	 0.00000},
	{-2.0,	 0.0,	 2.0,	 2.0,	2.0,	 0.00060,	 0.00000,	-0.0003,	 0.00000},
	{-2.0,	 0.0,	 1.0,	 2.0,	1.0,	 0.00060,	 0.00000,	-0.0003,	 0.00000},
	{ 2.0,	 0.0,	-2.0,	 0.0,	1.0,	-0.00060,	 0.00000,	 0.0003,	 0.00000},
	{ 2.0,	 0.0,	 0.0,	 0.0,	1.0,	-0.00060,	 0.00000,	 0.0003,	 0.00000},
	{ 0.0,	-1.0,	 1.0,	 0.0,	0.0,	 0.00050,	 0.00000,	 0.0001,	 0.00000},
	{-2.0,	-1.0,	 0.0,	 2.0,	1.0,	-0.00050,	 0.00000,	 0.0003,	 0.00000},
	{-2.0,	 0.0,	 0.0,	 0.0,	1.0,	-0.00050,	 0.00000,	 0.0003,	 0.00000},
	{ 0.0,	 0.0,	 2.0,	 2.0,	1.0,	-0.00050,	 0.00000,	 0.0003,	 0.00000},
	{-2.0,	 0.0,	 2.0,	 0.0,	1.0,	 0.00040,	 0.00000,	 0.0001,	 0.00000},
	{-2.0,	 1.0,	 0.0,	 2.0,	1.0,	 0.00040,	 0.00000,	 0.0001,	 0.00000},
	{ 0.0,	 0.0,	 1.0,	-2.0,	0.0,	 0.00040,	 0.00000,	 0.0001,	 0.00000},
	{-1.0,	 0.0,	 1.0,	 0.0,	0.0,	-0.00040,	 0.00000,	 0.0001,	 0.00000},
	{-2.0,	 1.0,	 0.0,	 0.0,	0.0,	-0.00040,	 0.00000,	 0.0001,	 0.00000},
	{ 1.0,	 0.0,	 0.0,	 0.0,	0.0,	-0.00040,	 0.00000,	 0.0001,	 0.00000},
	{ 0.0,	 0.0,	 1.0,	 2.0,	0.0,	 0.00030,	 0.00000,	 0.0001,	 0.00000},
	{ 0.0,	 0.0,	-2.0,	 2.0,	2.0,	-0.00030,	 0.00000,	 0.0001,	 0.00000},
	{-1.0,	-1.0,	 1.0,	 0.0,	0.0,	-0.00030,	 0.00000,	 0.0001,	 0.00000},
	{ 0.0,	 1.0,	 1.0,	 0.0,	0.0,	-0.00030,	 0.00000,	 0.0001,	 0.00000},
	{ 0.0,	-1.0,	 1.0,	 2.0,	2.0,	-0.00030,	 0.00000,	 0.0001,	 0.00000},
	{ 2.0,	-1.0,	-1.0,	 2.0,	2.0,	-0.00030,	 0.00000,	 0.0001,	 0.00000},
	{ 0.0,	 0.0,	 3.0,	 2.0,	2.0,	-0.00030,	 0.00000,	 0.0001,	 0.00000},
	{ 2.0,	-1.0,	 0.0,	 2.0,	2.0,	-0.00030,	 0.00000,	 0.0001,	 0.00000}
};

int
sca_earth_get_ecliptic_obliquity (double jd, SCAAngle *obl)
{
	double		t;
	SCAAngle	obl0, d_obl;

	if (jd < 0 || obl == NULL)
		return -1;

	t	= sca_jd_get_centuries_2000 (jd);

	if (fabs (t) < 100) {
		t /= 100.0;
		/* Use Laskar high accuracy formulae */
		d_obl	= sca_angle_from_decimal_degrees ((-4680.93	* t
							   - 1.55	* t * t
							   + 1999.25	* t * t *t
							   - 51.38	* t * t * t * t
							   - 249.67	* t * t * t * t * t
							   - 39.05	* t * t * t * t * t * t
							   + 7.12	* t * t * t * t * t * t * t
							   + 27.87	* t * t * t * t * t * t * t * t
							   + 5.79	* t * t * t * t * t * t * t * t * t
							   + 2.45	* t * t * t * t * t * t * t * t * t * t)
							   / 3600);
	} else {
		/* Use less accuracy formulae */
		d_obl	= sca_angle_from_decimal_degrees ((-46.8150 * t
							   - 0.00059 * t * t
							   + 0.001813 * t * t * t)
							   / 3600.0);
	}

	obl0	= sca_angle_from_degrees (23, 26, 21, 448.0);
	*obl	= obl0 + d_obl;

	return 0;
}

int
sca_earth_get_nutation (double jd, SCAAngle *nut, SCAAngle *obl)
{
	int		i;
	double		t;
	double		d_nut, d_obl;
	SCAAngle	D, M, dM, F, Asc;

	if (jd < 0)
		return -1;

	t = sca_jd_get_centuries_2000 (jd);

	sca_moon_get_mean_elongation_from_sun (jd, &D);
	sca_sun_get_mean_anomaly (jd, &M);
	sca_moon_get_mean_anomaly (jd, &dM);
	sca_moon_get_latitude_argument (jd, &F);
	sca_moon_get_mean_longitude_of_ascnode (jd, &Asc);

	d_nut = d_obl = 0.0;
	for (i = 0; i < SCA_EARTH_NUT_MAX_COEFS; ++i) {
		d_nut += (nutation_data[i][5] + nutation_data[i][6] * t)
			 * sin (nutation_data[i][0] * D
			      + nutation_data[i][1] * M
			      + nutation_data[i][2] * dM
			      + nutation_data[i][3] * F
			      + nutation_data[i][4] * Asc);

		d_obl += (nutation_data[i][7] + nutation_data[i][8] * t)
			 * cos (nutation_data[i][0] * D
			      + nutation_data[i][1] * M
			      + nutation_data[i][2] * dM
			      + nutation_data[i][3] * F
			      + nutation_data[i][4] * Asc);
	}


	if (nut != NULL)
		*nut = sca_angle_from_decimal_degrees (d_nut / 3600.0);

	if (obl != NULL)
		*obl = sca_angle_from_decimal_degrees (d_obl / 3600.0);

	return 0;
}

SCAAngle
sca_earth_get_refraction (SCAAngle h)
{
	/* G.G. Bennet formulae, in arcminutes */
	return  sca_angle_from_decimal_degrees (1 / tan (sca_angle_to_radians (h
									       + (7.31 / (h + 4.4))) + 0.0013515)
									       / 60.0);
}

int
sca_earth_get_parallax_equatorial (double		jd,
				   double		dst,
				   SCAGeoLocation	*loc,
				   SCAAngle		ra,
				   SCAAngle		dec,
				   SCAAngle		*d_ra,
				   SCAAngle		*d_dec)
{
	SCAAngle	H, sa, pi, dlat;
	SCAAngle	dra, ddec, new_dec;
	double		p, f_ratio;
	double		sin_dlat, cos_dlat;
	double		sin_pi, cos_pi, sin_H, cos_H;
	double		sin_ra, cos_ra, sin_dec, cos_dec;

	if (jd < 0 || loc == NULL)
		return -1;

	sca_jd_get_sidereal_time (jd, &sa);
	H = sa - loc->longitude - ra;

	/* Geocentric radius-vector */
	p = 0.9983271 + 0.0016764 * sca_angle_get_cos (2.0 * loc->latitude)
		      - 0.0000035 * sca_angle_get_cos (4.0 * loc->latitude);

	/* Earth's flattering: 1/298.257 */
	f_ratio	= 1 - 1/298.257;
	dlat		= atan2 (f_ratio * f_ratio * sca_angle_get_sin (loc->latitude),
				 sca_angle_get_cos (loc->latitude)) * SCA_ANGLE_RAD_TO_DEG;

	/* Equatorial horiazontal parallax */
	pi = sca_angle_from_degrees (0, 0, 8, 794) / dst;

	sca_angle_get_sincos (dlat, &sin_dlat, &cos_dlat);
	sca_angle_get_sincos (pi, &sin_pi, &cos_pi);
	sca_angle_get_sincos (H, &sin_H, &cos_H);
	sca_angle_get_sincos (ra, &sin_ra, &cos_ra);
	sca_angle_get_sincos (dec, &sin_dec, &cos_dec);

	dra	= atan2 ((-p) * cos_dlat * sin_pi * sin_H,
			 cos_dec - p * cos_dlat * sin_pi * cos_H) * SCA_ANGLE_RAD_TO_DEG;

	new_dec	= atan2 ((sin_dec - p * sin_dlat * sin_pi) * sca_angle_get_cos (dra),
			 cos_dec - p * cos_dlat * sin_pi * cos_H) * SCA_ANGLE_RAD_TO_DEG;
	ddec	= new_dec - dec;

	if (d_ra != NULL)
		*d_ra = dra;

	if (d_dec != NULL)
		*d_dec = ddec;

	return 0;
}

int
sca_earth_get_orbit_eccentricity (double jd, double *e)
{
	double	t;

	if (jd < 0 || e == NULL)
		return -1;

	t = sca_jd_get_centuries_2000 (jd); 	
	*e = 0.016708617 - 0.000042037 * t - 0.0000001236 * t * t;

	return 0;
}

SCAAngle
sca_earth_get_aberration_constant (void)
{
	return sca_angle_from_degrees (0, 0, 20, 495.52);
}

int
sca_earth_get_perihelion_longitude (double jd, SCAAngle *pi)
{
	double	t;

	if (jd < 0 || pi == NULL)
		return -1;

	t = sca_jd_get_centuries_2000 (jd);
	*pi = sca_angle_from_decimal_degrees (102.93735 + 1.71953 * t + 0.00046 * t * t);
	sca_angle_reduce (pi);
	
	return 0;
}

