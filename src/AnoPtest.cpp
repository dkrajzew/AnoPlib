/* *************************************************************************
   @file       AnoP.h
   @project    AnoPlib
   @module     AnoPexamples
   @brief      Some examples
   @date       25.04.2009
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
#include <GL/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <AnoP.h>
#include <AnoPhelpers.h>
#include <math.h>
#include <iostream>
#include <vector>
// examples
#include <AnoPemergency1.h>
#include <AnoPflashlight1.h>
#include <AnoPstarfield1.h>
#include <AnoPtentacle1.h>
#include <AnoPwavelogo1.h>
#include <AnoPwavepropagation1.h>


/* =========================================================================
 * used namespaces
 * ======================================================================= */
using namespace std;


/* =========================================================================
 * global variables
 * ======================================================================= */
// glut window
int win;

// "Anop" text (actually "ANOP")
string anopText[] = {
"      xxxx   xx  xx   xxxx   xxxxx      ",
"     xxxxxx  xx  xx  xxxxxx  xxxxxx     ",
"     xx  xx  xxx xx  xx  xx  xx  xx     ",
"     xx  xx  xxx xx  xx  xx  xx  xx     ",
"     xxxxxx  xxxxxx  xx  xx  xxxxxx     ",
"     xxxxxx  xxxxxx  xx  xx  xxxxx      ",
"     xx  xx  xx xxx  xx  xx  xx         ",
"     xx  xx  xx xxx  xx  xx  xx         ",
"     xx  xx  xx  xx  xxxxxx  xx         ",
"     xx  xx  xx  xx   xxxx   xx         "
};

// pointers to AnoP examples
vector<AnoP::AnoPsystemBase*> anop;

// index of currently shown system
int shown = 0;

// some performance measuring variables
int frame=0,currentTime,timebase=0;

// a text buffer
char s[11];


/* =========================================================================
 * glut stuff
 * ======================================================================= */
void menu(int value){
    if(value == 0){
        glutDestroyWindow(win);
        exit(0);
    } else {
        shown = value - 1;
    }
    glutPostRedisplay();
}


void
display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    anop[shown]->renderAll(0, 0);
    frame++;
	currentTime=glutGet(GLUT_ELAPSED_TIME);
	if (currentTime - timebase > 1000) {
		sprintf(s,"FPS:%4.2f", frame*1000.0/(currentTime-timebase));
		timebase = currentTime;		
		frame = 0;
	}
    glutSetWindowTitle( s );
    glutSwapBuffers();
}


void
init()
{
    /* Enable a single OpenGL light. */
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
    /* Use depth buffering for hidden surface elimination. */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    /* Setup the view of the cube. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(-1,-1,0);
    glScaled(1./20, 1./20, 1.);
    glTranslated(0,15,0);
}


void createMenu(void){
    glutCreateMenu(menu);
    glutAddMenuEntry("Wireless#1", 1);
    glutAddMenuEntry("Wave Logo#1", 2);
    glutAddMenuEntry("Starfield#1", 3);
    glutAddMenuEntry("Emergency#1", 4);
    glutAddMenuEntry("Signal#1", 5);
    glutAddMenuEntry("Tentacle#1", 6);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


/* =========================================================================
 * main
 * ======================================================================= */
int
main(int argc, char **argv)
{
	AnoPhelpers::init();
    // wireless effect
    AnoPwavepropagation1 *awp = new AnoPwavepropagation1(5);
    for(int i=0; i<5; ++i) {
        wireless1Struct s;
        s.pos[0] = (double) rand() / (double) (RAND_MAX-1) * 400.;
        s.pos[1] = (double) rand() / (double) (RAND_MAX-1) * 400.;
        s.step = (double) rand() / (double) (RAND_MAX-1) * 500.;
        awp->addAnimlet(s);
    }
    anop.push_back(awp);
    // wave effect
    AnoPwavelogo1 *awl = new AnoPwavelogo1(1);
    for(unsigned int y=0; y<10; ++y) {
        for(unsigned int x=0; x<anopText[y].length(); ++x) {
            if(anopText[y][x]!=' ') {
                waveStruct s;
                s.step = ((x+y)*10)%360;
                s.pos[0] = x;
                s.pos[1] = 10-y;
                awl->addAnimlet(s);
            }
        }
    }
    anop.push_back(awl);
    // starfield effect
    AnoPstarfield1 *asf = new AnoPstarfield1(1000);
    for(int i=0; i<1000; ++i) {
        starfield1Struct s;
        s.pos[0] = (double) rand() / (double) (RAND_MAX-1) * 40.;
        s.pos[1] = (double) rand() / (double) (RAND_MAX-1) * 10.;
        s.speed = (double) rand() / (double) (RAND_MAX-1) * .1;
        asf->addAnimlet(s);
    }
    anop.push_back(asf);
    // emergency effect
    AnoPemergency1 *ae = new AnoPemergency1(10);
    for(int i=0; i<10; ++i) {
        emergency1Struct s;
        s.pos[0] = (double) rand() / (double) (RAND_MAX-1) * 400.;
        s.pos[1] = (double) rand() / (double) (RAND_MAX-1) * 400.;
        s.step = (double) rand() / (double) (RAND_MAX-1) * 360.;
        ae->addAnimlet(s);
    }
    anop.push_back(ae);
    // red signal effect
    AnoPflashlight1 *afl = new AnoPflashlight1(40);
    for(int i=0; i<40; ++i) {
        flashSignal1Struct s;
        s.pos[0] = 10 * double(i);
        s.pos[1] = 10 * double(i);
        s.step = i * 10;
        afl->addAnimlet(s);
    }
    anop.push_back(afl);
    // tentacle
    AnoPtentacle1 *at = new AnoPtentacle1(40);
    for(int i=0; i<40; ++i) {
        at->addAnimlet(i);
    }
    anop.push_back(at);
    // run
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    win = glutCreateWindow("AnoPlib examples");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    createMenu();
    glClearColor(0.0,0.0,0.0,0.0);
    init();
    glutMainLoop();
	AnoPhelpers::close();
    return 0;
}
