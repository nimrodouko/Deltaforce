#include <GL/glew.h>     
#include <GLFW/glfw3.h>  

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window );

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    " out vec4 fragcolor;\n"
    "void main()\n"
    "{\n"
    "   fragcolor = vec4(1.0f,0.3f,0.6f,1.0f);\n"
    "}\0";
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

    
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    float vertices[] ={
        0.5f, 0.0f ,0.0f,
        -0.5f, 0.0f,0.0f,
        0.0f, 0.5f, 0.0f
};
unsigned int VBO,VAO;

glGenBuffers(1, &VBO);
glGenVertexArrays(1,&VAO);
glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

unsigned int vertexshader;
vertexshader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexshader,1 ,&vertexShaderSource, NULL);
glCompileShader(vertexshader);

unsigned int fragmentshader;
fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentshader,1 , &fragmentShaderSource, NULL);
glCompileShader(fragmentshader);

unsigned int shaderprogram;
shaderprogram = glCreateProgram();
glAttachShader(shaderprogram, vertexshader);
glAttachShader(shaderprogram, fragmentshader);
glLinkProgram(shaderprogram);

int success;
char infolog[512];
glGetProgramiv(shaderprogram,GL_LINK_STATUS, &success);
if (!success){
    glGetProgramInfoLog(shaderprogram , 512, NULL, infolog);
    std::cout<<infolog<<std::endl;
}


glDeleteShader(vertexshader);
glDeleteShader(fragmentshader);



    
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderprogram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0,3);

      

        glfwSwapBuffers(window);
       
        glfwPollEvents();
    }
       glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1,&VBO);
        glDeleteProgram(shaderprogram);

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
