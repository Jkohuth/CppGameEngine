#version 120

attribute vec4 vertex;
varying vec2 TexCoords;

uniform bool  shake;
uniform float time;


void main(void){

    gl_Position = vec4(vertex.xy, 0.0f, 1.0f);
    vec2 texture = vertex.zw;

    TexCoords = texture;

    if(shake)
    {
        float strength = 0.01;
        gl_Position.x += cos(time * 10) * strength;
        gl_Position.y += cos(time * 15) * strength;
    }

}