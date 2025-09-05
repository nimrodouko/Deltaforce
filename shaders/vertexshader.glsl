#version 330 core

layout (location = 0) in vec3 aPos;     // position attribute
layout (location = 1) in vec3 aColor;   // color attribute

out vec3 ourColor;  // output color to fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0); // correct spelling & capitalization
    ourColor = aColor;             // pass color to fragment shader
}
