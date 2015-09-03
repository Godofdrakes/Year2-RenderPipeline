#include "FlyCamera.h"

FlyCamera::FlyCamera( const float speed_f, GLFWwindow* const window )
    : up_key_( GLFW_KEY_W ), down_key_( GLFW_KEY_S ),
    left_key_( GLFW_KEY_A ), right_key_( GLFW_KEY_D ),
    speed_f_( speed_f ), window_( window ) {}

FlyCamera::~FlyCamera() {}


void FlyCamera::Update() {
    // Conflicting keys should just cancel eachother out.
    if ( glfwGetKey( window_, up_key_ ) == GLFW_PRESS ) {
        position_vec3_.y += speed_f_;
    }
    if ( glfwGetKey( window_, down_key_ ) == GLFW_PRESS ) {
        position_vec3_.y -= speed_f_;
    }
    if ( glfwGetKey( window_, left_key_ ) == GLFW_PRESS ) {
        position_vec3_.x -= speed_f_;
    }
    if ( glfwGetKey( window_, right_key_ ) == GLFW_PRESS ) {
        position_vec3_.x += speed_f_;
    }
    SetLookAt( position_vec3_, lookAt_vec3_, up_vec3_ );
}