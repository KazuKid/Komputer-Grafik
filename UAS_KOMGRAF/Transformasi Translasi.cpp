#include <GLFW/glfw3.h>
#include <iostream>

// Koordinat titik A
float x = 1.0f;
float y = 2.0f;

// Fungsi untuk menggambar titik pada posisi (x, y)
void drawPoint(float x, float y) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Menggambar titik A(1,2) dengan transformasi translasi
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(x, y, 0.0f);

    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f); // Titik A(1,2)
    glEnd();
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Gagal menginisialisasi GLFW" << std::endl;
        return -1;
    }

    // Konfigurasi GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Membuat window GLFW
    GLFWwindow* window = glfwCreateWindow(800, 600, "Transformasi Translasi", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glViewport(0, 0, 800, 600);

    glMatrixMode(GL_PROJECTION);
    glOrtho(0.0, 8.0, 0.0, 6.0, -1.0, 1.0);

    while (!glfwWindowShouldClose(window)) {
        drawPoint(x, y);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}