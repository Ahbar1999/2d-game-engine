#version 330 core

layout(location = 0) in  vec4 vertex; // <vec2 position, vec2 TexCoords>
// layout(location = 1)
out vec2 TexCoords;
out vec4 ParticleColor;

uniform mat4 projection;
uniform mat4 view;
uniform vec2 offset;
uniform vec4 color;

void main()
{
	float scale = 10.0f;
	TexCoords = vertex.zw;
	ParticleColor = color;
	// why not use the model matrix to translate and scale coordinates ?
	// because we are directly supplying the final coords in terms offset 
	gl_Position = projection * view* vec4((vertex.xy* scale) + offset, 0.0, 1.0);
}