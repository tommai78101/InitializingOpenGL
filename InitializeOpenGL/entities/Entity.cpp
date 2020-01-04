#include "../pch.h"
#include "Entity.h"

namespace Kaizo {
	ShaderReader::ShaderReader(std::string filename) {
		std::string line;
		std::string allLines;
		std::ifstream file(filename);
		if (file.is_open()) {
			while (std::getline(file, line)) {
				allLines = allLines + line + "\n";
			}
			this->sourceCode.assign(allLines.begin(), allLines.end());
			this->size = (GLint) this->sourceCode.size();
			this->data = this->sourceCode.data();

			file.close();
		}
		else {
			OutputDebugString(TEXT("Error - ShaderReader cannot load file. Please check if file is loaded in properly."));
			this->sourceCode.clear();
			this->size = 0;
			this->data = nullptr;
		}
	}
	
	//-------------------------------------------------------------------------------------------------------

	size_t getFileLength(std::ifstream& file) {
		if (!file.good())
			return 0;

		//Set the position to the end of the file.
		file.seekg(0, std::ios::end);

		//Return the position of the current character in the input stream
		size_t length = file.tellg();

		//Reset to beginning of the file
		file.seekg(0, std::ios::beg);

		return length;
	}

	Entity::~Entity() {}

	void Entity::LoadShaderFiles(GLchar* vertexShaderFilename, GLchar* fragmentShaderFilename) {
		//Vertex shaders
		ShaderReader vertexShader(vertexShaderFilename);
		this->handleVertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER);
		glShaderSourceARB(this->handleVertexShader, 1, &vertexShader.data, &vertexShader.size);

		//Checking for shader compiling errors
		GLint shaderCompilationStatus = 0;
		GLint shaderCompilationLogSize = 0;
		glCompileShaderARB(this->handleVertexShader);
		glGetShaderiv(this->handleVertexShader, GL_COMPILE_STATUS, &shaderCompilationStatus);
		if (shaderCompilationStatus == GL_FALSE) {
			glGetShaderiv(this->handleVertexShader, GL_INFO_LOG_LENGTH, &shaderCompilationLogSize);
			std::vector<GLchar> errorLog(shaderCompilationLogSize);
			glGetShaderInfoLog(this->handleVertexShader, (GLsizei) shaderCompilationLogSize, &shaderCompilationLogSize, &errorLog[0]);
			OutputDebugStringA((LPCSTR) errorLog.data());
			glDeleteShader(this->handleVertexShader);
			return;
		}

		//Fragment shaders
		ShaderReader fragmentShader(fragmentShaderFilename);
		this->handleFragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);
		glShaderSourceARB(this->handleFragmentShader, 1, &fragmentShader.data, &fragmentShader.size);

		glCompileShaderARB(this->handleFragmentShader);
		glGetShaderiv(this->handleFragmentShader, GL_COMPILE_STATUS, &shaderCompilationStatus);
		if (shaderCompilationStatus == GL_FALSE) {
			glGetShaderiv(this->handleFragmentShader, GL_INFO_LOG_LENGTH, &shaderCompilationLogSize);
			std::vector<GLchar> errorLog(shaderCompilationLogSize);
			glGetShaderInfoLog(this->handleFragmentShader, (GLsizei) shaderCompilationLogSize, &shaderCompilationLogSize, &errorLog[0]);
			OutputDebugStringA((LPCSTR) errorLog.data());
			glDeleteShader(this->handleFragmentShader);
			return;
		}
	}

	void Entity::SetScreenResolution(GLfloat width, GLfloat height) {
		this->screenResolutions[0] = (float) width;
		this->screenResolutions[1] = (float) height;
	}

	void Entity::SetTime(GLfloat newTime) {
		this->currentTime = newTime;
	}
}
