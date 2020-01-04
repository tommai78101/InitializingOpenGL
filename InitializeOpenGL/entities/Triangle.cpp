#include "../pch.h"
#include "Entity.h"
#include "Triangle.h"

namespace Kaizo {
	Triangle::Triangle() {
		//Initialize variables
		this->handleVertexArrayObject = 0;
		this->handleVertexBufferObject = 0;
		this->isReady = false;

		//---------------------------------------------------------------

		//Allocate and assign a Vertex Array Object to our handle
		glGenVertexArrays(1, &(this->handleVertexArrayObject));

		//Bind our Vertex Array Object as the current used object
		glBindVertexArray(this->handleVertexArrayObject);

		//----------------------------------------------------------------------------------------------------------

			//Generate the buffer objects for vertices
			glGenBuffers(1, &(this->handleVertexBufferObject));

				//Bind our Vertex Buffer Object as the current used buffer and store the vertex attribute location
				glBindBufferARB(GL_ARRAY_BUFFER, this->handleVertexBufferObject);

				//Copy the vertex points data into the currently bound buffer object
				size_t pointsSize = sizeof(this->points);
				glBufferDataARB(GL_ARRAY_BUFFER, pointsSize, this->points, GL_STATIC_DRAW);

			//Generate the buffer objects for indices
			glGenBuffers(1, &(this->handleIndexBufferObject));

				//Bind our Index Buffer Object as the current used buffer and store the vertex attribute location
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, this->handleIndexBufferObject);

				//Copy the indices data into the currently bound buffer object
				size_t indexSize = sizeof(this->indices);
				glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, indexSize, this->indices, GL_STATIC_DRAW);

			//----------------------------------------------------------------------------------------------------------

			//The method of using interleaved attributes in a single VBO, and offsets.

			//After focusing on the array object, we enable the first attribute, 0.
			//0 is the first attribute location, which contains our vertex buffer object.
			glEnableVertexAttribArrayARB(0);

				//We need to define the layout of the first vertex buffer object.
				//The first parameter refers to the first attribute's location, 0
				//The second parameter refers to the size of each element of the buffer object, which is a Vector3f made up of 3 floats
				//The third parameter determines the type of each individual value that makes up the Vector3f
				//The fourth parameter is whether the data is normalized or not. (If true, Integer Range [-1, 1] and Unsigned Range [0, 1])
				//The fifth parameter determines the "stride" or "offset" between consecutive generic attributes 
				//The sixth parameter determines the offset of the first component of the first generic attribute in the array. 
				//    Needs to be a void pointer.
				glVertexAttribPointerARB(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);

			//Setting up the color attribute. Uses the same code logic as above.
			glEnableVertexAttribArrayARB(1);
				glVertexAttribPointerARB(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3 * sizeof(GLfloat)));

			//----------------------------------------------------------------------------------------------------------

			//Load the shaders
			this->LoadShaderProgramARB();

		//Unbind our Vertex Array Object as the current used object
		glBindVertexArray(0);

			//Stop focusing on the array object, we disable the first attribute, 0.
			//0 is the first attribute location, which contains our vertex buffer object.
			glDisableVertexAttribArrayARB(0);

		this->isReady = true;
	}

	Triangle::~Triangle() {
		/* Cleanup all the things we bound and allocated */
		glUseProgramObjectARB(0);
		glDisableVertexAttribArrayARB(0);

		if (this->handleShaderProgramARB) {
			if (this->handleVertexShader) {
				glDetachShader(this->handleShaderProgramARB, this->handleVertexShader);
				glDeleteShader(this->handleVertexShader);
				this->handleVertexShader = 0;
			}
			if (this->handleFragmentShader) {
				glDetachShader(this->handleShaderProgramARB, this->handleFragmentShader);
				glDeleteShader(this->handleFragmentShader);
				this->handleFragmentShader = 0;
			}
			glDeleteProgram(this->handleShaderProgramARB);
			this->handleShaderProgramARB = 0;
		}

		glDeleteBuffers(1, &this->handleVertexBufferObject);
		this->handleVertexBufferObject = 0;

		glDeleteVertexArrays(1, &this->handleVertexArrayObject);
		this->handleVertexArrayObject = 0;
	}

	GLuint Triangle::GetVertexBufferObject() {
		return this->handleVertexBufferObject;
	}

	GLuint Triangle::GetVertexArrayObject() {
		return this->handleVertexArrayObject;
	}

	GLhandleARB Triangle::GetShaderProgramARB() {
		return this->handleShaderProgramARB;
	}

	void Triangle::SetUniformScreenResolution(float width, float height) {
		glUseProgram(this->handleShaderProgramARB);
		this->SetScreenResolution(width, height);
		GLint location = glGetUniformLocationARB(this->handleShaderProgramARB, "u_ScreenResolution");
		//Setting 1 vec2 to the shader. 1 is the size. 2fv refers to vec2.
		glUniform2fvARB(location, 1, this->screenResolutions);
	}

	void Triangle::SetUniformTime(GLfloat time) {
		glUseProgram(this->handleShaderProgramARB);
		this->SetTime(time);
		GLint location = glGetUniformLocationARB(this->handleShaderProgramARB, "u_Time");
		//Setting 1 vec2 to the shader. 1 is the size. 2fv refers to vec2.
		glUniform1fARB(location, time);
	}

	void Triangle::Draw() {
		//Use the program object
		glUseProgramObjectARB(this->handleShaderProgramARB);

		//Bind the vertex array
		glBindVertexArray(this->handleVertexArrayObject);

		//Draw the element by index
		glDrawElements(GL_TRIANGLES, sizeof(this->indices), GL_UNSIGNED_SHORT, nullptr);

		//Unbind the vertex array
		glBindVertexArray(0);
	}

	bool Triangle::IsReady() {
		return this->isReady;
	}

	GLuint Triangle::LoadShaderProgramARB() {
		//Provide relative path based from the macro root path, $(SolutionDir).
		this->LoadShaderFiles((GLchar*) "entities/Triangle.vert", (GLchar*) "entities/Triangle.frag");

		//Create shader program, attach all shaders, and then link shaders into program
		this->handleShaderProgramARB = glCreateProgramObjectARB();
		glAttachObjectARB(this->handleShaderProgramARB, this->handleVertexShader);
		glAttachObjectARB(this->handleShaderProgramARB, this->handleFragmentShader);
		glLinkProgramARB(this->handleShaderProgramARB);

		//Linking error handling
		GLint linkStatus = 0;
		glGetProgramiv(this->handleShaderProgramARB, GL_LINK_STATUS, &linkStatus);
		if (linkStatus == GL_FALSE) {
			GLint linkLogSize = 0;
			glGetProgramiv(this->handleShaderProgramARB, GL_INFO_LOG_LENGTH, &linkLogSize);
			std::vector<GLchar> logData(linkLogSize);
			glGetProgramInfoLog(this->handleShaderProgramARB, (GLsizei) linkLogSize, &linkLogSize, &logData[0]);
			OutputDebugStringA((LPCSTR) logData.data());
			glDeleteProgram(this->handleShaderProgramARB);
			return 0;
		}

		return this->handleShaderProgramARB;
	}
}