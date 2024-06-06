#include <GLFW/glfw3.h>
#include <cmath>

// Function to draw a circle
void drawCircle(float centerX, float centerY, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // Center of circle
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * 3.14159268 * float(i) / float(segments);
        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "Three Circles", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Set the viewport
    glViewport(0, 0, 640, 480);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 640, 0, 480, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw three circles
        glColor3f(1.0f, 0.0f, 0.0f); // Red color
        drawCircle(160.0f, 240.0f, 50.0f, 100);

        glColor3f(0.0f, 1.0f, 0.0f); // Green color
        drawCircle(320.0f, 240.0f, 50.0f, 100);

        glColor3f(0.0f, 0.0f, 1.0f); // Blue color
        drawCircle(480.0f, 240.0f, 50.0f, 100);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
