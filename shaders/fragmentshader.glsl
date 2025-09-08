#version 330 core

in vec3 ourColor;        // input from vertex shader
out vec4 FragColor;      // final output color
in vec2 ourText;

uniform sampler2D texture1;


void main()
{

    FragColor = texture(texture1, ourText);
}
