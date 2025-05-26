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
in vec3 FragPos;
in vec3 normal;

uniform vec3 theta_CameraViewingLocation;

uniform vec3 theta_AlbedoColor;
uniform float theta_MetallicScalar;
uniform float theta_RoughnessScalar;
uniform float theta_AmbientOcclusionScalar;

uniform sampler2D theta_Albedo;
uniform sampler2D theta_Normal;
uniform sampler2D theta_Metallic;
uniform sampler2D theta_Roughness;
uniform sampler2D theta_AmbientOcclusion;

uniform bool theta_UsesAlbedoMap;
uniform bool theta_UsesNormalMap;
uniform bool theta_UsesMetallicMap;
uniform bool theta_UsesRoughnessMap;
uniform bool theta_UsesAmbientOcclusionMap;

struct Light 
{
    vec3 Position;
    vec3 Color;
    float Intensity;
};

// uniform Light theta_Lights[90];
// uniform int theta_LightCount;

// Simply for testing purposes. Once this is working, Ill add a UBO object and implement multipe lights.
uniform Light theta_FirstLight;

const float PI = 3.141592653589;

// Weird hack that learnopengl.com shows.
vec3 GetNormalFromMap() {
    vec3 tangent_normal = texture(theta_Normal, texCoord).xyz * 2.0 - 1.0;
    
    // vec3 Q1 = dFdx(theta_WorldPosition);
    // vec3 Q2 = dFdy(theta_WorldPosition);
    // vec2 st1 = dFdx(texCoord);
    // vec2 st2 = dFdy(texCoord);

    // vec3 N = normalize(normal);
    // vec3 T = normalize(Q1*st2.t - Q2*st1.t);
    // vec3 B = -normalize(cross(N, T));
    // mat3 TBN = mat3(T, B, N);

    // Copied and pasted from ye old https://learnopengl.com/code_viewer_gh.php?code=src/6.pbr/1.2.lighting_textured/1.2.pbr.fs
    vec3 Q1  = dFdx(FragPos);
    vec3 Q2  = dFdy(FragPos);
    vec2 st1 = dFdx(texCoord);
    vec2 st2 = dFdy(texCoord);

    vec3 N   = normalize(normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangent_normal);
}


vec3 fresnelSchlick(float cosTheta, vec3 F0){
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2 * (a2-1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness){
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

void main() 
{
    // Query whether the shader is using map versions or scalar versions
    vec3 albedo = theta_AlbedoColor;
    float metallic = theta_MetallicScalar;
    float roughness = theta_RoughnessScalar;
    float ao = theta_AmbientOcclusionScalar;
    
    if(theta_UsesAlbedoMap) {
        albedo = pow(texture(theta_Albedo, texCoord).rgb, vec3(2.2));
    }
    if(theta_UsesMetallicMap){
        metallic = texture(theta_Metallic, texCoord).r;
    }
    if(theta_UsesRoughnessMap) {
        roughness = texture(theta_Roughness, texCoord).r;
    }
    if(theta_UsesAmbientOcclusionMap) {
        ao = texture(theta_AmbientOcclusion, texCoord).r;
    }


    vec3 N = normalize(normal);
    if(theta_UsesNormalMap) {
        N = GetNormalFromMap();
    }

    vec3 V = normalize(theta_CameraViewingLocation - FragPos);
    
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);
    
    vec3 Lo = vec3(0.0);
    // There is only one light for now.
    for(int i = 0; i < 1; ++i){
        // Per Light Radiance
        vec3 L = normalize(theta_FirstLight.Position - FragPos);
        vec3 H = normalize(V + L);

        float distance = length(theta_FirstLight.Position - FragPos);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = theta_FirstLight.Color * attenuation;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);
        float G = GeometrySmith(N, V, L, roughness);
        vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;

        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
        vec3 specular = numerator / denominator;

        // Add to Outgoing Radiance Lo
        float NdotL = max(dot(N, L), 0.0);
        Lo += ((kD * albedo / PI + specular) * radiance * NdotL) * theta_FirstLight.Intensity;
    }

    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + Lo;

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(color, 1.0);
}