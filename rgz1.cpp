#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <GL/freeglut.h>

int Width = 1000, Height = 500;
int delay = 20;
long time0 = 0;
double X, Y;
double AOM, OM, FI;              // Угловое ускорение, скорость и угол поворота
int Xold, Yold;
int Xshow, Yshow;
double K1 = 0.003, K2 = 0.003;    // Коэффициент упругости и затухания
int X0 = 200, Y0 = 250, R = 200;  // Центр и длина маятника
int XG;                           // Текущая точка графика (ось времени)
int RM = 20;

//Функция рисования окружности
void drawCircle(int x, int y, int r, int amountSegments) {
    int i;
    float angle, dx, dy;
    glBegin(GL_POLYGON);
    for (i = 0; i < amountSegments; i++) {
        angle = 2.0 * 3.1415926 * (float)i / (float)amountSegments;
        dx = r * cosf(angle);
        dy = r * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// Функция отрисовки 
void Display(void) {
    glColor3ub(255, 255, 255);
    glBegin(GL_LINE_STRIP);
    glVertex2f(XG - 1, Yold);
    glVertex2f(XG, Yshow);
    glEnd();

    XG++;
    if (XG == Width) XG = Width / 2;

    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(X0, Y0);
    glVertex2f(Xshow, Yshow);
    glEnd();

    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2f(X0, Y0);
    glVertex2f(Xold, Yold);
    glEnd();

    glColor3ub(0, 0, 0);
    drawCircle(Xshow, Yshow, RM, 50);

    glColor3ub(255, 0, 0);
    drawCircle(Xold, Yold, RM, 50);

    Xshow = Xold;
    Yshow = Yold;

    glFlush();
}

// Изменение размера окна
void Reshape(int w, int h) {
    Width = w;
    Height = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Функция анимации
void Idle(void) {
    if (clock() - time0 < delay)
        return;
    time0 = clock();

    AOM = -K1 * sin(FI) - K2 * OM;
    FI += OM;
    OM += AOM;

    X = X0 + R * sin(FI);
    Y = Y0 - R * cos(FI);

    if ((int)X != Xold || (int)Y != Yold) {
        Xold = (int)X;
        Yold = (int)Y;
        glutPostRedisplay();
    }
}

void Keyboard1(unsigned char key, int x, int y) {
    if (key == 27 || key == 13) { // ESC или Enter
        glutLeaveMainLoop();
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    Y0 = Height;
    X0 = Width / 4;
    FI = 3.14;
    OM = 0;
    XG = Width / 2;

    glutInitWindowSize(Width, Height);
    int win = glutCreateWindow("Маятник");
    
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutIdleFunc(Idle);
    glutKeyboardFunc(Keyboard1);

    glutMainLoop(); 
    glutDestroyWindow(win);
    return 0;
}

