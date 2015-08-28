#include "CelestialBody.h"



CelestialBody::CelestialBody( int set_quality_i,
                              vec4 set_color_vec4,
                              float set_scale_f,
                              vec3 set_offset_vec3 ) {

    scale_mat4_ = glm::scale( vec3( set_scale_f, set_scale_f, set_scale_f ) );

    quality_i_ = set_quality_i;

    color_vec4_ = set_color_vec4;

    position_mat4_ = glm::translate( set_offset_vec3 );

    local_rotation_mat4_ = mat4( 0 );

    global_rotation_mat4_ = mat4( 0 );
}

CelestialBody::~CelestialBody() {

}

void CelestialBody::Update() {
    transform_mat4_ = global_rotation_mat4_ * position_mat4_ * local_rotation_mat4_ * scale_mat4_;
}

void CelestialBody::Draw() const {
    Gizmos::addSphere( vec3( 0 ),
                       1.f,
                       quality_i_,
                       quality_i_,
                       color_vec4_,
                       &transform_mat4_ );
}

void CelestialBody::SetPosition(vec3 set_pos_vec3) {
    position_mat4_ = glm::translate( set_pos_vec3 );
}