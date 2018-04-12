#version 120

varying vec2 TexCoords;
//varying 
vec4 color;

uniform sampler2D	scene;
uniform vec2		offsets[9];
uniform float		blur_kernel[9];

uniform bool shake;

void main() 
{
	color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	vec3 sample[9];
	// Sample from texture offsets if using convolution	matrix
	if(shake){
		for(int i = 0; i < 9; i++)
			sample[i] = vec3(texture2D(scene, TexCoords.st + offsets[i]));

		for(int i = 0; i < 9; i++)
			color += vec4(sample[i] * blur_kernel[i], 0.0f);
		color.a = 1.0f;
	}
	else{
		color = texture2D(scene, TexCoords);
	}

	gl_FragColor = color;

}
