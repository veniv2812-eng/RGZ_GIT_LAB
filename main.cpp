#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>

void waitForEnter() {
    printf("\nPress Enter to return menu");
    getchar();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    int choice;
    int exit = 0;

    while (!exit) {
        system("cls");

        printf("        MAIN MENU              \n");
        printf("================================\n");
        printf("1. Run RGZ 1\n");
        printf("2. Run RGZ 2\n");
        printf("0. Exit\n");
        printf("================================\n");
        printf("Your choice: ");

        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                system("rgz1.exe");
                waitForEnter();
                break;
            case 2:
                system("rgz2.exe");
                waitForEnter();
                break;
            case 0:
                exit = 1;
                break;
             default:
                printf("Invalid choice!");
                waitForEnter();
        }
    }

    return 0;
}