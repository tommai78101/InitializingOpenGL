#pragma once

#ifndef __ENTITY_H___

namespace Kaizo {
	struct ShaderReader {
		std::vector<GLchar> sourceCode;
		const GLchar* data;
		GLint size;

		ShaderReader(std::string name);
	};

	class Entity {
	protected:
		//--- Shader stuffs ---
		GLuint handleVertexShader = 0;
		GLuint handleFragmentShader = 0;

		//Common uniforms
		float screenResolutions[2] = { 0.0f, 0.0f };
		float currentTime = 0.0f;

	public:
		virtual ~Entity();
		void LoadShaderFiles(GLchar* vertexShaderFilename, GLchar* fragmentShaderFilename);
		void SetScreenResolution(GLfloat width, GLfloat height);
		void SetTime(GLfloat newTime);
	};
}

//#	pragma message("Entity header is defined.")
#	define __ENTITY_H___
#endif