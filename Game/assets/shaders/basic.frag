#version 460 core
out vec4 FragColor;  

uniform sampler2D tex;
  
in VS_OUT {
  vec2 UV;
} fs_in;

layout(std140, binding = 3) uniform testBlock {
  vec4 color;
  vec4 position;
} test;

void main()
{
    //FragColor = vec4(texture(tex, fs_in.UV)); 
    FragColor = test.position; 
    
}
