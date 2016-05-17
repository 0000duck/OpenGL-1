//FRAGMENT SHADER: set red color to each fragment

#version 330
in vec3 worldSpacePos;
in vec3 color;
in vec2 texCoord;
in vec3 normal;

out vec4 fragmentColor;

struct sLight
{
	vec3 lightColor;
	float intensityAmbient;
	float intensityDiffuse;
	vec3 direction;
};

uniform sampler2D gSampler;		//the application puts in this variable the value of the texture unit to let the shader access it
uniform sLight light;
uniform vec3 eyeWorldSpace;
uniform float specularIntensity;
uniform float specularPower;

void main()
{
	vec4 ambientColor  = vec4(0, 0, 0, 0);
	vec4 diffuseColor  = vec4(0, 0, 0, 0);
	vec4 specularColor = vec4(0, 0, 0, 0);

	vec2 flipped_texcoord = vec2(texCoord.x,1.0f - texCoord.y);
	vec4 fragmentTexture = texture2D(gSampler, flipped_texcoord.st);

	ambientColor = vec4(light.lightColor, 1.0f) * light.intensityAmbient;

	float diffuseFactor = dot(normalize(normal), -light.direction);	//cosine between the surface normal and the light direction
	if(diffuseFactor > 0) {
		diffuseColor = vec4(light.lightColor, 1.0f)  * light.intensityDiffuse * diffuseFactor;

		//subtracting the vertex for the eye position (both in world space) we get the sight vector
		vec3 sightV = normalize(eyeWorldSpace - worldSpacePos);
		//to calculate the reflection vector we can use the "reflect" builtin function or make the calculations
		vec3 reflectV = normalize(reflect(light.direction, normal));
		float specularFactor = dot(sightV, reflectV);
		if(specularFactor > 0) {
			specularFactor = pow(specularFactor, specularPower);
			specularColor = vec4(light.lightColor, 1.0f) * specularIntensity * specularFactor;
		}
	} 

	fragmentColor = fragmentTexture * (ambientColor + diffuseColor + specularColor);
}