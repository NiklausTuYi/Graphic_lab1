#version 330 core
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform sampler2D ourTexture;

uniform int numberLights;
uniform vec3 lightPos[10];
uniform vec3 lightColor[10];
uniform vec3 viewPos;
uniform float shininess;

void main()
{
	//obj tex coordinate color
	vec3 objColor=vec3(texture(ourTexture, TexCoord));
	float ambientStrength=0.2f;
	vec3 ambient = ambientStrength * vec3(1.0,1.0,1.0);

	float specularStrength = shininess;
	vec3 result = vec3(0.0f,0.0f,0.0f);
	for(int i=0; i<numberLights; i++){
		//diffuse term
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(lightPos[i] - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColor[i];

		//specular term
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength * spec * lightColor[i];
		result+=(diffuse+specular);
	}

	result = (ambient+result) * objColor;
    color = vec4(result, 1.0f);
}