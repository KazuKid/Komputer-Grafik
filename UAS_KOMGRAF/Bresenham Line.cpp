#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const int window_width = 800;
const int window_height = 600;

void drawLineBresenham(int xa, int ya, int xb, int yb) {
    int dx = abs(xb - xa);
    int dy = abs(yb - ya);

    int twoDy = 2 * dy;
    int twoDyMinusDx = 2 * (dy - dx);
    int p = 2 * dy - dx;

    int x, y;
    if (xa > xb) {
        x = xb;
        y = yb;
        xb = xa;
    }
    else {
        x = xa;
        y = ya;
    }

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    while (x < xb) {
        x++;
        if (p < 0) {
            p += twoDy;
        }
        else {
            y++;
            p += twoDyMinusDx;
        }
        glVertex2i(x, y);
    }
    glEnd();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    drawLineBresenham(100, 200, 400, 600); // A(1,2) ke B(4,6)

    glFlush();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error: GLFW initialization failed" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Bresenham Line Drawing Algorithm", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Error: Failed to create GLFW window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window_width, 0, window_height, -1, 1);

    while (!glfwWindowShouldClose(window)) {
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}