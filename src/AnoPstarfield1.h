/* *************************************************************************
   @file       AnoPstarfield1.h
   @project    AnoPlib
   @module     AnoPstarfield1
   @brief      Old-style c64 stars scroller
   @date       23.11.2010
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
#ifndef ANOP_STARFIELD1
#define ANOP_STARFIELD1


/* =========================================================================
 * included modules
 * ======================================================================= */
#include <AnoP.h>
#include <GL/gl.h>


/* =========================================================================
 * class and struct definitions
 * ======================================================================= */
// @brief The animlet definition structure
struct starfield1Struct {
    /// @brief The star's position
    double pos[2];
    /// @brief The star's speed
    double speed;
};
    
    
/** @class AnoPstarfield1
 * @brief Old-style c64 stars scroller
 */
class AnoPstarfield1 : public AnoP::AnoPsystem<starfield1Struct> {
public:
    /** @brief Constructor
     * @param[in] bufSize The number of animlets to pre-allocate
     */         
    AnoPstarfield1(unsigned int bufSize=10) : AnoP::AnoPsystem<starfield1Struct>(bufSize) {}


    /** @brief Pre-rendering step
     */    
    void preRender() throw() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslated(-1,-1,0);
        glScaled(1./20, 1./20, 1.);
        glTranslated(0,15,0);
    }


    /** @brief Rendering step
     * @param[in] s The settings of the animlet to render
     * @param[in] timeDiff The time passed since last call
     * @param[in] something Not used here
     */                   
    bool render(starfield1Struct &s, unsigned int timeDiff, void * const something) throw() {
        glColor3d(1,1,1);
        glBegin(GL_POINTS);
        glVertex3f(s.pos[0], s.pos[1], 0);
        glEnd();
        s.pos[0] = s.pos[0] - s.speed;
        if(s.pos[0]<0) {
            s.pos[0] = 40;
        }
        return true;
    }
};

#endif
