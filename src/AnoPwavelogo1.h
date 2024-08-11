/* *************************************************************************
   @file       AnoPwavelogo1.h
   @project    AnoPlib
   @module     AnoPwavelogo1
   @brief      Old-style c64 wave effect
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
#ifndef ANOP_WAVELOGO1
#define ANOP_WAVELOGO1


/* =========================================================================
 * included modules
 * ======================================================================= */
#include <AnoP.h>
#include <AnoPhelpers.h>
#include <GL/gl.h>


/* =========================================================================
 * class and struct definitions
 * ======================================================================= */
// @brief The animlet definition structure
struct waveStruct {
    /// @brief The current animation step
    int step;
    /// @brief The animlet's position
    double pos[2];
};


/** @class AnoPwavelogo1
 * @brief Old-style c64 wave effect
 */
class AnoPwavelogo1 : public AnoP::AnoPsystem<waveStruct> {
public:
    /** @brief Constructor
     * @param[in] bufSize The number of animlets to pre-allocate
     */         
    AnoPwavelogo1(unsigned int bufSize=10) : AnoP::AnoPsystem<waveStruct>(bufSize) { }


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
    bool render(waveStruct &s, unsigned int timeDiff, void * const something) throw() {
        glPushMatrix();
        int off = s.step;
        glTranslated(s.pos[0]+AnoPhelpers::sintab[off]/100., s.pos[1]+AnoPhelpers::costab[off]/100., 0);
        glScaled(1./4., 1./4., 1);
        glColor3d(1,1,1);
        glBegin(GL_QUADS);
        glVertex3f(-1,-1,0);
        glVertex3f(-1,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,-1,0);
        glEnd();
        glPopMatrix();
        s.step++;
        if(s.step>359) {
            s.step = 0;
        }
        return true;
    }
    
};

#endif
