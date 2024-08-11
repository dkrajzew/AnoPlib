/* *************************************************************************
   @file       AnoPflashlight1.h
   @project    AnoPlib
   @module     AnoPflashlight1
   @brief      A flashing signal
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
#ifndef ANOP_FLASHLIGHT1
#define ANOP_FLASHLIGHT1


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
struct flashSignal1Struct {
    /// @brief The animlet's position
    double pos[2];
    /// @brief The current animation step
    int step;
};


/** @class AnoPflashlight1
 * @brief A flashing signal
 */
class AnoPflashlight1 : public AnoP::AnoPsystem<flashSignal1Struct> {
public:
    /** @brief Constructor
     * @param[in] bufSize The number of animlets to pre-allocate
     */    
    AnoPflashlight1(unsigned int bufSize=10) : AnoP::AnoPsystem<flashSignal1Struct>(bufSize) {
        white[0] = 1;
        white[1] = 1;
        white[2] = 1;
        white[3] = 1;
        redbright[0] = 1;
        redbright[1] = 0;
        redbright[2] = 0;
        redbright[3] = 1;
        reddark[0] = .1;
        reddark[1] = .0;
        reddark[2] = .0;
        reddark[3] = .1;
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
    bool render(flashSignal1Struct &s, unsigned int timeDiff, void * const something) throw() {
        s.step += 5;
        if(s.step>=360) {
            s.step = 0;
        }
        glPushMatrix();
        glTranslated(s.pos[0], s.pos[1], 0);
        double scale = AnoPhelpers::sintab[s.step] / 256. / 100. + .03;
        glScaled(scale, scale, 1);
        //glScaled(.05, .05, 05);
        AnoPhelpers::drawOutlineCircle2(.5, 0, 36, 0, 360, white, reddark);
        AnoPhelpers::drawOutlineCircle2(1., 0, 36, 0, 360, redbright, reddark);
        glPopMatrix();
        return true;
    }

    /// @brief Used colors
    float white[4], redbright[4], reddark[4];
};

#endif

