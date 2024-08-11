/* *************************************************************************
   @file       AnoPhelpers.cpp
   @project    AnoPlib
   @module     AnoPhelpers 
   @brief      Some helper methods and data
   @date       29.11.2010
   @copyright  Daniel Krajzewicz
   @licence    GPL
   @author     Daniel Krajzewicz
   @email      d.krajzewicz@googlemail.com
   ------------------------------------------------------------------
    AnoPlib - small "animlet" library, see http://sf.net/projects/anoplib
    Copyright (C) 2009-2010 Daniel Krajzewicz

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

/* =========================================================================
 * included modules
 * ======================================================================= */
#ifdef _WIN32
#include <windows.h>
#endif

#include "AnoPhelpers.h"
#include <GL/gl.h>
#include <cmath>


/* =========================================================================
 * static members
 * ======================================================================= */
double *AnoPhelpers::sintab;
double *AnoPhelpers::costab;


/* =========================================================================
 * method definitions
 * ======================================================================= */
void AnoPhelpers::init() {
	double PI = 3.1415926535897932384626433832795;
	sintab = new double[360];
	costab = new double[360];
	for(int i=0; i<360; ++i) {
		sintab[i] = 256. * sin(PI/180.*(double)i);
		costab[i] = 256. * cos(PI/180.*(double)i);
	}
}


void AnoPhelpers::close() {
	delete[] sintab;
	delete[] costab;
}


void
AnoPhelpers::drawOutlineCircle(double width, double iwidth, int steps, double beg, double end) throw() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    double p1x = beg==0 ? sintab[0] : sintab[((int) beg)%360];
    double p1y = beg==0 ? costab[0] : costab[((int) beg)%360];
    for (int i=(int)(beg); i<steps&&(360.0/(double) steps *(double) i)<end; i++) {
        double p2x = sintab[(size_t)(360.0/(double) steps * (double) i)%360];
        double p2y = costab[(size_t)(360.0/(double) steps * (double) i)%360];
        glBegin(GL_TRIANGLES);
        glVertex2d(p1x * width, p1y * width);
        glVertex2d(p2x * width, p2y * width);
        glVertex2d(p2x * iwidth, p2y * iwidth);

        glVertex2d(p2x * iwidth, p2y * iwidth);
        glVertex2d(p1x * iwidth, p1y * iwidth);
        glVertex2d(p1x * width, p1y * width);
        glEnd();
        p1x = p2x;
        p1y = p2y;
    }
    double p2x = end==360 ? sintab[0] : sintab[((int) end)%360];
    double p2y = end==360 ? costab[0] : costab[((int) end)%360];
    glBegin(GL_TRIANGLES);
    glVertex2d(p1x * width, p1y * width);
    glVertex2d(p2x * width, p2y * width);
    glVertex2d(p2x * iwidth, p2y * iwidth);

    glVertex2d(p2x * iwidth, p2y * iwidth);
    glVertex2d(p1x * iwidth, p1y * iwidth);
    glVertex2d(p1x * width, p1y * width);
    glEnd();
}


void
AnoPhelpers::drawOutlineCircle2(double width, double iwidth, int steps, double beg, double end, 
                   float *rgba1, float *rgba2) throw() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    double p1x = beg==0 ? sintab[0] : sintab[((int) beg)%360];
    double p1y = beg==0 ? costab[0] : costab[((int) beg)%360];
    double s = end - beg;
    if(s<0) {
        s = 360. + s;
    }
    for (int i=0; i<steps; ++i) {
        double p2x = sintab[(size_t)(s/(double) steps * (double) i + beg)%360];
        double p2y = costab[(size_t)(s/(double) steps * (double) i + beg)%360];
        glBegin(GL_TRIANGLES);
        glColor4fv(rgba2);
        glVertex2d(p1x * width, p1y * width);
        glVertex2d(p2x * width, p2y * width);
        glColor4fv(rgba1);
        glVertex2d(p2x * iwidth, p2y * iwidth);

        glVertex2d(p2x * iwidth, p2y * iwidth);
        glVertex2d(p1x * iwidth, p1y * iwidth);
        glColor4fv(rgba2);
        glVertex2d(p1x * width, p1y * width);
        glEnd();
        p1x = p2x;
        p1y = p2y;
    }
    double p2x = end==360 ? sintab[0] : sintab[((int) end)%360];
    double p2y = end==360 ? costab[0] : costab[((int) end)%360];
    glBegin(GL_TRIANGLES);
    glColor4fv(rgba2);
    glVertex2d(p1x * width, p1y * width);
    glVertex2d(p2x * width, p2y * width);
    glColor4fv(rgba1);
    glVertex2d(p2x * iwidth, p2y * iwidth);

    glVertex2d(p2x * iwidth, p2y * iwidth);
    glVertex2d(p1x * iwidth, p1y * iwidth);
    glColor4fv(rgba2);
    glVertex2d(p1x * width, p1y * width);
    glEnd();
}
