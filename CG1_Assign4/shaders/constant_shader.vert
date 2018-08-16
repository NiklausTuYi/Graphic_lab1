#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out vec3 lightingColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 cameraMatrix;

uniform int numberOfLights;
uniform vec3 lightPos[10];
uniform vec3 lightColor[10];
uniform vec3 viewPos;
uniform float shininess;

void main()
{
	gl_Position =cameraMatrix* model * vec4(position, 1.0f);
	TexCoord = vec2(texCoord.x, 1.0-texCoord.y);
	vec3 vertPos = vec3(model * vec4(position, 1.0f));

	//calculate ambient lighting for this vertex
	float ambientStrength=0.2f;
	vec3 result = ambientStrength * vec3(1.0,1.0,1.0);

	float specularStrength = shininess;
	
	vec3 Normal = mat3(transpose(inverse(model))) * normal;

	for(int i=0; i<numberOfLights; i++){
		//diffuse term
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(lightPos[i] - vertPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColor[i];

		//specular term
		vec3 viewDir = normalize(viewPos - vertPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength * spec * lightColor[i];
		result+=(diffuse+specular);
	}
	
	lightingColor = result;
}