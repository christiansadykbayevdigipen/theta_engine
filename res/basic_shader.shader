#version 330 core
layout (location = 0) in vec3 input_position;

void main()
{
    gl_Position = vec4(input_position, 1.0);
}

~NewShader

#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.5, 0.25, 1.0);
}