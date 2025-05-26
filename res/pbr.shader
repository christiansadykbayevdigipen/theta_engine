// https://learnopengl.com/PBR/Lighting

#version 330 core
layout (location = 0) in vec3 input_position;
layout (location = 1) in vec2 tex_coords;
layout (location = 2) in vec3 normals;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform float xTiling;
uniform float yTiling;

out vec2 texCoord;
out vec3 normal;
out vec3 FragPos;

void main()
{
    vec2 new_tex_coords = tex_coords;
    float x_tiling = xTiling;
    float y_tiling = yTiling;

    // If any of the tiling variables are set to 0, that means that they are either not set at all, or improperly set. Either way, we want to set them to one so that when we multiply tiling variables by the texture coordinate, it does't break.
    if(x_tiling == 0 || y_tiling == 0)
    {
        x_tiling = 1;
        y_tiling = 1;
    }

    new_tex_coords.x = new_tex_coords.x * x_tiling;
    new_tex_coords.y = new_tex_coords.y * y_tiling;

    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(input_position, 1.0);
    texCoord = new_tex_coords;
    FragPos = vec3(model * vec4(input_position, 1.0));
    normal = mat3(transpose(inverse(model))) * normals;
}

~NewShader
#version 330 core
out vec4 FragColor;
in vec2 texCoord;
uniform vec3 theta_WorldPosition;
in vec3 normal;

uniform vec3 theta_CameraViewingLocation;

uniform vec3 theta_AlbedoColor;
uniform float theta_MetallicScalar;
uniform float theta_RoughnessScalar;
uniform float theta_AmbientOcclusionScalar;

struct Light 
{
    vec3 Position;
    vec3 Color;
};

// uniform Light theta_Lights[90];
// uniform int theta_LightCount;

// Simply for testing purposes. Once this is working, Ill add a UBO object and implement multipe lights.
uniform Light theta_FirstLight;

void main() 
{
    vec3 N = normalize(normal);
    vec3 V = normalize(theta_CameraViewingLocation - theta_WorldPosition);
    FragColor = vec4(theta_AlbedoColor, 1.0);
}