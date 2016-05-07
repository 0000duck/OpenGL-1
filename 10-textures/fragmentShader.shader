//FRAGMENT SHADER: set red color to each fragment

#version 330
in vec3 color;
in vec2 texCoord;
out vec4 fragmentColor;
vec4 fragmentTexture;

uniform sampler2D gSampler;		//the application puts in this variable the value of the texture unit to let the shader access it

void main()
{
	vec2 flipped_texcoord = vec2(texCoord.x,texCoord.y);
	fragmentTexture = texture2D(gSampler, flipped_texcoord.st);
	fragmentColor = fragmentTexture * vec4((color * 0.5), 0.0);
}