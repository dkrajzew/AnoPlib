/* *************************************************************************
   @file       AnoPtentacle1.h
   @project    AnoPlib
   @module     AnoPtentacle1
   @brief      Four moving tentacle arms
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
#ifndef ANOP_TENTACLE1
#define ANOP_TENTACLE1


/* =========================================================================
 * included modules
 * ======================================================================= */
#include <AnoP.h>
#include <AnoPhelpers.h>
#include <GL/gl.h>


/* =========================================================================
 * class and struct definitions
 * ======================================================================= */
/** @class AnoPtentacle1
 * @brief Four moving tentacle arms
 */ 
class AnoPtentacle1 : public AnoP::AnoPsystem<int> {
public:
    /** @brief Constructor
     * @param[in] bufSize The number of animlets to pre-allocate
     */    
    AnoPtentacle1(unsigned int bufSize=10) : AnoP::AnoPsystem<int>(bufSize) {
        pos = 0;
    }


    /** @brief Pre-rendering step
     */    
    void preRender() throw() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glScaled(1./10, 1./10, 1.);
        glPushMatrix();
        glEnable (GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        glDepthMask(GL_FALSE);
        pos = pos + 1;
        if(pos>=360) {
            pos = pos - 360;
        }
        glPopMatrix();
    }


    /** @brief Rendering step
     * @param[in] s The settings of the animlet to render
     * @param[in] timeDiff The time passed since last call
     * @param[in] something Not used here
     */                   
    bool render(int &s, unsigned int timeDiff, void * const something) throw() {
        if(s%10==0) {
            glPopMatrix();
            glRotated(90., 0, 0, 1);
            glPushMatrix();
        }
        glRotated(AnoPhelpers::sintab[pos]/16., 0, 0, 1);
        glTranslated(2.2, 0, 0);
        glScaled(.8,.8,.8);
        glColor3f(1,1,1);
        glBegin(GL_QUADS);
        glVertex3f(-1,-1,0);
        glVertex3f(-1,1,0);
        glVertex3f(1,1,0);
        glVertex3f(1,-1,0);
        glEnd();
        return true;
    }

    /// @brief The global step
    int pos;

};

#endif
