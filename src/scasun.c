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

#include <scasun.h>
#include <scaearth.h>
#include <scaplanetdata.h>
#include <scaprivate.h>

int
sca_sun_get_mean_longitude (double jd, SCAAngle *L)
{
	double	t;

	if (jd < 0 || L == NULL)
		return -1;

	t	= sca_jd_get_centuries_2000 (jd);
	*L	= sca_angle_from_decimal_degrees (280.46645
						  + 36000.76983 * t
						  + 0.0003032 * t * t);

	sca_angle_reduce (L);

	return 0;
}

int
sca_sun_get_true_longitude (double jd, SCAAngle *T)
{
	double		t;
	SCAAngle	L, C, M;

	if (jd < 0 || T == NULL)
		return -1;

	t = sca_jd_get_centuries_2000 (jd);
	sca_sun_get_mean_anomaly (jd, &M);
	sca_sun_get_mean_longitude (jd, &L);

	/* Sun's equation of the center */
	C = sca_angle_from_decimal_degrees ((1.914600 -0.004817 * t - 0.000014 * t * t) * sca_angle_get_sin (M)
					   + (0.019993 - 0.000101 * t) * sca_angle_get_sin (2.0 * M)
					   + (0.000290) * sca_angle_get_sin (3.0 * M));

	*T = L + C;
	sca_angle_reduce (T);

	return 0;
}

int
sca_sun_get_mean_anomaly (double jd, SCAAngle *M)
{
	double	t;

	if (jd < 0 || M == NULL)
		return -1;

	t	= sca_jd_get_centuries_2000 (jd); 
	*M	= sca_angle_from_decimal_degrees (357.52910
						  + 35999.0502909 * t
						  - 0.0001559 * t * t
						  - 0.00000048 * t * t * t);
	
	sca_angle_reduce (M);
	
	return 0;
}

int
sca_sun_update_date (SCASun *s, SCADate *date)
{
	double		jd;
	SCAAngle	d_lon, d_abr;

	SCAAngle	L, B;
	double		R;
	
	if (s == NULL || date == NULL)
		return -1;

	jd	= sca_jd_from_calendar_date (date);
	jd	+= sca_jd_get_dynamic_time (jd);
		
	sca_planet_data_get (SCA_PLANET_EARTH, jd, &L, &B, &R);

	L += 180.0;
	B = -B;

	/* Take nutation into account */
	sca_earth_get_nutation (jd, &d_lon, NULL);
	L += d_lon;

	/* Take aberration into account:
	 * this constant is K * (1 - e^2), where K is aberration constant, and e is
	 * Earth's orbit eccentricity */
	d_abr	= sca_angle_from_degrees (0, 0, -20, 489.8) / R;
	L	+= d_abr; 

	sca_coordinates_ecliptic_to_equatorial (jd, L, B, &s->ra, &s->dec);

	s->jd	= jd;
	s->dst	= R;
	
	return 0;
}

int
sca_sun_get_local_coordinates (SCASun		*s,
			       SCAGeoLocation	*loc,
			       SCAAngle		*A,
			       SCAAngle		*h)
{
	SCAAngle d_ra, d_dec;

	if (s == NULL || loc == NULL)
		return -1;

	/* Take parallax into account */
	sca_earth_get_parallax_equatorial (s->jd, s->dst, loc, s->ra, s->dec, &d_ra, &d_dec);
	
	s->ra	+= d_ra;
	s->dec	+= d_dec;

	sca_coordinates_equatorial_to_local (s->jd, loc, s->ra, s->dec, A, h);

	return 0;
}
