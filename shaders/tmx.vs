   #version 120
    
    attribute vec3 vertex;
	attribute vec2 texture;
    varying vec2 TexCoord;
   
    uniform mat4 projection;
    
    
    void main()
    {
    	TexCoord = texture;

        gl_Position = projection * vec4(vertex, 1.0);

        
    }