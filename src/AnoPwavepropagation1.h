/* *************************************************************************
   @file       AnoPwavepropagation1.h
   @project    AnoPlib
   @module     AnoPwavepropagation1
   @brief      electromagnatic waves propagation :-)
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
#ifndef ANOP_WAVEPROPAGATION1
#define ANOP_WAVEPROPAGATION1


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
struct wireless1Struct {
    /// @brief The animlet's position
    double pos[2];
    /// @brief The current animation step
    double step;
};


/** @class AnoPwavepropagation1
 * @brief electromagnatic waves propagation :-)
 */
class AnoPwavepropagation1 : public AnoP::AnoPsystem<wireless1Struct> {
public:
    /** @brief Constructor
     * @param[in] bufSize The number of animlets to pre-allocate
     */    
    AnoPwavepropagation1(unsigned int bufSize=10) : AnoP::AnoPsystem<wireless1Struct>(bufSize) {}


    /** @brief Pre-rendering step
     */    
    void preRender() throw() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslated(-1,-1,0);
        glScaled(1./200, 1./200, 1.);
    }


    /** @brief Rendering step
     * @param[in] s The settings of the animlet to render
     * @param[in] timeDiff The time passed since last call
     * @param[in] something Not used here
     */                   
    bool render(wireless1Struct &s, unsigned int timeDiff, void * const something) throw() {
        glPushMatrix();
        int off = s.step;
        glTranslated(s.pos[0], s.pos[1], 0);
        for(int i=0; i<5; ++i) {
            glPushMatrix();
            int step = s.step + i * 100;
            double scale = step;
            glScaled(scale/256., scale/256., scale/256.);
            double c = 1. / scale * 50;
            glTranslated(0, 0, (double) i / 10.);
            glColor4d(c,c,c,c);
            //glScaled(100., 100., 100.);
            int q = step>72 ? step : step / 2;
            AnoPhelpers::drawOutlineCircle(1., .9, q, 0, 360.);
            glPopMatrix();
        }
        glPopMatrix();
        s.step += 1;
        if(s.step>100) {
            s.step = 1;
        }
        return true;
    }
};

#endif
