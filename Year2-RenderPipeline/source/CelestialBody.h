#pragma once
#ifndef _CELESTIALBODY_H_
#define _CELESTIALBODY_H_

#include <Gizmos/Gizmos.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

enum CelestialBody_Type {
    SPHERE,
    RING
};

class CelestialBody {
    int quality_i_;

    vec4 color_vec4_;

    mat4 scale_mat4_;
    mat4 position_mat4_;
    mat4 rotation_local_mat4_;
    mat4 rotation_global_mat4_;
    mat4 transform_mat4_;

public:
    CelestialBody* parent;
    CelestialBody_Type bodyType;

    CelestialBody();
    CelestialBody( const int set_quality_i, const CelestialBody_Type type );
    ~CelestialBody();

    void SetQuality( const int set_quality_i );

    void Update();
    void Draw() const;

    void SetColor( const vec4 set_color_vec4 );
    void SetColor( const float r, const float g, const float b, const float a );

    void SetScale( const vec3 set_scale_vec3 );
    void SetScale( const float x, const float y, const float z );

    void SetPosition( const vec3 set_pos_vec3 );
    void SetPosition( const float x, const float y, const float z );

    void SetGlobalRotation( const float deg_f, const vec3 set_rot_vec3 );
    void SetGlobalRotation( const float deg_f, const float x, const float y, const float z );

    void SetLocalRotation( const float deg_f, const vec3 set_rot_vec3 );
    void SetLocalRotation( const float deg_f, const float x, const float y, const float z );

private:
    mat4 CalculateGlobalTransform() const;
    mat4 CalculateLocalTransform() const;
};

#endif
