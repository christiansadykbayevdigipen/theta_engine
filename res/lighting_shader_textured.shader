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
in vec3 FragPos;
in vec3 normal;

uniform sampler2D theta_Albedo;

uniform vec3 theta_CameraViewingLocation;

struct Material {
    sampler2D diffuse;
    bool uses_specular_map;
    sampler2D specular;
    vec3 specular_vector;
    float shininess;
};

struct DI_Light {
    vec3 direction;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material theta_Material;

uniform DI_Light theta_SceneDirectionalLight;
uniform bool theta_SceneDirectionalLightExists;

vec3 _calculate_lighting(float ambient_strength, vec3 ambient_color, vec3 normal, vec3 light_position, vec3 light_color, vec3 viewing_location, float specular_highlight, float specular_strength) {
    // vec3 ambient = theta_AmbientStrength * theta_AmbientColor;
    // vec3 norm = normalize(normal);
    // vec3 light_dir = normalize(light_position - FragPos);

    // float diff = max(dot(norm, light_dir), 0.0);
    // vec3 diffuse = diff * light_color;

    // vec3 view_dir = normalize(viewing_location - FragPos);
    // vec3 reflect_dir = reflect(-light_dir, norm);

    // float spec = pow(max(dot(view_dir, reflect_dir), 0.0), specular_highlight);
    // vec3 specular = specular_strength * spec * light_color;

    // vec3 result = (ambient + diffuse + specular);

    // return result;
    return vec3(0.0, 0.0, 0.0);
}

vec3 calculate_di_light() {
    vec3 ambient = theta_SceneDirectionalLight.ambient * texture(theta_Material.diffuse, texCoord).rgb;

    vec3 norm = normalize(normal);
    vec3 light_dir = normalize(-theta_SceneDirectionalLight.direction);
    float diff = max(dot(norm, light_dir), 0.0);
    vec3 diffuse = theta_SceneDirectionalLight.diffuse * diff * texture(theta_Material.diffuse, texCoord).rgb;

    vec3 view_dir = normalize(theta_CameraViewingLocation - FragPos);
    vec3 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), theta_Material.shininess);

    vec3 specular = vec3(1.0, 1.0, 1.0);

    if(theta_Material.uses_specular_map)
        specular = theta_SceneDirectionalLight.specular * spec * texture(theta_Material.specular, texCoord).rgb;
    else
        specular = theta_SceneDirectionalLight.specular * spec * theta_Material.specular_vector;

    vec3 result = ambient + diffuse + specular;

    return result;
}

void main()
{
    if(theta_SceneDirectionalLightExists) {
        vec3 result = calculate_di_light();
        FragColor = vec4(result, 1.0);
        return;
    }

    FragColor = texture(theta_Material.diffuse, texCoord);
}