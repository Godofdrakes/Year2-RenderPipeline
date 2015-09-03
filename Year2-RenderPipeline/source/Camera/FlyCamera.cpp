#include "FlyCamera.h"
#include <glm/ext.hpp>

using glm::mat4;

FlyCamera::FlyCamera( const float speed_f )
    : up_key_( KEY_W ), down_key_( KEY_S ),
    left_key_( KEY_A ), right_key_( KEY_D ),
    speed_f_( speed_f ), mouse_old_vec2_( 0 ) {}

FlyCamera::~FlyCamera() {}


void FlyCamera::Update() {
    // Conflicting keys should just cancel eachother out.
    if ( Input::GetKeyboardKey( up_key_ ) == INPUT_DOWN ) {
        position_vec3_.y += speed_f_;
    }
    if ( Input::GetKeyboardKey( down_key_ ) == INPUT_DOWN ) {
        position_vec3_.y -= speed_f_;
    }
    if ( Input::GetKeyboardKey( left_key_ ) == INPUT_DOWN ) {
        position_vec3_.x -= speed_f_;
    }
    if ( Input::GetKeyboardKey( right_key_ ) == INPUT_DOWN ) {
        position_vec3_.x += speed_f_;
    }

    /*vec2 mouse_new = Input::GetMousePosition();
    vec2 mouse_delta = mouse_new - mouse_old_vec2_;
    mat4 rotation = mat4( 1 );*/

    SetLookAt( position_vec3_, lookAt_vec3_, up_vec3_ );
}