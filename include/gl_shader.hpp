/*
 * =====================================================================================
 *
 *       Filename:  gl_shader.h
 *
 *    Description:  A class for glShader compilation and linking 
 *       Compiler:  gcc
 *
 *        Practice
 *
 * =====================================================================================
 */


namespace practice{
	
	class Shader{

	GLuint sID;

public:

	GLuint id() const { return sID; }

	Shader(const char * vert, const char * frag){


		//Create shader program
		sID = glCreateProgram();
		GLuint vID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);

		//Load shader source code
		glShaderSource(vID, 1, &vert, NULL);
		glShaderSource(fID, 1, &frag, NULL);

		//GL compile shader
		glCompileShader(vID);
		glCompileShader(fID);

		//Check for errors
		compilerCheck(vID);
		compilerCheck(fID);

		//attach shaders
		glAttachShader(sID,vID);
		glAttachShader(sID,fID);

		//Link Program
		glLinkProgram(sID);

		linkCheck(sID);

		glUseProgram(sID);

	}

	void bind() { glUseProgram(sID); }
	void unBind() { glUseProgram(0); }

	void compilerCheck(GLuint ID){
		GLint comp;
		glGetShaderiv(ID, GL_COMPILE_STATUS, &comp);


		if(comp == GL_FALSE){
			cout<< "Shader Compilation FAILED" << endl;
			GLchar messages[256];
			glGetShaderInfoLog(ID, sizeof(messages), 0, &messages[0]);
			cout << messages;
		}
	}

	void linkCheck(GLuint ID){
		GLint linkStatus, validateStatus;
		glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus);

		if(linkStatus == GL_FALSE){
			cout<<"Shader linking FAILED" << endl;
			GLchar messages[256];
			glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
			cout << messages;
		}


		glValidateProgram(ID);
		glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateStatus);

		if(validateStatus == GL_FALSE){
			cout << "Shader validation FAILED " << endl;
			GLchar messages[256];
			glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
			cout<< messages;
		}

	}




	};
}














