#include "pch.h"
#include "entities/Entity.h"
#include "entities/Triangle.h"
#include "core.h"

namespace Kaizo {
	Engine::Engine() :
		gameWidth(640), gameHeight(480), gameBitDepth(32)
	{
		this->flagRunning = false;
		this->flagEnableFullscreen = false;
		this->windowName = nullptr;
		this->handleInstance = nullptr;
		this->handleWindow = nullptr;
		this->handleDeviceContext = nullptr;
		this->pixelFormatHolder = (GLuint) 0;
		this->handleRenderingContext = nullptr;
	}

	Engine::Engine(int width, int height) :
		gameWidth(width), gameHeight(height), gameBitDepth(32)
	{
		this->flagRunning = false;
		this->flagEnableFullscreen = false;
		this->windowName = nullptr;
		this->handleInstance = nullptr;
		this->handleWindow = nullptr;
		this->handleDeviceContext = nullptr;
		this->pixelFormatHolder = (GLuint)0;
		this->handleRenderingContext = nullptr;
	}

	void Engine::InitializeWindow(WindowProc mainWindowProcedure, LPCTSTR windowName) {
		this->windowName = windowName;

		if (!this->handleInstance)
			this->handleInstance = GetModuleHandle(nullptr);

		//Window class
		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(wc);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc                          = mainWindowProcedure;
		wc.hInstance = this->handleInstance;
		//Default application icon
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		//MSDN - A color value must be one of the following standard system colors (the value 1 must be added to the chosen color)
		wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
		wc.lpszMenuName = this->windowName;
		wc.lpszClassName = this->windowName;
		

		if (!RegisterClassEx(&wc)) {
			this->ErrorExit(TEXT("RegisterClassEx"));
		}

		//Attempting full screen mode
		if (this->flagEnableFullscreen) {
			DEVMODE devModeScreenSettings = {};
			devModeScreenSettings.dmSize = sizeof(devModeScreenSettings);
			//"Pel" = "Pixel".
			devModeScreenSettings.dmPelsWidth = this->gameWidth;
			devModeScreenSettings.dmPelsHeight = this->gameHeight;
			devModeScreenSettings.dmBitsPerPel = this->gameBitDepth;
			devModeScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			//CDS_FULLSCREEN flag gets rid of the Start Taskbar
			if (ChangeDisplaySettings(&devModeScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
				//If not successful, we need Plan B. Offer two options: Quit game or use windowed mode.
				//We prompt the user to choose whether to use windowed mode or quit the game.
				LPCTSTR message = TEXT("The requested fullscreen mode is not supported by\nyour video card. Use windowed mode instead?");
				LPCTSTR title = TEXT("Error");
				LPCTSTR quitMessage = TEXT("Program will now close.");
				if (MessageBox(nullptr, message, title, MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
					//User accepts to use windowed mode.
					this->flagEnableFullscreen = false;
				}
				else {
					//Prompt user the game will quit.
					MessageBox(nullptr, quitMessage, title, MB_OK | MB_ICONSTOP);
					this->ErrorExit(TEXT("ChangeDisplaySettings"));
				}
			}
		}

		DWORD dwExStyle;
		DWORD dwStyle;
		if (this->flagEnableFullscreen) {
			dwExStyle = WS_EX_APPWINDOW;
			dwStyle = WS_POPUP;
			//Hide mouse pointer
			ShowCursor(false);
		}
		else {
			dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
			dwStyle = WS_OVERLAPPEDWINDOW;
		}

		//Adjust window to requested size.
		RECT windowRect = {};
		windowRect.left = 0;
		windowRect.right = this->gameWidth;
		windowRect.top = 0;
		windowRect.bottom = this->gameHeight;
		AdjustWindowRectEx(&windowRect, dwStyle, false, dwExStyle);

		//Create the window
		dwStyle |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		this->handleWindow = CreateWindowEx(dwExStyle, windowName, windowName, dwStyle, 0, 0, this->gameWidth, this->gameHeight, nullptr, nullptr, this->handleInstance, nullptr);
		if (!this->handleWindow) {
			this->ErrorExit(TEXT("CreateWindowEx"));
		}

		//Static pixel format descriptor. Used only in the initialization process. Only initialize variable if variable doesn't exist.
		//Variable is not expected to be changed after initialization.
		static PIXELFORMATDESCRIPTOR pfd =              // "pfd" tells Windows how we want things to be
		{
			 sizeof(PIXELFORMATDESCRIPTOR),              // Size Of This Pixel Format Descriptor
			 1,                                          // Version Number
			 PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
			 PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
			 PFD_DOUBLEBUFFER,                           // Must Support Double Buffering
			 PFD_TYPE_RGBA,                              // Request An RGBA Format
			 (BYTE) this->gameBitDepth,                  // Select Our Color Depth
			 0, 0, 0, 0, 0, 0,                           // Color Bits Ignored
			 0,                                          // No Alpha Buffer
			 0,                                          // Shift Bit Ignored
			 0,                                          // No Accumulation Buffer
			 0, 0, 0, 0,                                 // Accumulation Bits Ignored
			 16,                                         // 16Bit Z-Buffer (Depth Buffer)  
			 0,                                          // No Stencil Buffer
			 0,                                          // No Auxiliary Buffer
			 PFD_MAIN_PLANE,                             // Main Drawing Layer
			 0,                                          // Reserved
			 0, 0, 0                                     // Layer Masks Ignored
		};

		//Obtain device context
		if (!(this->handleDeviceContext = GetDC(this->handleWindow))) {
			this->ErrorExit(TEXT("GetDC"));
			return;
		}

		//Find matching pixel format
		if (!(this->pixelFormatHolder = ChoosePixelFormat(this->handleDeviceContext, &pfd))) {
			//Can't find any supported pixel formats.
			this->ErrorExit(TEXT("ChoosePixelFormat"));
			return;
		}

		//Set the pixel format
		if (!SetPixelFormat(this->handleDeviceContext, this->pixelFormatHolder, &pfd)) {
			//Unable to set pixel format
			this->ErrorExit(TEXT("SetPixelFormat"));
			return;
		}

		//Obtain rendering context
		if (!(this->handleRenderingContext = wglCreateContext(this->handleDeviceContext))) {
			//Unable to obtain rendering context
			this->ErrorExit(TEXT("wglCreateContext"));
			return;
		}

		//Activate the rendering context
		if (!wglMakeCurrent(this->handleDeviceContext, this->handleRenderingContext)) {
			//Unable to activate the rendering context.
			this->ErrorExit(TEXT("wglMakeCurrent"));
			return;
		}

		//Show window
		ShowWindow(this->handleWindow, SW_SHOWDEFAULT);

		//Set window to have a higher priority on focus
		SetForegroundWindow(this->handleWindow);

		//Set the keyboard focus to the window
		SetFocus(this->handleWindow);

		//Prepare window message pump
		this->flagRunning = true;
	}

	void Engine::ErrorExit(LPCTSTR lpszFunction) {
		this->CleanExit();

		//Handle the main error
		DWORD errorCode = this->HandleError(lpszFunction);

		//Kill the current process because of error.
		ExitProcess(errorCode);
	}

	DWORD Engine::HandleError(LPCTSTR lpszFunction) {
		// Retrieve the system error message for the last-error code
		LPVOID lpMsgBuf;
		LPTSTR lpDisplayBuf;

		// Prepare the parameters
		DWORD errorCode = GetLastError();
		DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
		DWORD language = MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT);

		// Format the message
		FormatMessage(flags, nullptr, errorCode, language, (LPTSTR)& lpMsgBuf, 0, nullptr);

		//Set the message string buffer length
		SIZE_T msgBufLength = lstrlen((LPTSTR)lpMsgBuf);
		msgBufLength += ((SIZE_T) lstrlen(lpszFunction) * 3);

		//Create the string buffer
		if (!(lpDisplayBuf = (LPTSTR)LocalAlloc(LMEM_ZEROINIT, msgBufLength))) {
			//Failed to create the string buffer. Just return the error code
			LocalFree(lpMsgBuf);
			return errorCode;
		}

		//Do not include the NUL terminator at the very end of the "lpDisplayBuf".
		SIZE_T intended = ((SIZE_T) LocalSize(lpDisplayBuf)) - 1;

		//For "__func__" runtime macro, use %S, with a capital S, not lowercase S. 
		//This is not "printf". This is "StringCchPrintf".
		//See footnote for more information.
		//https://docs.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions?view=vs-2017
		HRESULT result = StringCchPrintf(lpDisplayBuf,
													intended,
													TEXT("%S\n\n%s\nFailed with error %d: %ls\n"),
													__func__, lpszFunction, errorCode, (LPTSTR) &lpMsgBuf);

		//Display the error message and exit the process
		//We display alternate message so we know where to start debugging at.
		if (result == S_OK)
			MessageBoxW(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);
		else
			MessageBoxW(NULL, (LPCTSTR)TEXT("ErrorExit failed to catch error. Please debug!"),
							TEXT("Error"), MB_OK);

		//RAII
		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);

		//Return the error code
		return errorCode;
	}

	long long Engine::GetMillisecondsNow() {
		static LARGE_INTEGER staticFrequency;
		static BOOL staticUseQueryPerformanceCounter = QueryPerformanceFrequency(&staticFrequency);
		if (staticUseQueryPerformanceCounter) {
			LARGE_INTEGER now;
			QueryPerformanceCounter(&now);
			return (1000LL * now.QuadPart) / staticFrequency.QuadPart;
		}
		else {
			//Don't use the 32-bit version that overflows every 49 days.
			return (long long) GetTickCount64();
		}
	}

	double Engine::GetSecondsNow() {
		static LARGE_INTEGER staticFrequency;
		static BOOL staticUseQueryPerformanceCounter = QueryPerformanceFrequency(&staticFrequency);
		if (staticUseQueryPerformanceCounter) {
			LARGE_INTEGER now;
			QueryPerformanceCounter(&now);
			return ((double) ((1000LL * now.QuadPart) / staticFrequency.QuadPart)) / 1000.0;
		}
		else {
			//Don't use the 32-bit version that overflows every 49 days.
			return ((double) GetTickCount64()) / 1000.0;
		}
	}

	template<typename... Varargs>
	void Engine::DebugPrintf(std::string format, Varargs... args) {
		CHAR buffer[100 * sizeof...(args)];
		StringCchPrintfA(buffer, 100 * sizeof...(args), format.c_str(), args...);
		OutputDebugStringA(buffer);
	}

	void Engine::SetupOpenGLScene() {
		//Preventing divide by zero
		if (this->gameHeight <= 0) {
			this->gameHeight = 1;
		}

		//Load essential OpenGL functions.
		this->LoadOpenGLFunctions();

		this->ObtainOpenGLInfo();

		//Enable depth testing.
		glEnable(GL_DEPTH_TEST);
		//Depth testing to interpret a smaller value as "closer" to the camera view.
		glDepthFunc(GL_LESS);

		//The Matrix stack is deprecated since OpenGL 3.0 and removed in OpenGL 3.2.

		//Setting the background color
		glClearColor(0.4f, 0.2f, 0.8f, 1.0f);

		//Load OpenGL objects
		this->LoadOpenGLObjects();
	}

	void Engine::ExecuteLoop() {
		MSG message;
		BOOL peekResult;

		while (this->flagRunning) {
			if ((peekResult = PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) != 0) {
				if (peekResult == -1) {
					this->flagRunning = false;
					this->ErrorExit(TEXT("PeekMessage"));
					break;
				}
				if (message.message == WM_QUIT) {
					this->flagRunning = false;
				}
				else {
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
			}
			this->Update();
			this->Render();
		}
		this->CleanExit();
	}

	void Engine::CleanExit() {
		// First, we reset from fullscreen mode to default mode
		if (this->flagEnableFullscreen) {
			ChangeDisplaySettings(nullptr, 0);
			ShowCursor(true);
		}

		// Second, we check if we obtained a rendering context. If yes, we need to handle this
		if (this->handleRenderingContext) {
			//Release the device context and rendering context
			if (!wglMakeCurrent(nullptr, nullptr)) {
				//Unable to release device context and rendering context.
				this->HandleError(TEXT("wglMakeCurrent(nullptr, nullptr)"));
			}

			if (!wglDeleteContext(this->handleRenderingContext)) {
				//Unable to delete rendering context.
				this->HandleError(TEXT("wglDeleteContext"));
			}
			this->handleDeviceContext = nullptr;
		}

		// Third, we check if we're able to release the device context.
		if (this->handleDeviceContext && !ReleaseDC(this->handleWindow, this->handleDeviceContext)) {
			//Failed to release device context
			this->HandleError(TEXT("ReleaseDC"));
			this->handleDeviceContext = nullptr;
		}

		// Fourth, check if we can destroy window
		if (this->handleWindow && this->flagRunning && !DestroyWindow(this->handleWindow)) {
			//Failed to destroy window
			this->HandleError(TEXT("DestroyWindow"));
		}
		this->handleWindow = nullptr;

		// Fifth, unregister the window class
		if (!UnregisterClass(this->windowName, this->handleInstance)) {
			//Unable to unregister window class
			this->HandleError(TEXT("UnregisterClass"));
			this->handleInstance = nullptr;
		}
	}

	void Engine::ObtainOpenGLInfo() {
		//Get renderer string
		const GLubyte* rendererInfo = glGetString(GL_RENDERER);
		//Get version string
		const GLubyte* versionInfo = glGetString(GL_VERSION);
		int major = 0;
		int minor = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);

		//Print info out to the window title
		size_t stringSize = strnlen_s((char*) rendererInfo, 128) + strnlen_s((char*) versionInfo, 128) + 32;
		CHAR title[300];
		StringCchPrintfA(title, stringSize, "%s. OpenGL version %d.%d.", rendererInfo, major, minor);
		SetWindowTextA(this->handleWindow, title);
	}

	void Engine::Update() {
		double currentTime = this->GetSecondsNow();
		for (size_t index = 0; index < this->triangles.size(); index++) {
			std::shared_ptr<Triangle> triangle = this->triangles.at(index);
			if (triangle->IsReady()) {
				GLfloat floatTime = static_cast<GLfloat>(currentTime);
				//We need to pass in the time in seconds, not in milliseconds.
				triangle->SetUniformTime(floatTime);
			}
		}
	}

	void Engine::Render() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (size_t index = 0; index < this->triangles.size(); index++) {
			std::shared_ptr<Triangle> triangle = this->triangles.at(index);
			if (triangle->IsReady()) {
				triangle->Draw();
			}
		}
		SwapBuffers(this->handleDeviceContext);
	}

	void Engine::LoadOpenGLObjects() {
		std::shared_ptr<Triangle> triangle(new Triangle);
		triangle->SetUniformScreenResolution((float) this->gameWidth, (float) this->gameHeight);
		this->triangles.push_back(triangle);
	}

	void Engine::LoadOpenGLFunctions() {
		//To add a function, add the function pointer declaration to the pch.h precompiled header file, with the "extern" keyword.
		//Then in the main.cpp, re-declare the same function pointer.
		//Finally, set the function pointer declaration by calling on wglGetProcAddress

		//Create all the functions using wglGetProcAddress
		glCreateProgramObjectARB = (PFNGLCREATEPROGRAMOBJECTARBPROC) wglGetProcAddress("glCreateProgramObjectARB");
		glDeleteObjectARB = (PFNGLDELETEOBJECTARBPROC) wglGetProcAddress("glDeleteObjectARB");
		glUseProgramObjectARB = (PFNGLUSEPROGRAMOBJECTARBPROC) wglGetProcAddress("glUseProgramObjectARB");
		glCreateShaderObjectARB = (PFNGLCREATESHADEROBJECTARBPROC) wglGetProcAddress("glCreateShaderObjectARB");
		glShaderSourceARB = (PFNGLSHADERSOURCEARBPROC) wglGetProcAddress("glShaderSourceARB");
		glCompileShaderARB = (PFNGLCOMPILESHADERARBPROC) wglGetProcAddress("glCompileShaderARB");
		glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC) wglGetProcAddress("glGetObjectParameterivARB");
		glAttachObjectARB = (PFNGLATTACHOBJECTARBPROC) wglGetProcAddress("glAttachObjectARB");
		glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC) wglGetProcAddress("glGetInfoLogARB");
		glLinkProgramARB = (PFNGLLINKPROGRAMARBPROC) wglGetProcAddress("glLinkProgramARB");
		glGetUniformLocationARB = (PFNGLGETUNIFORMLOCATIONARBPROC) wglGetProcAddress("glGetUniformLocationARB");
		glUniform4fARB = (PFNGLUNIFORM4FARBPROC) wglGetProcAddress("glUniform4fARB");
		glUniform3fARB = (PFNGLUNIFORM3FARBPROC) wglGetProcAddress("glUniform3fARB");
		glUniform1fARB = (PFNGLUNIFORM1FARBPROC) wglGetProcAddress("glUniform1fARB");
		glUniform1iARB = (PFNGLUNIFORM1IARBPROC) wglGetProcAddress("glUniform1iARB");
		glUniform2fvARB = (PFNGLUNIFORM2FVARBPROC) wglGetProcAddress("glUniform2fvARB");
		glGetAttribLocationARB = (PFNGLGETATTRIBLOCATIONARBPROC) wglGetProcAddress("glGetAttribLocationARB");
		glVertexAttrib3fARB = (PFNGLVERTEXATTRIB3FARBPROC) wglGetProcAddress("glVertexAttrib3fARB");
		glVertexAttribPointerARB = (PFNGLVERTEXATTRIBPOINTERARBPROC) wglGetProcAddress("glVertexAttribPointerARB");
		glEnableVertexAttribArrayARB = (PFNGLENABLEVERTEXATTRIBARRAYARBPROC) wglGetProcAddress("glEnableVertexAttribArrayARB");
		glDisableVertexAttribArrayARB = (PFNGLDISABLEVERTEXATTRIBARRAYARBPROC) wglGetProcAddress("glDisableVertexAttribArrayARB");
		glGenBuffersARB = (PFNGLGENBUFFERSARBPROC) wglGetProcAddress("glGenBuffersARB");
		glBindBufferARB = (PFNGLBINDBUFFERARBPROC) wglGetProcAddress("glBindBufferARB");
		glBufferDataARB = (PFNGLBUFFERDATAARBPROC) wglGetProcAddress("glBufferDataARB");

		//Non-ARB functions
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC) wglGetProcAddress("glGenVertexArrays");
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC) wglGetProcAddress("glBindVertexArray");
		glGenBuffers = (PFNGLGENBUFFERSPROC) wglGetProcAddress("glGenBuffers");
		glCreateShader = (PFNGLCREATESHADERPROC) wglGetProcAddress("glCreateShader");
		glDetachShader = (PFNGLDETACHSHADERPROC) wglGetProcAddress("glDetachShader");
		glDeleteShader = (PFNGLDELETESHADERPROC) wglGetProcAddress("glDeleteShader");
		glDeleteProgram = (PFNGLDELETEPROGRAMPROC) wglGetProcAddress("glDeleteProgram");
		glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) wglGetProcAddress("glDeleteBuffers");
		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC) wglGetProcAddress("glDeleteVertexArrays");
		glGetShaderiv = (PFNGLGETSHADERIVPROC) wglGetProcAddress("glGetShaderiv");
		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC) wglGetProcAddress("glGetShaderInfoLog");
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC) wglGetProcAddress("glGetProgramiv");
		glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC) wglGetProcAddress("glGetProgramInfoLog");
		glUseProgram = (PFNGLUSEPROGRAMPROC) wglGetProcAddress("glUseProgram");
	}
}