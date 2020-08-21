#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
	
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform vec3 ourColor;
	
void main()
{
	FragColor = mix(vec4(ourColor, 1.0), mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.2), 0.0);
}