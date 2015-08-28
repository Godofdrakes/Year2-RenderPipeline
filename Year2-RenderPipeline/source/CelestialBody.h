#pragma once
#ifndef _CELESTIALBODY_H_
#define _CELESTIALBODY_H_

#include "Gizmos.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

using glm::vec3;
using glm::vec4;
using glm::mat4;

class CelestialBody {
    mat4 scale_mat4_;

    int quality_i_;

    vec4 color_vec4_;

    mat4 position_mat4_;

    mat4 local_rotation_mat4_;

    mat4 global_rotation_mat4_;

    mat4 transform_mat4_;
public:
    CelestialBody( int set_quality_i = 5,
                   vec4 set_color_vec4 = vec4( 1 ),
                   float set_scale_f = 1.f,
                   vec3 set_offset_vec3 = vec3(0) );
    ~CelestialBody();

    void Update();
    void Draw() const;

    void SetPosition( vec3 set_pos_vec3 );
};

#endif
