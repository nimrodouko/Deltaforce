#version 330 core

in vec3 ourColor;        // input from vertex shader
out vec4 FragColor;      // final output color

void main()
{
    FragColor = vec4(ourColor, 1.0); // use interpolated color
}
