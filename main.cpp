#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#define PI 3.14159265

void plot(float x, float y);
void MatrixMultiply(int x, int y, float transformMatrix[3][3]);
using namespace std;
int transformationType = 0;
float returnX = 0, returnY = 0;

void Translate(int x, int y){
    float tx = 50, ty = 50;
    float translateMatrix[3][3] = {{1,0,tx},{0,1,ty},{0,0,1}};
    MatrixMultiply(x,y, translateMatrix);
}

void Rotate(int x, int y){
    float angle = 45 * PI/180;
    float translateMatrix[3][3] = {{cos(angle),-sin(angle),0},{sin(angle),cos(angle),0},{0,0,1}};
    MatrixMultiply(x,y, translateMatrix);
}

void Scale(int x, int y){
    float sx = 2, sy = 2;
    float translateMatrix[3][3] = {{sx,0,0},{0,sy,0},{0,0,1}};
    MatrixMultiply(x,y, translateMatrix);
}

void MatrixMultiply(int x, int y, float transformMatrix[3][3]){
    float inputMatrix[3] = {x,y,1};
    float resultMatrix[3];
    for (int i = 0; i < 3; i++){
        float sum = 0;
        for (int j = 0; j < 3; j++){
            sum += transformMatrix[i][j] * inputMatrix[j];
        }
        resultMatrix[i] = sum;
    }
    returnX = resultMatrix[0];
    returnY = resultMatrix[1];
}

void DrawPolygon(float x1, float x2, float x3,float x4, float y1, float y2, float y3, float y4){
    plot(x1, y1);
    plot(x2, y2);
    plot(x3, y3);
    plot(x4, y4);
}

void DisplayAxes(){
    glColor3ub(255,255,255);
    glBegin(GL_LINES);
        glVertex2f(0,1);
        glVertex2f(0,-1);
        glVertex2f(-1,0);
        glVertex2f(1,0);
    glEnd();
}

void DisplayTransformedObject(){
    glClear(GL_COLOR_BUFFER_BIT);
    DisplayAxes();
    float x1 = 50, x2 = 100, x3 = 100, x4 = 50;
    float y1 = 0, y2 = 0, y3 = 100, y4 = 100;
    glColor3ub(255,0,0);

    glBegin(GL_POLYGON);
        DrawPolygon(x1,x2,x3,x4,y1,y2,y3,y4);
    glEnd();

    glColor3ub(0,0,255);
    glBegin(GL_POLYGON);
        switch(transformationType){
            case 1:
                Translate(x1,y1);
                plot(returnX, returnY);
                Translate(x2,y2);
                plot(returnX, returnY);
                Translate(x3,y3);
                plot(returnX, returnY);
                Translate(x4,y4);
                plot(returnX, returnY);
                break;

            case 2:
                Rotate(x1,y1);
                plot(returnX, returnY);
                Rotate(x2,y2);
                plot(returnX, returnY);
                Rotate(x3,y3);
                plot(returnX, returnY);
                Rotate(x4,y4);
                plot(returnX, returnY);
                break;

            case 3:
                Scale(x1,y1);
                plot(returnX, returnY);
                Scale(x2,y2);
                plot(returnX, returnY);
                Scale(x3,y3);
                plot(returnX, returnY);
                Scale(x4,y4);
                plot(returnX, returnY);
                break;
        }

    glEnd();
    glFlush();
}

void plot(float x, float y)
{
    glVertex2f(x/300, y/300);
}


int main(int argc, char** argv)
{
    cout << ("Enter the mode of transform: \n");
    cout << ("1. Translate \t");
    cout << ("2. Rotate \t");
    cout << ("3. Scale \t");
    cin >> transformationType;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("2D transformation Demo");
    glutDisplayFunc(DisplayTransformedObject);

    glutMainLoop();
    return 0;
}
