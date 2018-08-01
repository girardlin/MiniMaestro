#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;


void main()
{
    FragColor = texture(texture_diffuse1, TexCoord);
	//FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
} 