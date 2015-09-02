#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <string>
#include <array>
#include "gl_core_4_4.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "CelestialBody.h"

using std::string;
using std::array;
using glm::vec3;
using glm::vec4;
using glm::mat4;

enum ApplicationFail {
    NONE,
    GLFW_INIT,
    GLFW_CREATE_WINDOW,
    OGL_LOAD_FUNCTIONS,
};

class Application {
    string name_string_;
    int width_i_, height_i_;
    GLFWwindow* window_glfw_;

    mat4 view_mat4_, projection_mat4_;

    const double TICK_PER_SEC_D_;
    double time_current_d_, time_previous_d_, time_elapsed_d_, time_lag_d_;

    array<CelestialBody*, 2> celestial_body;
public:
    Application();
    Application( string set_name );
    Application( string set_name, int set_width, int set_height );
    ~Application();

    ApplicationFail Init();
    void Shutdown();

    bool Update();
    void Tick();
    void Draw();
};

#endif
