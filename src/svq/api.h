#ifndef API__H
#define API__H

#ifdef _WIN32
	#ifdef _DLL
		#define SVQ_API __declspec(dllexport)
	#else
		#define SVQ_API __declspec(dllimport)
	#endif
#else
	#define SVQ_API
#endif

#endif // API__H
