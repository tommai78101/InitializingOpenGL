//Macros for hardware acceleration and dual graphics support.
//These macros must be exported only once in the entire compilation process.
#ifdef WIN32
extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif //def WIN32