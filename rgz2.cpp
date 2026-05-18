#include <GL/freeglut.h>
#include <cmath>

static int Width2 = 300, Height2 = 300;
static float angle = 0;

void Display2() {
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    angle += 0.1f;
    float cx = Width2 / 2;
    float cy = Height2 / 2;

    glColor3f(0, 0, 0);

    // Голова
    glBegin(GL_POLYGON);
    for (int i = 0; i < 12; i++) {
        float a = 2 * 3.14159 * i / 12;
        glVertex2f(cx + cos(a) * 10, cy - 30 + sin(a) * 10);
    }
    glEnd();

    // Тело
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2f(cx, cy - 20);
    glVertex2f(cx, cy + 20);
    glEnd();

    // Руки
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(cx, cy);
    glVertex2f(cx - 20, cy - 15);
    glVertex2f(cx, cy);
    glVertex2f(cx + 20, cy - 15);
    glEnd();

    // Ноги
    glLineWidth(6);
    float step = sin(angle) * 12;

    glBegin(GL_LINES);
    glVertex2f(cx, cy + 20);
    glVertex2f(cx - 15 + step, cy + 50);
    glVertex2f(cx, cy + 20);
    glVertex2f(cx + 15 - step, cy + 50);
    glEnd();

    glFlush();
}

void Timer2(int) {
    glutPostRedisplay();
    glutTimerFunc(16, Timer2, 0);
}

void Keyboard2(unsigned char key, int x, int y) {
    if (key == 27 || key == 13) {
        glutLeaveMainLoop();
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(Width2, Height2);
    int win = glutCreateWindow("Шагающий человечек");
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Width2, Height2, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(Display2);
    glutTimerFunc(0, Timer2, 0);
    glutKeyboardFunc(Keyboard2);

    glutMainLoop();
    glutDestroyWindow(win);
    return 0;
}

