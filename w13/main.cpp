#include <opencv/highgui.h> ///�ϥ� OpenCV 2.1 ���²��, �u�n�� High GUI �Y�i
#include <opencv/cv.h>
#include <GL/glut.h>
#include "glm.h"
GLMmodel* pmodel = NULL;
GLuint id1, id2; ///TODO:�W�[2�� �K��ID
void
drawmodel(void)
{
    if (!pmodel) {
    pmodel = glmReadOBJ("Gundam.obj");
    if (!pmodel) exit(0);
    glmUnitize(pmodel);
    glmFacetNormals(pmodel);
    glmVertexNormals(pmodel, 90.0);
    }

    glmDraw(pmodel, GLM_SMOOTH | GLM_TEXTURE);
}
int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCVŪ��
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV���m (�ݭncv.h)
    glEnable(GL_TEXTURE_2D); ///1. �}�ҶK�ϥ\��
    GLuint id; ///�ǳƤ@�� unsigned int ���, �s �K��ID
    glGenTextures(1, &id); /// ����Generate �K��ID
    glBindTexture(GL_TEXTURE_2D, id); ///�j�wbind �K��ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// �K�ϰѼ�, �W�L�]�˪��d��T, �N���жK��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// �K�ϰѼ�, �W�L�]�˪��d��S, �N���жK��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// �K�ϰѼ�, ��j�ɪ�����, �γ̪��I
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// �K�ϰѼ�, �Y�p�ɪ�����, �γ̪��I
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
float angle=180;
void display()
{
    angle++;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, id1);///�ҫ�

    glPushMatrix();
        glRotatef(angle, 0, 1, 0);
        drawmodel();///glutSolidTeapot(0.3);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, id2);///�I����
    glBegin(GL_POLYGON);            ///�Ჾ ���M�|�ҫ��|�Q�I���Y��
        glTexCoord2f( 0, 0 ); glVertex3f( -1, -1, +0.9);
        glTexCoord2f( 0, 1 ); glVertex3f( -1, -1, +0.9);
        glTexCoord2f( 1, 1 ); glVertex3f( -1, -1, +0.9);
        glTexCoord2f( 1, 0 ); glVertex3f( -1, -1, +0.9);
    glEnd();
    glutSwapBuffers();
    glutIdleFunc(display);
}




int main(int argc, char** argv)
{
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_DEPTH );
    glutCreateWindow(" Week13 ");
    glutDisplayFunc(display);

    id1 = myTexture("diffuse.jpg");
    id2 = myTexture("bg.jpg");
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}