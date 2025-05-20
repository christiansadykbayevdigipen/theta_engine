#version 330 core
layout (location = 0) in vec3 input_position;
layout (location = 1) in vec2 tex_coords;
layout (location = 2) in vec3 normals;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 texCoord;
out vec3 normal;
out vec3 FragPos;

void main()
{
    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(input_position, 1.0);
    texCoord = tex_coords;
    FragPos = vec3(model * vec4(input_position, 1.0));
    normal = mat3(transpose(inverse(model))) * normals;
}

~NewShader

#version 330 core
out vec4 FragColor;
in vec2 texCoord;
in vec3 FragPos;
in vec3 normal;

uniform sampler2D theta_Albedo;

uniform vec3 theta_SceneLightPos;
uniform vec3 theta_SceneLightColor;
uniform float theta_AmbientStrength;
uniform vec3 theta_AmbientColor;
uniform vec3 theta_CameraViewingLocation;

uniform float theta_MaterialSpecularStrength;
uniform float theta_MaterialSpecularHighlight;

void main()
{
    // Ambient Lighting Here
    vec3 ambient = theta_AmbientStrength * theta_AmbientColor;

    // Diffuse Lighting
    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(theta_SceneLightPos - FragPos);

    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = diff * theta_SceneLightColor;

    // Calculate viewing stuff
    vec3 viewDir = normalize(theta_CameraViewingLocation - FragPos);
    vec3 reflectDir = reflect(-light_dir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), theta_MaterialSpecularHighlight);
    vec3 specular = theta_MaterialSpecularStrength * spec * theta_SceneLightColor;

    vec3 result = (ambient + diffuse + specular);

    //FragColor = mix(texture(theta_Albedo, texCoord), vec4(0.5, 0.5, 1.0, 1.0), 0.5);
    FragColor = vec4(result, 1.0) * texture(theta_Albedo, texCoord);
}