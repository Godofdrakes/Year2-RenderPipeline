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

    mat4 rotation_local_mat4_;

    mat4 rotation_global_mat4_;

    mat4 transform_mat4_;

public:
    CelestialBody* parent;

    CelestialBody();
    CelestialBody( int set_quality_i );
    ~CelestialBody();

    void Update();
    void Draw() const;

    void SetColor( vec4 set_color_vec4 );
    void SetColor( float r, float g, float b, float a );

    void SetScale( vec3 set_scale_vec3 );
    void SetScale( float x, float y, float z );

    void SetPosition( vec3 set_pos_vec3 );
    void SetPosition( float x, float y, float z );

    void SetGlobalRotation( float deg_f, vec3 set_rot_vec3 );
    void SetGlobalRotation( float deg_f, float x, float y, float z );

    void SetLocalRotation( float deg_f, vec3 set_rot_vec3 );
    void SetLocalRotation( float deg_f, float x, float y, float z );

private:
    mat4 CalculateGlobalTransform() const;
    mat4 CalculateLocalTransform() const;
};

#endif
