#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() 
{
	// Linearally interpret between the textures
	vec4 texColor =  mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	if(texColor.a < 0.01)	// If the pixel is transparent enough, discard it
		discard;
	FragColor = texColor;
}
