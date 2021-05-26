#include <GL/glut.h>]
float angle=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glRotatef( angle, 0, 0, 1 );
        glutSolidCube( 0.3 );
    glPopMatrix();
    glutSwapBuffers();
}
int diff=2;
void timer(int t){
    glutTimerFunc(30, timer, t+1);
    glClearColor(1, 0, 0, 0);
    if(angle>90) diff=-2;
    if(angle<0) diff=+2;
    angle += diff;
    display();
}
int main( int argc, char**argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH );
    glutCreateWindow("08160333");
    glutDisplayFunc(display);
     glutTimerFunc( 3000 , timer , 0 );

    glutMainLoop();

}
