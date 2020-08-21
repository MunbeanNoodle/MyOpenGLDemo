#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
	
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

uniform vec3 objectColor;
uniform vec3 lightColor;
	
void main()
{
	FragColor = vec4(lightColor * objectColor, 1.0);
}