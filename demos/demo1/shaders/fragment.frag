#version 330

in vec3 col;
out vec4 outColor;

void main(){
//    outColor = vec4(1.0,0.0,0.0, 1.0);
    vec3 c = col;
    outColor = vec4(col, 1.0);
}
