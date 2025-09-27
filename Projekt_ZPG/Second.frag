#version 330 core
out vec4 FragColor;

in vec2 UV;

uniform float time;
uniform sampler2D texture1;

void main()
{

    float intensity = (sin(time) + 1.0) / 2.0;

    vec4 color = texture(texture1, UV);
    
    FragColor = vec4(UV.x, UV.y, color.g, 1.0);
}