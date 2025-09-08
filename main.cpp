#include <GL/glew.h>     
#include <GLFW/glfw3.h>  
#include <cmath>
#include "shader.h"
#include "stb_image.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window );

int main() {
    
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    
    GLFWwindow* window = glfwCreateWindow(1280, 720, "DeltaForce", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    
    glViewport(0, 0, 1280, 720);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };

unsigned int indices[]={
0,1,3,1,2,3
};
unsigned int VBO,VAO,EBO;
glGenVertexArrays(1,&VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);




glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);


glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 8  * sizeof(float), (void*)(3*sizeof(float)));
glEnableVertexAttribArray(1);

glVertexAttribPointer(2,2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
glEnableVertexAttribArray(2);

Shader myshader("./shaders/vertexshader.glsl","./shaders/fragmentshader.glsl");


int width, height, nrchannels;
stbi_set_flip_vertically_on_load(true);

unsigned char *data =stbi_load("container.jpg", &width, &height, &nrchannels,0);
int format;
if(nrchannels ==1 )
    format = GL_RED;
else if (nrchannels ==3)
    format = GL_RGB;
else if (nrchannels == 4)
    format =GL_RGBA;

unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
glTexImage2D(GL_TEXTURE_2D,0, format, width, height, 0 , format, GL_UNSIGNED_BYTE,data);
glGenerateMipmap(GL_TEXTURE_2D);
stbi_image_free(data);


while (!glfwWindowShouldClose(window)) {


        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
      
        myshader.use();
        glBindTexture(GL_TEXTURE_2D, texture);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);
      

      

        glfwSwapBuffers(window);
       
        glfwPollEvents();
    }
       glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1,&VBO);
        glDeleteBuffers(1, &EBO);
     

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    };

}
