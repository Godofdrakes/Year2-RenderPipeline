#include "CelestialBody.h"

CelestialBody::CelestialBody() : CelestialBody( 15, SPHERE ) {}

CelestialBody::CelestialBody( const int set_quality_i, const CelestialBody_Type type ) {
    bodyType = type;
    scale_mat4_ = mat4( 1 );

    quality_i_ = set_quality_i;

    color_vec4_ = vec4( 0 );

    position_mat4_ = mat4( 1 );

    rotation_local_mat4_ = mat4( 1 );
    rotation_global_mat4_ = mat4( 1 );

    parent = nullptr;
}

CelestialBody::~CelestialBody() {}

void CelestialBody::SetQuality( const int set_quality_i ) {
    quality_i_ = set_quality_i;
}

void CelestialBody::Update() {
    transform_mat4_ = CalculateGlobalTransform() * CalculateLocalTransform();
}

void CelestialBody::Draw() const {
    Gizmos::addSphere( vec3( 0 ),
                       1.f,
                       quality_i_,
                       quality_i_,
                       color_vec4_,
                       &transform_mat4_ );
}

void CelestialBody::SetColor( const vec4 set_color_vec4 ) {
    color_vec4_ = set_color_vec4;
}

void CelestialBody::SetColor( const float r, const float g, const float b, const float a ) {
    color_vec4_ = vec4( r, g, b, a );
}

void CelestialBody::SetScale( const vec3 set_scale_vec3 ) {
    scale_mat4_ = glm::scale( set_scale_vec3 );
}

void CelestialBody::SetScale( const float x, const float y, const float z ) {
    scale_mat4_ = glm::scale( vec3( x, y, z ) );
}

void CelestialBody::SetPosition( const vec3 set_pos_vec3 ) {
    position_mat4_ = glm::translate( set_pos_vec3 );
}

void CelestialBody::SetPosition( const float x, const float y, const float z ) {
    position_mat4_ = glm::translate( vec3( x, y, z ) );
}

void CelestialBody::SetGlobalRotation( const float deg_f, const vec3 set_rot_vec3 ) {
    rotation_global_mat4_ = glm::rotate( glm::radians( deg_f ), set_rot_vec3 );
}

void CelestialBody::SetGlobalRotation( const float deg_f, const float x, const float y, const float z ) {
    rotation_global_mat4_ = glm::rotate( glm::radians( deg_f ), vec3( x, y, z ) );
}

void CelestialBody::SetLocalRotation( const float deg_f, const vec3 set_rot_vec3 ) {
    rotation_local_mat4_ = glm::rotate( glm::radians( deg_f ), set_rot_vec3 );
}

void CelestialBody::SetLocalRotation( const float deg_f, const float x, const float y, const float z ) {
    rotation_local_mat4_ = glm::rotate( glm::radians( deg_f ), vec3( x, y, z ) );
}

mat4 CelestialBody::CalculateGlobalTransform() const {
    mat4 matrix = mat4( 1 );
    if ( parent != nullptr ) {
        matrix = parent->CalculateGlobalTransform();
    }
    return matrix * rotation_global_mat4_ * position_mat4_;
}

mat4 CelestialBody::CalculateLocalTransform() const {
    return rotation_local_mat4_ * scale_mat4_;
}