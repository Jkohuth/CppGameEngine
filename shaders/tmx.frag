#version 120

varying vec2 TexCoord;
    
uniform sampler2D tileMap;
uniform sampler2D lookupMap;
    
varying vec4 color;


void main()
{

    vec4 color = texture2D(lookupMap, TexCoord);
    gl_FragColor = color;
}