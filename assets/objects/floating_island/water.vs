#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aOffset;

out VS_OUT
{
    vec3 v_Normal;
    vec2 v_TexCoord;
    vec4 v_FragPos;
    float time;
} vs_out;

uniform float time;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos+aOffset, 1.0f);
	vs_out.v_FragPos = model * vec4(aPos, 1.0);
	vs_out.v_TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	vs_out.v_Normal = aNormal;
	vs_out.time = time;
}
