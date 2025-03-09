#version 410 core  
out vec4 ourColour;  
uniform float time;  
void main() {  
    float r = (sin(time) / 2.0) + 0.5;  
    float g = (sin(time + 1.0) / 2.0) + 0.5;  
    float b = (sin(time + 2.0) / 2.0) + 0.5;  
    ourColour = vec4(r, g, b, 1.0);  
}  