#include "Application.h"

Application::Application() : Application( "" ) {}

Application::Application( string set_name ) : Application( set_name, 1280, 720 ) {}

Application::Application( string set_name, int set_width, int set_height ) : TICK_PER_SEC_D_( 1.0 / 60.0 ) {
    name_string_ = set_name;
    width_i_ = set_width;
    height_i_ = set_height;
    window_glfw_ = nullptr;

    view_mat4_ = glm::lookAt( vec3( 10, 10, 10 ), vec3( 0 ), vec3( 0, 1, 0 ) );
    projection_mat4_ = glm::perspective( glm::pi<float>() * 0.25f, 16 / 9.f, 0.1f, 1000.f );

    time_current_d_ = 0.0;
    time_elapsed_d_ = 0.0;
    time_lag_d_ = 0.0;
    time_previous_d_ = 0.0;

    for ( int n = 0; n < celestial_body.size(); ++n ) {
        celestial_body[n] = new CelestialBody( 15, CelestialBody_Type::SPHERE );
    }
}

Application::~Application() {
    for ( int n = 0; n < celestial_body.size(); ++n ) {
        delete( celestial_body[n] );
    }
}

ApplicationFail Application::Init() {
    if ( glfwInit() == false ) { return ApplicationFail::GLFW_INIT; }

    window_glfw_ = glfwCreateWindow( 1280, 720, name_string_.c_str(), nullptr, nullptr );
    if ( window_glfw_ == nullptr ) {
        glfwTerminate();
        return GLFW_CREATE_WINDOW;
    }
    glfwMakeContextCurrent( window_glfw_ );

    if ( ogl_LoadFunctions() == ogl_LOAD_FAILED ) {
        glfwDestroyWindow( window_glfw_ );
        glfwTerminate();
        return OGL_LOAD_FUNCTIONS;
    }

    const int OGL_MAJOR = ogl_GetMajorVersion();
    const int OGL_MINOR = ogl_GetMinorVersion();
    printf( "OpenGL Version: %i.%i\n", OGL_MAJOR, OGL_MINOR );

    glClearColor( 0.25f, 0.25f, 0.25f, 1.0f );
    glEnable( GL_DEPTH_TEST );

    time_previous_d_ = glfwGetTime();

    Gizmos::create();

    celestial_body[0]->SetPosition( 0.f, 0.f, 0.f );
    celestial_body[0]->SetScale( 1.5f, 1.5f, 1.5f );
    celestial_body[0]->SetColor( 1.f, 1.f, 0.f, 1.f );

    celestial_body[1]->SetPosition( 5.f, 0.f, 0.f );
    celestial_body[1]->SetScale( 0.5f, 0.5f, 0.5f );
    celestial_body[1]->SetColor( 0.0f, 0.25f, 0.5f, 1.f );

    return ApplicationFail::NONE;
}

void Application::Shutdown() {
    Gizmos::destroy();
    glfwDestroyWindow( window_glfw_ );
    glfwTerminate();
}

bool Application::Update() {
    if ( glfwWindowShouldClose( window_glfw_ ) ||
         glfwGetKey( window_glfw_, GLFW_KEY_ESCAPE ) == GLFW_PRESS ) { return false; }
    glfwSwapBuffers( window_glfw_ );
    glfwPollEvents();
    time_current_d_ = glfwGetTime();
    time_elapsed_d_ = time_current_d_ - time_previous_d_;
    time_previous_d_ = time_current_d_;
    time_lag_d_ += time_elapsed_d_;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    Gizmos::clear();
    Gizmos::addTransform( mat4( 1 ) );
    return true;
}

void Application::Tick() {
    while ( time_lag_d_ >= TICK_PER_SEC_D_ ) {
        for ( int n = 0; n < celestial_body.size(); ++n ) {
            celestial_body[n]->SetGlobalRotation( time_current_d_ * ( n + 1 ) * ( n + 1 ), vec3( 0.f, 1.f, 0.f ) );
            celestial_body[n]->Update();
        }

        time_lag_d_ -= TICK_PER_SEC_D_;
    }
}

void Application::Draw() {
    for ( int n = 0; n < 21; ++n ) {
        Gizmos::addLine( vec3( -10 + n, 0, 10 ),
                         vec3( -10 + n, 0, -10 ),
                         n == 10 ? vec4( 1, 1, 1, 1 ) : vec4( 0, 0, 0, 1 ) );
        Gizmos::addLine( vec3( 10, 0, -10 + n ),
                         vec3( -10, 0, -10 + n ),
                         n == 10 ? vec4( 1, 1, 1, 1 ) : vec4( 0, 0, 0, 1 ) );
    }
    for ( int n = 0; n < celestial_body.size(); ++n ) { celestial_body[n]->Draw(); }
    Gizmos::draw( projection_mat4_ * view_mat4_ );
}