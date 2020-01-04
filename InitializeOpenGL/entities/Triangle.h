#ifndef __TRIANGLE__H__

namespace Kaizo {
	class Triangle : public Entity {
	private:
		//Data stuffs - Drawing a quad (2 triangles) instead of 1 triangle
		//Interleaved attribute in a single VBO
		float points[6 * 4] = {
			//Top vertex (position XYZ, color RGB)
			-1.0f,  1.0f,  0.0f, 0.8f, 0.2f, 0.3f,
			//Right vertex (position XYZ, color RGB)
			1.0f, 1.0f,  0.0f, 0.2f, 0.8f, 0.2f,
			//Left vertex (position XYZ, color RGB)
		  1.0f, -1.0f,  0.0f, 0.15f, 0.25f, 0.8f,
		  //Bottom vertex (position XYZ, color RGB)
		  -1.0f, -1.0f,  0.0f, 0.15f, 0.25f, 0.8f
		};
		GLshort indices[3 * 2] = { 0, 1, 2, 0, 2, 3 };

		//===============================================================================

		bool isReady = false;

		//--- Non-ARB OpenGL stuffs ---
		//Holds a chunk of memory onto the graphics cards in a unit called a vertex buffer object
		GLuint handleVertexBufferObject = 0;

		//Holds a chunk of memory onto the graphics cards in a vertex buffer object for indices.
		GLuint handleIndexBufferObject = 0;

		//Holds all of the vertex buffer objects that we want to use and the memory layout of each buffer objects
		//We set up the vertex array object once per mesh
		GLuint handleVertexArrayObject = 0;

		//--- ARB OpenGL stuffs ---
		GLuint handleShaderProgramARB = 0;

	public:
		Triangle();
		~Triangle();

		//Getters
		GLuint GetVertexBufferObject();
		GLuint GetVertexArrayObject();
		GLuint GetShaderProgramARB();

		//Setters
		void SetUniformScreenResolution(float x, float y);
		void SetUniformTime(GLfloat time);

		void Draw();
		bool IsReady();
		GLuint LoadShaderProgramARB();
	};
}

//How to debug preprocessing header files
//#	pragma message("Triangle header is defined.")
#	define __TRIANGLE__H__
#endif
