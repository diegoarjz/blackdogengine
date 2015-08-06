#version 330

in float finalTint;
in vec3 col;
out vec4 outColor;

void main(){
    outColor = vec4(col*finalTint, 1.0);
}
