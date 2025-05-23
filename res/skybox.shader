#version 330 core
layout (location = 0) in vec3 input_position;

uniform mat4 projection;
uniform mat4 view;

out vec3 texCoord;

void main()
{
    vec4 pos = projection * view * vec4(input_position, 1.0);
    gl_Position = pos;
    texCoord = input_position;
}

~NewShader

#version 330 core
out vec4 FragColor;
in vec3 texCoord;

uniform samplerCube theta_Skybox;

void main()
{
    //FragColor = mix(texture(theta_Albedo, texCoord), vec4(0.5, 0.5, 1.0, 1.0), 0.5);
    FragColor = texture(theta_Skybox, texCoord);
    //FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}