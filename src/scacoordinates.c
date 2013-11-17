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

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "scacoordinates.h"
#include "scajulianday.h"

int
sca_coordinates_equatorial_to_ecliptic (double jd, SCAAngle ra, SCAAngle dec, SCAAngle *lon, SCAAngle *lat)
{
	SCAAngle	obl;
	double		sin_obl, cos_obl;

	if (jd < 0)
		return -1;

	sca_earth_get_ecliptic_obliquity (jd, &obl);
	sca_angle_get_sincos (obl, &sin_obl, &cos_obl);

	if (lon != NULL)
		*lon = (atan2 (sca_angle_get_sin (ra) * cos_obl
				+ tan (sca_angle_to_radians (dec)) * sin_obl,
				sca_angle_get_cos (ra))) * SCA_ANGLE_RAD_TO_DEG;

	if (lat != NULL)
		*lat = (asin (sca_angle_get_sin (dec) * cos_obl
			      - sca_angle_get_cos (dec) * sin_obl
			      * sca_angle_get_sin (ra))) * SCA_ANGLE_RAD_TO_DEG;

	return 0;
}

int
sca_coordinates_ecliptic_to_equatorial (double jd, SCAAngle lon, SCAAngle lat, SCAAngle *ra, SCAAngle *dec)
{
	SCAAngle obl;
	double	sin_obl, cos_obl;

	if (jd < 0)
		return -1;

	sca_earth_get_ecliptic_obliquity (jd, &obl);
	sca_angle_get_sincos (obl, &sin_obl, &cos_obl);

	if (ra != NULL)
		*ra = (atan2 (sca_angle_get_sin (lon) * cos_obl
			     - tan (sca_angle_to_radians (lat)) * sin_obl,
			     sca_angle_get_cos (lon))) * SCA_ANGLE_RAD_TO_DEG;

	if (dec != NULL)
		*dec = (asin (sca_angle_get_sin (lat) * cos_obl
			     + sca_angle_get_cos (lat) * sin_obl
			     * sca_angle_get_sin (lon))) * SCA_ANGLE_RAD_TO_DEG;

	return 0;
}

int
sca_coordinates_equatorial_to_local (double jd, SCAGeoLocation *loc, SCAAngle ra, SCAAngle dec, SCAAngle *A, SCAAngle *h)
{
	SCAAngle	theta0;
	SCAAngle	H;

	if (jd < 0 || loc == NULL)
		return -1;
	
	sca_jd_get_sidereal_time (jd, &theta0);
	H = theta0 - loc->longitude - ra;

	if (A != NULL)
		*A = atan2 (sca_angle_get_sin (H),
			    sca_angle_get_cos (H) * sca_angle_get_sin (loc->latitude)
			    - tan (sca_angle_to_radians (dec))
			    * sca_angle_get_cos (loc->latitude)) * SCA_ANGLE_RAD_TO_DEG;

	if (h != NULL)
		*h = asin (sca_angle_get_sin (loc->latitude) * sca_angle_get_sin (dec)
			   + sca_angle_get_cos (loc->latitude) * sca_angle_get_cos (dec)
			   * sca_angle_get_cos (H)) * SCA_ANGLE_RAD_TO_DEG;

	return 0;
}
