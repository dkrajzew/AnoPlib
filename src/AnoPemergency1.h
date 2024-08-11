/* *************************************************************************
   @file       AnoPemergency1.h
   @project    AnoPlib
   @module     AnoPemergency1 
   @brief      An emergency vehicle's flash light
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
#ifndef ANOP_EMERGENCY1
#define ANOP_EMERGENCY1


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
struct emergency1Struct {
    /// @brief The animlet's position
    double pos[2];
    /// @brief The current animation step
    int step;
};


/** @class AnoPemergency1 
 * @brief An emergency vehicle's flash light
 */ 
class AnoPemergency1 : public AnoP::AnoPsystem<emergency1Struct> {
public:
    /** @brief Constructor
     * @param[in] bufSize The number of animlets to pre-allocate
     */    
    AnoPemergency1(unsigned int bufSize=10) : AnoP::AnoPsystem<emergency1Struct>(bufSize) {
        white[0] = 1;
        white[1] = 1;
        white[2] = 1;
        white[3] = 1;
        yellowbright[0] = 1;
        yellowbright[1] = 1;
        yellowbright[2] = 0;
        yellowbright[3] = 1;
        yellowdark[0] = .1;
        yellowdark[1] = .1;
        yellowdark[2] = .0;
        yellowdark[3] = .1;
    }


    /** @brief Pre-rendering step
     */    
    void preRender() throw() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslated(-1,-1,0);
        glScaled(1./200, 1./200, 1.);
        glEnable (GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        glDepthMask(GL_FALSE);
    }


    /** @brief Rendering step
     * @param[in] s The settings of the animlet to render
     * @param[in] timeDiff The time passed since last call
     * @param[in] something Not used here
     */                   
    bool render(emergency1Struct &s, unsigned int timeDiff, void * const something) throw() {
        glPushMatrix();
        int off = s.step;
        glTranslated(s.pos[0], s.pos[1], 0.);
        double scale = off;
        glScaled(50./256., 50./256., 50./256.);
        glColor4d(1,1,0,1);
		AnoPhelpers::drawOutlineCircle2(.5, .09, 36, (s.step+10)%360, (s.step+70)%360, white, yellowdark);
        AnoPhelpers::drawOutlineCircle2(1., .09, 36, (s.step-00)%360, (s.step+80)%360, yellowbright, yellowdark);
        glRotated(180.,0,0,1);
        AnoPhelpers::drawOutlineCircle2(.5, .09, 36, (s.step+10)%360, (s.step+70)%360, white, yellowdark);
        AnoPhelpers::drawOutlineCircle2(1., .09, 36, (s.step-00)%360, (s.step+80)%360, yellowbright, yellowdark);
        glPopMatrix();
        s.step += 5;
        if(s.step>360) {
            s.step = 1;
        }
        return true;
    }

    float white[4], yellowbright[4], yellowdark[4];
};

#endif
