#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

const int window_width = 800;
const int window_height = 600;

void rotatePoint(float& x, float& y, float angle) {
    float radian = angle * (3.14159265358979323846 / 180.0);
    float newX = x * cos(radian) - y * sin(radian);
    float newY = x * sin(radian) + y * cos(radian);
    x = newX;
    y = newY;
}

void drawLineBresenham(int x1, int y1, int x2, int y2, float angle) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int twoDy = 2 * dy;
    int twoDyMinusDx = 2 * (dy - dx);
    int twoDx = 2 * dx;
    int twoDxMinusDy = 2 * (dx - dy);

    int x, y, xe, ye;

    if (x1 < x2) {
        x = x1;
        y = y1;
        xe = x2;
    } else {
        x = x2;
        y = y2;
        xe = x1;
    }

    glBegin(GL_POINTS);
    glVertex2i(x, y);

    while (x < xe) {
        x = x + 1;
        if (twoDx < twoDy) {
            if (twoDxMinusDy >= 0) {
                y = y + 1;
                twoDx = twoDx + twoDxMinusDy;
            } else {
                twoDx = twoDx + twoDy;
            }
        } else {
            if (twoDxMinusDy >= 0) {
                twoDx = twoDx + twoDy;
            } else {
                y = y + 1;
                twoDx = twoDx + twoDyMinusDx;
            }
        }

        float xf = static_cast<float>(x);
        float yf = static_cast<float>(y);
        rotatePoint(xf, yf, angle);
        glVertex2f(xf, yf);
    }
    glEnd();
}

void render(float angle) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    drawLineBresenham(100, 200, 400, 600, angle); // A(1,2) ke B(4,6)

    glFlush();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error: GLFW initialization failed" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Rotated Bresenham Line", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Error: Failed to create GLFW window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window_width, 0, window_height, -1, 1);

    float rotationAngle = 45.0f;

    while (!glfwWindowShouldClose(window)) {
        render(rotationAngle);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
