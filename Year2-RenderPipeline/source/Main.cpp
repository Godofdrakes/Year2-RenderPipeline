#include <iostream>

#include "gl_core_4_4.h"

#include "GLFW\glfw3.h"

#include "Gizmos.h"

#include <glm\glm.hpp>
#include <glm\ext.hpp>

#include "CelestialBody.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

const char* PROJECT_NAME = "Year2-RenderPipline";
double time_previous_d = 0.0;
const double TIME_TICK_RATE_D = 1.0 / 60.0;

const vec4 COLOR_WHITE( 1.f, 1.f, 1.f, 1.f );
const vec4 COLOR_BLACK( 0.f, 0.f, 0.f, 1.f );

int main() {
    if ( glfwInit() == false ) { return -1; }

    time_previous_d = glfwGetTime();
    double time_lag_d = 0.0;

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

    const int NUMBER_BODIES = 4;
    CelestialBody celestial_body[NUMBER_BODIES] = {};

    celestial_body[0] = CelestialBody();
    celestial_body[0].SetPosition( 4.5f, 0.f, 0.f );
    celestial_body[0].SetScale( 0.5f, 0.5f, 0.5f );
    celestial_body[0].SetColor( 0.f, 0.5f, 0.f, 1.f );

    celestial_body[1] = CelestialBody();
    celestial_body[1].SetPosition( 1.f, 0.f, 0.f );
    celestial_body[1].SetScale( 0.1f, 0.1f, 0.1f );
    celestial_body[1].SetColor( 0.25f, 0.25f, 0.25f, 1.f );
    celestial_body[1].parent = &celestial_body[0];

    celestial_body[2] = CelestialBody();
    celestial_body[2].SetPosition( 0.f, 0.f, 7.f );
    celestial_body[2].SetScale( 1.f, 1.f, 1.f );
    celestial_body[2].SetColor( 1.f, 0.25f, 0.f, 1.f );

    celestial_body[3] = CelestialBody();
    celestial_body[3].SetPosition( 0.f, 0.f, 0.f );
    celestial_body[3].SetScale( 1.5f, 1.5f, 1.5f );
    celestial_body[3].SetColor( 1.f, 1.f, 0.f, 1.f );

    float number = 0;

    while ( glfwWindowShouldClose( window ) == false &&
            glfwGetKey( window, GLFW_KEY_ESCAPE ) != GLFW_PRESS ) {

        double time_current_d = glfwGetTime();
        double time_elapsed_d = time_current_d - time_previous_d;
        time_previous_d = time_current_d;
        time_lag_d += time_elapsed_d;

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // Stuff
        Gizmos::clear();

        Gizmos::addTransform( mat4( 1 ) );

        // Update Objects
        while ( time_lag_d >= TIME_TICK_RATE_D ) {
            for ( int n = 0; n < NUMBER_BODIES; ++n ) {
                celestial_body[n].SetGlobalRotation( number, vec3( 0.f, 1.f, 0.f ) );
                celestial_body[n].Update();
            }
            number += 1.f;
            if ( number >= 360.f ) { number = 0.f; }

            time_lag_d -= TIME_TICK_RATE_D;
        }

        // Draw Objects
        for ( int n = 0; n < 21; ++n ) {
            Gizmos::addLine( vec3( -10 + n, 0, 10 ),
                             vec3( -10 + n, 0, -10 ),
                             n == 10 ? COLOR_WHITE : COLOR_BLACK );
            Gizmos::addLine( vec3( 10, 0, -10 + n ),
                             vec3( -10, 0, -10 + n ),
                             n == 10 ? COLOR_WHITE : COLOR_BLACK );
        }

        for ( int n = 0; n < NUMBER_BODIES; ++n ) { celestial_body[n].Draw(); }

        // Render all
        Gizmos::draw( projection * view );

        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    Gizmos::destroy();

    glfwDestroyWindow( window );

    glfwTerminate();
    return 0;
}