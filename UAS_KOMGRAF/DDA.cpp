#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const int window_width = 800;
const int window_height = 600;

void drawLineDDA(float xa, float ya, float xb, float yb) {
    float dx = xb - xa;
    float dy = yb - ya;

    int steps = static_cast<int>(abs(dx) > abs(dy) ? abs(dx) : abs(dy));

    float x_increment = dx / steps;
    float y_increment = dy / steps;

    float x = xa;
    float y = ya;

    glBegin(GL_POINTS);
    for (int i = 0; i < steps; i++) {
        glVertex2f(x, y);
        x += x_increment;
        y += y_increment;
    }
    glEnd();
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    drawLineDDA(100, 200, 400, 600); // A(1,2) ke B(4,6)

    glFlush();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error: GLFW initialization failed" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "DDA Line Drawing Algorithm", NULL, NULL);
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
