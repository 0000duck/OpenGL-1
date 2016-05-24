//FRAGMENT SHADER: set red color to each fragment

#version 330
in vec3 worldSpacePos;
in vec3 color;
in vec2 texCoord;
in vec3 normal;

out vec4 fragmentColor;

layout(std140)
uniform material {
	vec4 lightColorAmbient;
	vec4 lightColorDiffuse;
	vec3 direction;
	vec4 lightspecularColor;
	float specularPower;
}Material;

uniform sampler2D gSampler;		//the application puts in this variable the value of the texture unit to let the shader access it
uniform vec3 eyeWorldSpace;

void main()
{
	vec4 ambientColor  = vec4(0, 0, 0, 0);
	vec4 diffuseColor  = vec4(0, 0, 0, 0);
	vec4 specularColor = vec4(0, 0, 0, 0);

	vec2 flipped_texcoord = vec2(texCoord.x,1.0f - texCoord.y);
	vec4 fragmentTexture = texture2D(gSampler, flipped_texcoord.st);

	ambientColor = Material.lightColorAmbient;
	//ambientColor = Material.lightColorDiffuse;

	float diffuseFactor = dot(normalize(normal), -Material.direction);	//cosine between the surface normal and the light direction
	if(diffuseFactor > 0) {
		diffuseColor = Material.lightColorDiffuse * diffuseFactor;

		//subtracting the vertex for the eye position (both in world space) we get the sight vector
		vec3 sightV = normalize(eyeWorldSpace - worldSpacePos);
		//to calculate the reflection vector we can use the "reflect" builtin function or make the calculations
		vec3 reflectV = normalize(reflect(Material.direction, normal));
		float specularFactor = dot(sightV, reflectV);
		specularFactor = pow(specularFactor, Material.specularPower);
		if(specularFactor > 0) {
			specularColor = Material.lightspecularColor * specularFactor;
		}
	} 

	fragmentColor = fragmentTexture *(ambientColor + diffuseColor + specularColor);
}