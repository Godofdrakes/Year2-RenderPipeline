#include <iostream>

#include "gl_core_4_4.h"

#include "GLFW\glfw3.h"

#include "Gizmos.h"

#include <glm\glm.hpp>
#include <glm\ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

const char* PROJECT_NAME = "Year2-RenderPipline";

int main() {
    if ( glfwInit() == false ) { return -1; }

    GLFWwindow* window = glfwCreateWindow( 1280, 720, PROJECT_NAME, nullptr, nullptr );

    if ( window == nullptr ) {
        glfwTerminate();
        return -2;
    }

    glfwMakeContextCurrent( window );

    if ( ogl_LoadFunctions() == ogl_LOAD_FAILED ) {
        glfwDestroyWindow( window );
        glfwTerminate();
        return -3;
    }

    const int OGL_MAJOR = ogl_GetMajorVersion();
    const int OGL_MINOR = ogl_GetMinorVersion();
    printf( "OpenGL Version: %i.%i\n", OGL_MAJOR, OGL_MINOR );

    Gizmos::create();

    mat4 view = glm::lookAt( vec3( 10, 10, 10 ), vec3( 0 ), vec3( 0, 1, 0 ) );
    mat4 projection = glm::perspective( glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f );

    glClearColor( 0.25f, 0.25f, 0.25f, 1.0f );

    while ( glfwWindowShouldClose( window ) == false &&
            glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS ) {

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // Stuff
        Gizmos::clear();

        Gizmos::addTransform( mat4( 1 ) );

        vec4 white( 1 );
        vec4 black( 0, 0, 0, 1 );

        for ( int n = 0; n < 21; ++n ) {
            Gizmos::addLine( vec3( -10 + n, 0, 10 ),
                             vec3( -10 + n, 0, -10 ),
                             n == 10 ? white : black );
            Gizmos::addLine( vec3( 10, 0, -10 + n ),
                             vec3( -10, 0, -10 + n ),
                             n == 10 ? white : black );
        }

        Gizmos::draw( projection * view );

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    Gizmos::destroy();

    glfwDestroyWindow( window );

    glfwTerminate();
    return 0;
}