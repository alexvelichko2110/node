
#include <iostream>
#include <cmath>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <vector>
#include <iostream>


//#include "shader.h"
//#include "buffer.h"
//#include "texture.h"
// #include "font.h"
//#include "node.h"
//#include "camera.h"
//#include "render.h"

//#include "resource_manager.h"

#include <shade/render.h>


// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;


bool keys[1024];

bool mouse_press = false;

float lastX = 400;
float lastY = 300;

bool firstMouse = true;

Node node;
Node node_cam;

Node node1;

float PITCH = WIDTH*0.5;
float YAW = HEIGHT* 0.5;


void error ( int error, const char * description )
{
    fputs ( description, stderr );
}


void key_callback ( GLFWwindow * window, int key, int scancode, int action, int mods )
{
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        glfwSetWindowShouldClose ( window, GL_TRUE );
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to leTCHft

    lastX = xpos;
    lastY = ypos;

    // std::cout << "mouse xoffset " << xoffset << " yoffset " << yoffset << std::endl;

    if (mouse_press) {

        PITCH += xoffset;
        YAW += yoffset;     

        node.set_pitch (PITCH);
        node.set_yaw (YAW);
    }
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        mouse_press = true;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        mouse_press = false;
    }
}



void load_resources_all()
{
    rm()->load_shader("poly", "./resources/simple_one_mat.vs", "./resources/poly.fs");
    rm()->load_shader("line1", "./resources/simple_one_mat.vs", "./resources/lines.fs");
    
    rm()->load_texture("tex1", "./resources/tex1.jpeg");
}


int main ()
{

    // Init GLFW
    glfwInit();

    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);


    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;

    // Initialize GLEW to setup the OpenGL Function pointers
    glewInit();


    Camera camera;

    camera.set_width(WIDTH);
    camera.set_height(HEIGHT);

    // camera.set_width(1024);
    // camera.set_height(768);


    // camera.set_distance_for_near_plane(0.5);
    // camera.set_distance_for_far_plane(10000);

    // camera.build_proj_ortho();

    camera.set_distance_for_near_plane(0.1);
    camera.set_distance_for_far_plane(10000);

    camera.build_proj_perspective();


    node.set_yaw(30.0);
    node.set_pitch(45.0);

    node.set_position(glm::vec3(-40.0, 0.0, 0.0));


    node1.set_yaw(30.0);
    node1.set_pitch(45.0);

    node1.set_position(glm::vec3(40.0, 40.0, 0.0));


    camera.set_node(&node_cam);


    Render* render = new Render();
    //render->allocate_all();

    render->set_framebuffer_size(WIDTH, HEIGHT);
    render->init();


    load_resources_all();




    Buffer* buffer_lines = new Buffer(GL_LINES);
    buffer_lines->make_buffers();

    Buffer* buffer_rects = new Buffer(GL_TRIANGLES);
    buffer_rects->make_buffers();


    while ( glfwWindowShouldClose ( window ) != true)
    {

        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();


        buffer_rects->reset();

        float rr = 50;

        buffer_rects->add_point( glm::vec3(rr, 0.0, -rr), glm::vec2(1.0f, 0.0f) );
        buffer_rects->add_point( glm::vec3(-rr, 0.0, -rr), glm::vec2(0.0f, 0.0f));
        buffer_rects->add_point( glm::vec3(-rr, 0.0, rr), glm::vec2(0.0f, 1.0f) );
        buffer_rects->add_point( glm::vec3(rr, 0.0, rr), glm::vec2(1.0f, 1.0f) );


        // buffer_rects->add_point( glm::vec3(50.0f, -50.0f, 0.0f), glm::vec2(1.0f, 0.0f) );
        // buffer_rects->add_point( glm::vec3(-50.0f, -50.0f, 0.0f), glm::vec2(0.0f, 0.0f));
        // buffer_rects->add_point( glm::vec3(-50.0f, 50.0f, 0.0f), glm::vec2(0.0f, 1.0f) );
        // buffer_rects->add_point( glm::vec3(50.0f, 50.0f, 0.0f), glm::vec2(1.0f, 1.0f) );


        buffer_rects->make_rect();

        buffer_rects->load_to_gpu();



        buffer_lines->reset();

        buffer_lines->add_point(glm::vec3(0.0, 0.0, 0.0));
        buffer_lines->add_point(glm::vec3(0.0, 100.0, 0.0));

        buffer_lines->add_point(glm::vec3(0.0, 0.0, 0.0));
        buffer_lines->add_point(glm::vec3(100.0, 0.0, 0.0));

        buffer_lines->add_point(glm::vec3(0.0, 0.0, 0.0));
        buffer_lines->add_point(glm::vec3(0.0, 0.0, 100.0));


        buffer_lines->make_line();

        buffer_lines->load_to_gpu();



        glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

        glm::vec3 pos = glm::vec3(0.0, 300.0, 100.0);
        glm::vec3 target = glm::vec3(0.0, 0.0, 0.0);

        node_cam.look_at(pos, target, up);
        node_cam.build_this();


        node.euler();
        node.build_this();


        node1.euler();
        node1.build_this();


        // draw all objects

        render->set_viewport(0, 0, WIDTH, HEIGHT);
        render->clear();

        Texture* tex = rm()->textures("default").get();
        render->set_texture(0, tex);

        // draw rect field
        {
            Shader* shader = rm()->shaders("poly").get();


            render->draw_buffer_u(buffer_rects, &node, &camera, shader, true);
        }

        // draw line
        {

            Shader* shader = rm()->shaders("line1").get();

            render->draw_buffer_u(buffer_lines, &node, &camera, shader, false);
        }



        {
            Shader* shader = rm()->shaders("poly").get();

            render->draw_buffer_u(buffer_rects, &node1, &camera, shader, true);
        }

        // draw line
        {

            Shader* shader = rm()->shaders("line1").get();

            render->draw_buffer_u(buffer_lines, &node1, &camera, shader, false);
        }

        // Swap the screen buffers
        glfwSwapBuffers(window);

    }

    delete buffer_lines;
    delete buffer_rects;


    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
