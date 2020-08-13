#version 330 core

/*
// Interpolated values from the vertex shaders
//in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
*/


in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex;

void main(){

    // Output color = color of the texture at the specified UV
    //color = texture( myTextureSampler, UV ).rgb;
    //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    outColor = texture(tex, Texcoord) * vec4(Color, 1.0);
}
