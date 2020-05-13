//
//  main.cpp
//  OpenGLExercise01
//
//  Created by ELVA on 2020-05-12.
//  Copyright © 2020 ELVA. All rights reserved.
//

#include <iostream>

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>
const GLint WIDTH=800, HEIGHT=600;

const char* vertexShaderSource=
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource=
"#version 330 core    \n"
"out vec4 FragColor;       \n"
"void main()   {\n"
"     FragColor=vec4(1.0f,0.5f,0.2f,1.0f);}   \n";

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
    glViewport(0,0,800,600);
    
    
    
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    //create one vertex array, VAO, and return the Pos of the array into the VAO;
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    
    //create one VBO
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    //create a vertex shader
    unsigned int vertexShader;
    vertexShader=glCreateShader(GL_VERTEX_SHADER);
    //compile
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    glCompileShader(vertexShader);
    
    
    //create a fragment shader
    unsigned int fragmentShader;
    fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    //compile
    glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);
    
    //create a shader program
    unsigned int shaderProgram;
    shaderProgram=glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    
    // if the user does not close the window, then loop
    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);
        //render to change the background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//RGB LR 0-1
        glClear(GL_COLOR_BUFFER_BIT);
        //draw a triangle, start from point 0, 3 points
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        
        
        glfwPollEvents();//user input
        glfwSwapBuffers(window);
        
    }
    //terminate the function
    glfwTerminate();
    return 0;
}
