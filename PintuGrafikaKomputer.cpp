#include <GL/glut.h>
#include <GL/glu.h>

float doorAngle = 0.0f;
bool isOpening = false;
bool isClosing = false;

void drawDoor3D() {
    float thickness = 0.1f;
    glPushMatrix();

    // Pivot Pintu
    glTranslatef(-0.5f, 0.0f, 0.0f);
    glRotatef(doorAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.5f, 0.0f, 0.0f);

    // Pintu
    glColor3f(0.36f, 0.25f, 0.20f); // Warna Pintu
    glBegin(GL_QUADS);
    // Depan
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.5f, -1.0f, thickness);
    glVertex3f(0.5f, -1.0f, thickness);
    glVertex3f(0.5f, 1.0f, thickness);
    glVertex3f(-0.5f, 1.0f, thickness);

    // Belakang
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-0.5f, -1.0f, -thickness);
    glVertex3f(0.5f, -1.0f, -thickness);
    glVertex3f(0.5f, 1.0f, -thickness);
    glVertex3f(-0.5f, 1.0f, -thickness);

    // Kiri
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-0.5f, -1.0f, -thickness);
    glVertex3f(-0.5f, -1.0f, thickness);
    glVertex3f(-0.5f, 1.0f, thickness);
    glVertex3f(-0.5f, 1.0f, -thickness);

    // Kanan
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.5f, -1.0f, -thickness);
    glVertex3f(0.5f, -1.0f, thickness);
    glVertex3f(0.5f, 1.0f, thickness);
    glVertex3f(0.5f, 1.0f, -thickness);

    // Atas
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 1.0f, -thickness);
    glVertex3f(0.5f, 1.0f, -thickness);
    glVertex3f(0.5f, 1.0f, thickness);
    glVertex3f(-0.5f, 1.0f, thickness);

    // Bawah
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-0.5f, -1.0f, -thickness);
    glVertex3f(0.5f, -1.0f, -thickness);
    glVertex3f(0.5f, -1.0f, thickness);
    glVertex3f(-0.5f, -1.0f, thickness);
    glEnd();

    // Gagang pintu
    glPushMatrix();
    glColor3f(1.0f, 0.85f, 0.2f); // Warna gagang pintu
    glTranslatef(0.4f, 0.3f, thickness + 0.03f);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    GLUquadric* handle = gluNewQuadric();
    gluCylinder(handle, 0.03f, 0.03f, 0.6f, 30, 30);
    gluDeleteQuadric(handle);
    glPopMatrix();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(2.0, 1.3, 3.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    drawDoor3D();

    glutSwapBuffers();
}

void update(int value) {
    if (isOpening && doorAngle < 90.0f) {
        doorAngle += 2.0f;
        if (doorAngle > 90.0f) doorAngle = 90.0f;
    }
    else if (isClosing && doorAngle > 0.0f) {
        doorAngle -= 2.0f;
        if (doorAngle < 0.0f) doorAngle = 0.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'o': case 'O':
        isOpening = true;
        isClosing = false;
        break;
    case 'c': case 'C':
        isClosing = true;
        isOpening = false;
        break;
    case 27:
        exit(0);
        break;
    }
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    GLfloat light_pos[] = { 2.0f, 3.0f, 2.0f, 1.0f };
    GLfloat light_dif[] = { 0.9f, 0.9f, 0.8f, 1.0f };
    GLfloat light_amb[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat light_spec[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);

    GLfloat mat_spec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 64.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glClearColor(0.12f, 0.12f, 0.15f, 1.0f);

    doorAngle = 0.0f; // posisi awal: tertutup penuh
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect, 0.1, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 700);
    glutCreateWindow("Pintu 3D Nasywa Elsa dan Muhamad Ihda");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}
