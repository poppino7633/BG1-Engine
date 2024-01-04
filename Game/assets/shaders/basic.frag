#version 460 core
out vec4 FragColor;  

uniform sampler2D tex;
  
in VS_OUT {
  vec2 UV;
} fs_in;

void main()
{
    FragColor = vec4(texture(tex, fs_in.UV));
}
