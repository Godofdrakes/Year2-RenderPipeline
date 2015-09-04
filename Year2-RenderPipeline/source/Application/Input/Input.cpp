#include "Input.h"
#include <GLFW/glfw3.h>

GLFWwindow* Input::window_ = nullptr;
map< const InputKeyboard, InputState> Input::key_map_;
map< const InputMouse, InputState> Input::mouse_map_;
vec2 Input::mousePos_vec2_ = vec2( 0 );


Input::Input() {}

Input::~Input() {}


InputState Input::GetKeyboardKey( InputKeyboard key ) {
    InputState state = INPUT_UP;
    if ( window_ != nullptr ) {
        if ( glfwGetKey( window_, key ) == GLFW_PRESS ) {
            if ( key_map_[key] == INPUT_UP ) { key_map_[key] = state = INPUT_PRESS; }
            if ( key_map_[key] == INPUT_PRESS ) { key_map_[key] = state = INPUT_DOWN; }
            if ( key_map_[key] == INPUT_DOWN ) { /*key_map_[key] =*/ state = INPUT_DOWN; }
            if ( key_map_[key] == INPUT_RELEASE ) { key_map_[key] = state = INPUT_PRESS; }
        } else {
            if ( key_map_[key] == INPUT_UP ) { /*key_map_[key] =*/ state = INPUT_UP; }
            if ( key_map_[key] == INPUT_PRESS ) { key_map_[key] = state = INPUT_RELEASE; }
            if ( key_map_[key] == INPUT_DOWN ) { key_map_[key] = state = INPUT_RELEASE; }
            if ( key_map_[key] == INPUT_RELEASE ) { key_map_[key] = state = INPUT_UP; }
        }
    }
    return state;
}

InputState Input::GetMouseButton( InputMouse button ) {
    InputState state = INPUT_UP;
    if ( window_ != nullptr ) {
        if ( glfwGetMouseButton( window_, button ) == GLFW_PRESS ) {
            if ( mouse_map_[button] == INPUT_UP ) { mouse_map_[button] = state = INPUT_PRESS; }
            if ( mouse_map_[button] == INPUT_PRESS ) { mouse_map_[button] = state = INPUT_DOWN; }
            if ( mouse_map_[button] == INPUT_DOWN ) { /*mouse_map_[button] =*/ state = INPUT_DOWN; }
            if ( mouse_map_[button] == INPUT_RELEASE ) { mouse_map_[button] = state = INPUT_PRESS; }
        } else {
            if ( mouse_map_[button] == INPUT_UP ) { /*mouse_map_[button] =*/ state = INPUT_UP; }
            if ( mouse_map_[button] == INPUT_PRESS ) { mouse_map_[button] = state = INPUT_RELEASE; }
            if ( mouse_map_[button] == INPUT_DOWN ) { mouse_map_[button] = state = INPUT_RELEASE; }
            if ( mouse_map_[button] == INPUT_RELEASE ) { mouse_map_[button] = state = INPUT_UP; }
        }
    }
    return state;
}

vec2 Input::GetMousePosition() {
    if( window_ != nullptr ) {
        double x, y;
        glfwGetCursorPos( window_, &x, &y );
        mousePos_vec2_ = vec2( x, y );
    }
    return mousePos_vec2_;
}
