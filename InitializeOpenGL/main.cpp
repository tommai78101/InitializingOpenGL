#include "pch.h"
#include "main.h"

//Macro header files
//Must include only once.
#	include "dllexport.h"

//ARB functions
PFNGLCREATEPROGRAMOBJECTARBPROC      glCreateProgramObjectARB;
PFNGLDELETEOBJECTARBPROC             glDeleteObjectARB;
PFNGLUSEPROGRAMOBJECTARBPROC         glUseProgramObjectARB;
PFNGLCREATESHADEROBJECTARBPROC       glCreateShaderObjectARB;
PFNGLSHADERSOURCEARBPROC             glShaderSourceARB;
PFNGLCOMPILESHADERARBPROC            glCompileShaderARB;
PFNGLGETOBJECTPARAMETERIVARBPROC     glGetObjectParameterivARB;
PFNGLATTACHOBJECTARBPROC             glAttachObjectARB;
PFNGLGETINFOLOGARBPROC               glGetInfoLogARB;
PFNGLLINKPROGRAMARBPROC              glLinkProgramARB;
PFNGLGETUNIFORMLOCATIONARBPROC       glGetUniformLocationARB;
PFNGLUNIFORM4FARBPROC                glUniform4fARB;
PFNGLUNIFORM3FARBPROC                glUniform3fARB;
PFNGLUNIFORM1FARBPROC                glUniform1fARB;
PFNGLUNIFORM1IARBPROC                glUniform1iARB;
PFNGLUNIFORM2FVARBPROC               glUniform2fvARB;
PFNGLGETATTRIBLOCATIONARBPROC        glGetAttribLocationARB;
PFNGLVERTEXATTRIB3FARBPROC           glVertexAttrib3fARB;
PFNGLVERTEXATTRIBPOINTERARBPROC      glVertexAttribPointerARB;
PFNGLENABLEVERTEXATTRIBARRAYARBPROC  glEnableVertexAttribArrayARB;
PFNGLDISABLEVERTEXATTRIBARRAYARBPROC glDisableVertexAttribArrayARB;
PFNGLGENBUFFERSARBPROC               glGenBuffersARB;
PFNGLBINDBUFFERARBPROC               glBindBufferARB;
PFNGLBUFFERDATAARBPROC               glBufferDataARB;

//Non-ARB functions
PFNGLGENVERTEXARRAYSPROC             glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC             glBindVertexArray;
PFNGLGENBUFFERSPROC                  glGenBuffers;
PFNGLCREATESHADERPROC                glCreateShader;
PFNGLDETACHSHADERPROC                glDetachShader;
PFNGLDELETESHADERPROC                glDeleteShader;
PFNGLDELETEPROGRAMPROC               glDeleteProgram;
PFNGLDELETEBUFFERSPROC               glDeleteBuffers;
PFNGLDELETEVERTEXARRAYSPROC          glDeleteVertexArrays;
PFNGLGETSHADERIVPROC                 glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC            glGetShaderInfoLog;
PFNGLGETPROGRAMIVPROC                glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC           glGetProgramInfoLog;
PFNGLUSEPROGRAMPROC                  glUseProgram;

LRESULT CALLBACK MainWindowProcedure(HWND hwnd, UINT msg, WPARAM width, LPARAM length) {
	switch (msg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;
		default:
			break;
	}
	return DefWindowProc(hwnd, msg, width, length);
}

int main() {
	//Just some name we give to our core engine.
	//Also, it's to prevent global namespace pollution.
	using Kaizo::Engine;

	//Engine variable.
	Engine coreApp;

	//We initialize the OpenGL in this function.
	coreApp.InitializeWindow(MainWindowProcedure, TEXT("OpenGL Window"));

	//Set up the OpenGL objects.
	coreApp.SetupOpenGLScene();

	//We then execute the program message loops.
	//Resource cleanup is handled inside this function.
	coreApp.ExecuteLoop();

	//We then exit the program.
	return 0;
}