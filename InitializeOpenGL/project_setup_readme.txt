                                                                                                               Line wrap boundary  >|

Project Properties Setup:

1. Set the active configuration to "All Configurations" and active platform to "All Platforms".
2. Linker > Input > Additional Dependencies, add "opengl32.lib".
3. When creating the Windows message pump, never pass the handle to the window (hwnd) to PeekMessage()'s second parameter. There is 
	seldom a reason to specify the window-handle to PeekMessage, even if you add more windows, you still want them to be handled by 
	the same message loop anyway. 
4. Go to "khronos.org" and obtain "wgl.h". Copy the contents or download the raw file and put them somewhere in the project. 
	Recommended to put it inside the "gl" folder in the project directory.
5. In C++, array initializers for class members do not work unless you provide a fixed size.
6. In order to use any OpenGL 1.2 and up functions (glGenBuffers, for example), you must "query" the functions. To "query" them, you
	must first declare the function pointer types, before using the functions as intended.
7. For function pointers, all function pointer declarations in the header files must be prefixed with "extern" access modifier. Only
	then, declare the function pointers inside a CPP file that will guarantee it will create only 1 translation unit by the compiler.
8. Do not pollute the namespace with function pointers. Unless it is necessary, check to make sure there are no conflicting function
	pointers existing inside the namespaces in case of Access Violations pointing to 0x0000000000000000 addresses.
9. For CPP files placed inside nested folders, not only should the CPP files must #include the precompiled header that is located in
	the project root directory, but also, the CPP file property settings for the C,C++ > Precompiled Headers should also point to
	the precompiled headers using relative paths.
10. For relative paths, by default, the project uses $(SolutionDir) as the root directory. If one must provide relative path to a file
	located at "$(SolutionDir)Foo\Bar\file.txt", the relative path should be "Foo/Bar/file.txt", without the "../" at the beginning.
11. Keep the "cpp.hint" file. They are used for helping the Visual Studio IDE interpret Visual C++ identifiers and macros.
12. Make sure to set the "pch.h" as a pre-compiled header. The "pch.cpp" is used merely to get MSVC++ compiler to compile the "pch.h" 
	ahead-of-time.
13. You might need the VSFILTER and VCXPROJ files, as it contains how the source codes are structured in the Visual Studio Solution
	when opened in the editor.
