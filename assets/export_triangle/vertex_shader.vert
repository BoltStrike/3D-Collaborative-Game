#version 330 core
layout (location = 0) in vec4 position;
uniform vec4 offset;
uniform mat4 perspectiveMatrix;

void main()
{
	vec4 cameraPos = position + vec4(offset.x, offset.y, offset.z, 0.0);
	gl_Position = perspectiveMatrix * cameraPos;
	//gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
