#version 330 core
in vec2 TexCoord;
in vec3 lightingColor;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
	//obj tex coordinate color
	vec3 objColor=vec3(texture(ourTexture, TexCoord));

    color = vec4(lightingColor*objColor, 1.0f);
}