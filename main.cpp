#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
// กำหนดตัวแปรสำหรับเก็บข้อมูลของกล้อง
float cameraAngle = 0.0f;
float cameraPosX = 0.0f;
float cameraPosY = 0.0f;
float cameraPosZ = 5.0f;

// ฟังก์ชันสำหรับการกำหนดการมองเห็นของกล้อง
void setCameraView() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPosX, cameraPosY, cameraPosZ, cameraPosX, cameraPosY, cameraPosZ - 1.0f, 0.0f, 1.0f, 0.0f);
}

// ฟังก์ชันสำหรับการแสดงผล
void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    setCameraView();
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(0.0f, 1.0f, -1.0f);
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

// ฟังก์ชันสำหรับการปรับเปลี่ยนมุมมองของกล้อง
void updateCameraView() {
    cameraPosX = 5.0f * sin(cameraAngle);
    cameraPosZ = 5.0f * cos(cameraAngle);
}

// ฟังก์ชันสำหรับการแก้ไขข้อมูลของกล้อง
void update(int value) {
    cameraAngle += 0.01f;
    updateCameraView();
    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

// ฟังก์ชันสำหรับการกดปุ่มบนคีย์บอร์ด
void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Camera");
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(10, update, 0);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
