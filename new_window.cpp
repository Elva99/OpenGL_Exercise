//
//  main.cpp
//  OpenGLExercise01
//
//  Created by ELVA on 2020-05-12.
//  Copyright © 2020 ELVA. All rights reserved.
//  This program create a new window with red background using c++

#include <iostream>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>
const GLint WIDTH=800, HEIGHT=600;

//if press escape, then exit
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,true);
    }
}








int main( ) {
    glfwInit();
    //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    //specail for MAC
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    
    GLFWwindow *window=glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);
    int screenwidth,screenheight;
    glfwGetFramebufferSize(window, &screenwidth, &screenheight);
    
    //fail to create a GLFW window
    if (nullptr==window)
    {
        std::cout<<"Fail to create GLFW window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    //make the window current
    glfwMakeContextCurrent(window);
    
    //use the glew
    glewExperimental=GL_TRUE;
    //if the initialization is successful, then return GLEW_OK
    if (GLEW_OK!=glewInit())
    {
        std::cout<<"Failed to initialize GLEW"<<std::endl;
        return -1;
    }
    glViewport(0,0,screenwidth,screenheight);
    // if the user does not close the window, then loop
    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);
        //render to change the background color
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);//RGB LR 0-1
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwPollEvents();//user input
        glfwSwapBuffers(window);
        
    }
    //terminate the function
    glfwTerminate();
    return 0;
}
