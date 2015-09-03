#pragma once
#ifndef _FLYCAMERA_H_
#define _FLYCAMERA_H_

#include <glm/glm.hpp>
#include "Camera.h"
#include "../Input/Input.h"

using glm::vec2;

class FlyCamera : public Camera {
    InputKeyboard up_key_, down_key_, left_key_, right_key_;
    float speed_f_;
    vec2 mouse_old_vec2_;
public:
    FlyCamera( const float speed_f );
    ~FlyCamera();

    virtual void Update() override;
};

#endif
