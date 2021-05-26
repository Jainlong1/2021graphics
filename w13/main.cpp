#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <GL/glut.h>
#include "glm.h"
GLMmodel* pmodel = NULL;
GLuint id1, id2; ///TODO:增加2個 貼圖ID
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
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
float angle=180;
void display()
{
    angle++;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, id1);///模型

    glPushMatrix();
        glRotatef(angle, 0, 1, 0);
        drawmodel();///glutSolidTeapot(0.3);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, id2);///背景圖
    glBegin(GL_POLYGON);            ///後移 不然會模型會被背景吃掉
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
