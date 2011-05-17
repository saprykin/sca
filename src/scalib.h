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
 * @file scalib.h
 * @brief Main header file
 * @author Alexander Saprykin
 */

/**
 * @page compile_with_scalib Compiling application with SCALib
 * In order to compile your application with SCALib you should do the following steps:
 * - include main header file scalib.h into your project - do not use other headers directly;
 * - point compiler for directory with SCALib header (on Linux you can add -I option to gcc
 *   or using pkg-config tool: `pkg-config --cflags sca`);
 * - compile your application with SCALib library, i.e by adding -lsca and -L&lt;directory&gt;
 *   flag to gcc or using pkg-config: `pkg-config --libs sca`;
 *
 * Note that you need only one scalib.h header, other headers shouldn't be
 * included directly into the project.
 *
 * You may also need to specify directory containing SCALib while launching
 * application. On Linux it can be done using LD_LIBRARY_PATH variable or
 * modifing /etc/ld.so.conf.
 */

/**
 * @mainpage
 * SCALib stands for Sky Computing Algorithms Library. It can be used to
 * calculate position of the star, Sun, Moon or any planet for given instance of
 * time. The main purpose is to provide data for sky observations from the
 * Earth. Calculation accuracy is not greater than 1 arcsecond, but it
 * would be enough for almoast all purposes. Most of the algorithms were
 * taken from the "Astronomical algorithms" by J. Meeus. 
 *
 * - @link
 * compile_with_scalib Compiling application with SCALib
 * @endlink
 *
 * - @link
 * scaangle.h Working with angles in SCALib
 * @endlink
 *
 * - @link
 * scajulianday.h Working with dates in SCALib
 * @endlink
 *
 * - @link
 * scastar.h Calculating position of the star
 * @endlink
 *
 * - @link
 * scasun.h Calculating position of the Sun
 * @endlink
 *
 * - @link
 * scamoon.h Calculating position of the Moon
 * @endlink
 */

#ifndef __SCALIB_H__
#define __SCALIB_H__

#define __SCALIB_H_INSIDE__

#include "scaangle.h"
#include "scacoordinates.h"
#include "scaearth.h"
#include "scajulianday.h"
#include "scamacros.h"
#include "scamisc.h"
#include "scamoon.h"
#include "scaplanetdata.h"
#include "scastar.h"
#include "scasun.h"

#endif /* __SCALIB_H__ */

