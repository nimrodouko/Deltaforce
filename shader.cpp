 #include "shader.h"

 
 Shader::Shader(const char * vertexpath, const char *fragmentpath){
    std::string vertexcode;
    std::string fragmentcode;
    std::ifstream vshaderfile;
    std::ifstream fshaderfile;

    vshaderfile.exceptions(std::ifstream::failbit|std::ifstream::badbit);
    fshaderfile.exceptions(std::ifstream::failbit|std::ifstream::badbit);
    std::cout<<vertexpath<<std::endl;
    std::cout<<fragmentpath<<std::endl;
    try
    {
        vshaderfile.open(vertexpath);
        fshaderfile.open(fragmentpath);
        std::stringstream vshaderstream, fshaderstream;
        vshaderstream << vshaderfile.rdbuf();
        fshaderstream<<fshaderfile.rdbuf();
        vshaderfile.close();
        fshaderfile.close();
        vertexcode = vshaderstream.str();
        fragmentcode = fshaderstream.str();

    }
    catch(std::ifstream::failure e)
    {
        std::cout << "error in reading shader file" << '\n';

    }
    const char * vshadercode = vertexcode.c_str();
    const char * fshadercode = fragmentcode.c_str();
    
    unsigned int vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource (vertex,1,&vshadercode,NULL);
    glCompileShader(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment,1 , &fshadercode, NULL);
    glCompileShader(fragment);

   

    
    shaderprogram= glCreateProgram();
    glAttachShader(shaderprogram, vertex);
    glAttachShader(shaderprogram, fragment);
    glLinkProgram(shaderprogram);
     int success;
    char infolog[512];
    glGetProgramiv(shaderprogram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderprogram, 512,NULL, infolog);
        std::cout<<"Error in the compiling the files::"<<infolog <<std::endl;
    };
    std::cout<<"Imefika hapa"<<std::endl;



    glDeleteShader(vertex);

    glDeleteShader(fragment);


};
void Shader::use(){
    glUseProgram(shaderprogram);
};
void Shader::setbool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderprogram, name.c_str()), (int)value);

};
void Shader::setint(const std::string &name, int value)const
{
    glUniform1i(glGetUniformLocation(shaderprogram, name.c_str()),value);
};
void Shader::setfloat(const std::string &name, float value)const
{
    glUniform1f(glGetUniformLocation(shaderprogram , name.c_str()), value);
}

