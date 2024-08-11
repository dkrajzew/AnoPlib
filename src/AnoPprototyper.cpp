#include <AnoP.h>
//#include <AnoPpos.h>
#include <AnoPprot.h>
#include <glut.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

// sinus/cosinus tables
double *sintab, *costab;
    int camera_rotation = 0;


int frame=0,time=0,timebase=0;
int newtime=0, oldtime=0;
char s[11];

AnoP::AnoPsystemBase *sys = 0;

void
display(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    double camera_x=sintab[camera_rotation]*30./256.;
    double camera_y=costab[camera_rotation]*30./256.;
    glRotated(camera_x, 1, 0, 0);
    glRotated(camera_y, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glScaled(.5,.5,.5);
    if(sys!=0) {
    	newtime=glutGet(GLUT_ELAPSED_TIME);
        sys->renderAll(newtime-oldtime, 0);
        oldtime = newtime;
    }
    frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		sprintf(s,"FPS:%4.2f",
			frame*1000.0/(time-timebase));
		timebase = time;		
		frame = 0;
	}
    glutSetWindowTitle( s );
    /*
	glColor3f(0.0f,1.0f,1.0f);
	glPushMatrix();
	glLoadIdentity();
	setOrthographicProjection();
	renderBitmapString(30,35,(void *)font,s);
	glPopMatrix();
	resetPerspectiveProjection();
    */
    glutSwapBuffers();
    camera_rotation++;
    if(camera_rotation>=360) {
        camera_rotation = 0;
    }
}

void
init(void)
{
    /* Enable a single OpenGL light. */
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);

    /* Use depth buffering for hidden surface elimination. */
    glEnable(GL_DEPTH_TEST);

    /* Setup the view of the cube. */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

int
main(int argc, char **argv)
{
    // init tabs
    double PI = 3.1415926535897932384626433832795;
    sintab = new double[360];
    costab = new double[360];
    for(int i=0; i<360; ++i) {
        sintab[i] = 256. * sin(PI/180.*(double)i);
        costab[i] = 256. * cos(PI/180.*(double)i);
    }
    ifstream strm(argv[1]);
    sys = AnoP::prototyping::parse(strm);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("AnoPlib examples");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glClearColor(0.0,0.0,0.0,0.0);
    init();
    glutMainLoop();
    return 0;
}

