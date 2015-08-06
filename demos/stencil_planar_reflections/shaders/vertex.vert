#version 330

layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float tintFactor;

out vec3 col;
out float finalTint;


void main(){
	vec4 worldPos = model*vec4(position, 1.0);
    gl_Position = projection*view*model*vec4(position, 1.0);
    col = normal;
	
	finalTint = min(1.0, tintFactor+(worldPos.y+1)*0.3);
}