#version 330 core

layout (location = 0) in vec3 aPos;     // position attribute
layout (location = 1) in vec3 aColor;   // color attribute
layout (location = 2) in vec2 atext;

out vec3 ourColor;  // output color to fragment shader
out vec2 ourText;

void main()
{
    gl_Position = vec4(aPos, 1.0); // correct spelling & capitalization
    ourColor = aColor;             // pass color to fragment shader
    ourText = atext;
}
