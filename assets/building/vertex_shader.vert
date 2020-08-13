#version 330 core
layout (location = 0) in vec4 position;
//layout (location = 1) in vec2 vertexUV;

//out vec2 UV;

in vec2 texcoord;

out vec3 Color;
out vec2 Texcoord;

uniform vec4 offset;
uniform mat4 perspectiveMatrix;

void main()
{
	Texcoord = texcoord;
	vec4 cameraPos = position + vec4(offset.x, offset.y, offset.z, 0.0);
	gl_Position = perspectiveMatrix * cameraPos;

	

	// UV of the vertex. No special space for this one.
    //UV = vertexUV;
}
