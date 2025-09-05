#version 330 core

layout (location =0 ) in vec3 apos;
layout (location =1) in vec3 acolor;
 out vec3 ourcolor;
void main(){
    glposition = vec4 (apos, 1.0);
    ourcolor = acolor;
}