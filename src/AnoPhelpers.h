/* *************************************************************************
   @file       AnoPhelpers.h
   @project    AnoPlib
   @module     AnoPhelpers 
   @brief      Some helper methods and data
   @date       29.11.2010
   @copyright  Daniel Krajzewicz
   @licence    LGPL
   @author     Daniel Krajzewicz
   @email      daniel@krajzewicz.de
   ------------------------------------------------------------------
    AnoPlib - small "animlet" library, see http://sf.net/projects/anoplib
    Copyright (C) 2009-2012 Daniel Krajzewicz

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
   ------------------------------------------------------------------
   Remarks:
   ------------------------------------------------------------------
   ToDo:
 * *********************************************************************** */
#ifndef ANOP_HELPERS
#define ANOP_HELPERS


/* =========================================================================
 * included modules
 * ======================================================================= */
#include <GL/gl.h>
#include <cmath>


/* =========================================================================
 * class and struct definitions
 * ======================================================================= */
/** @class AnoPhelpers 
 * @brief Some helper methods and data
 */ 
class AnoPhelpers {
public:
	// sinus/cosinus tables
	static double *sintab;
	static double *costab;

	static void init();

	static void close();


static void
drawOutlineCircle(double width, double iwidth, int steps, double beg, double end) throw();

static void
drawOutlineCircle2(double width, double iwidth, int steps, double beg, double end, 
                   float *rgba1, float *rgba2) throw();
};

#endif
