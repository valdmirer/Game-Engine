#include "SubSystemLayer.cpp"
#include <iostream>

// Window Creation
class Platform {
    private:
        int x;
        int y;
        GLFWwindow* window;
        const char* windowName;

    public:
        void createWindow(int a, int b, const char* name) {
            x = a;
            y = b;
            windowName = name;
            if (!glfwInit()) {
                std::cerr << "Glfw window not initialized" << std::endl;
                return;
            }
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required for macOS
        #endif
            window = glfwCreateWindow(x, y, windowName, 0, 0);
            if (!window) {
                std::cerr << "Window not created!" << std::endl;
                return;
            }
            glfwMakeContextCurrent(window);

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
                std::cerr << "Failed to initialize GLAD" << std::endl;
                return;
            }

            InputSystem input;
            input.init(window);

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            float vertices[] = {
                 0.0f,  0.5f, 0.0f,  // top right
                 0.5f, -0.5f, 0.0f,  // bottom right
                -0.5f, -0.5f, 0.0f,  // bottom left
                -0.5f,  0.5f, 0.0f   // top left
            };

            unsigned int VAO, VBO;

            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            // 1. Bind VAO first
            glBindVertexArray(VAO);

            // 2. Bind and fill VBO
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            // 3. Tell OpenGL how to interpret the vertex data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            // 4. Unbind (optional but good practice)
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);


            // Event Polling
            while (!glfwWindowShouldClose(window)) {
                glClear(GL_COLOR_BUFFER_BIT);

                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 3);

                if (input.isKeyJustPressed(GLFW_KEY_SPACE)) std::cout << "Space key Pressed!" << std::endl;
                if (input.isKeyDown(GLFW_KEY_W)) std::cout << "W key Down!" << std::endl;
                if (input.isMouseButtonDown(0))  std::cout << "mouse 0 down!" << std::endl;
                glfwSwapBuffers(window);
                glfwPollEvents();

                // Hardware Abstraction
                // 1 Action Mapping
                // 2 Input Rebindin
                // 3 Controller Support
            }
            glfwTerminate();
        }
};
