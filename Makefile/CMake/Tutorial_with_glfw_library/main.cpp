#include <iostream>
#include "adder.h"
#include "GLFW/glfw3.h"

void glfw_part()
{
    // Initialize the window
    GLFWwindow* window;
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit( EXIT_FAILURE );
    }

    // Create window with specified size
    window = glfwCreateWindow( 300, 300, "Gears", NULL, NULL );
    if (!window)
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    }

    // Open the window and keep it opened
    while( !glfwWindowShouldClose(window) )
    {
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
}

int main()
{
    std::cout << "Hello CMake!" << std::endl;
    std::cout << "Adder result = " << add(17.3f, 16.5f) << std::endl;

    glfw_part();

    return 0;
}