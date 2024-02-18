#version 460 core
layout(location = 0) in vec3 aPos; // the position variable has attribute position 0
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;
layout(location = 3) in vec3 aTangent;

out VS_OUT {
    vec2 UV;
} vs_out;

void main()
{
    gl_Position = vec4(aPos, 1.0f);
    vs_out.UV = aUV;
}
