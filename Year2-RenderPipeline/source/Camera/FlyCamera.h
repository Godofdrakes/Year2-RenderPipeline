#pragma once
#ifndef _FLYCAMERA_H_
#define _FLYCAMERA_H_

#include "Camera.h"
#include <GLFW/glfw3.h>

class FlyCamera : public Camera {
    GLuint up_key_, down_key_, left_key_, right_key_;
    float speed_f_;
    GLFWwindow* window_;
public:
    FlyCamera( const float speed_f, GLFWwindow* const window );
    ~FlyCamera();

    virtual void Update() override;
};

#endif
