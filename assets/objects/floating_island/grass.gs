#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT
{
    vec3 v_Normal;
    vec2 v_TexCoord;
    vec4 v_FragPos;
} gs_in[];

out GS_OUT
{
    vec3 v_Normal;
    vec2 v_TexCoord;
    vec4 v_FragPos;
} gs_out;

void main() 
{  
	// Ground
	gl_Position = gl_in[0].gl_Position;
	gs_out.v_FragPos = gs_in[0].v_FragPos;
	gs_out.v_Normal = gs_in[0].v_Normal;
	gs_out.v_TexCoord = gs_in[0].v_TexCoord;
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	gs_out.v_FragPos = gs_in[1].v_FragPos;
	gs_out.v_Normal = gs_in[1].v_Normal;
	gs_out.v_TexCoord = gs_in[1].v_TexCoord;
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	gs_out.v_FragPos = gs_in[2].v_FragPos;
	gs_out.v_Normal = gs_in[2].v_Normal;
	gs_out.v_TexCoord = gs_in[2].v_TexCoord;
	EmitVertex();
}
