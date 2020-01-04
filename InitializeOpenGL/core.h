#ifndef __CORE__H__

namespace Kaizo {
	//Win32 function declarations
	typedef LRESULT(*WindowProc)(HWND, UINT, WPARAM, LPARAM);

	class Triangle;

	class Engine {
	private:
		//Global variables
		int gameWidth;
		int gameHeight;
		int gameBitDepth;
		bool flagEnableFullscreen;
		bool flagRunning;

		//Windows related important variables
		LPCTSTR windowName;
		HINSTANCE handleInstance;
		HWND handleWindow;
		HDC handleDeviceContext;

		//OpenGL related important variables
		GLuint pixelFormatHolder;
		HGLRC handleRenderingContext;

		//Internal functions
		DWORD HandleError(LPCTSTR lpszFunction);
		long long GetMillisecondsNow();
		double GetSecondsNow();

		//Internal template functions
		template<typename... Varargs>
		void DebugPrintf(std::string format, Varargs... args);

		//Test variables
		//TODO: Need to put Triangles here.
		std::vector<std::shared_ptr<Triangle>> triangles;

	public:
		//Constructors
		Engine();
		Engine(int width, int height);

		//Functions
		void InitializeWindow(WindowProc proc, LPCTSTR windowName);
		void ErrorExit(LPCTSTR lpszFunction);
		void SetupOpenGLScene();
		void LoadOpenGLObjects();
		void ExecuteLoop();
		void CleanExit();
		void ObtainOpenGLInfo();
		void Update();
		void Render();
		void LoadOpenGLFunctions();
	};
}



#	define __CORE__H__
#endif
