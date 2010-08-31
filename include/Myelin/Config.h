
#ifndef MYELIN_CONFIG_H_
#define MYELIN_CONFIG_H_



/* helpers for shared library support */
#if defined _WIN32 || defined __CYGWIN__
	#define MYELIN_HELPER_DLL_IMPORT __declspec(dllimport)
	#define MYELIN_HELPER_DLL_EXPORT __declspec(dllexport)
	#define MYELIN_HELPER_DLL_LOCAL
#else
	#if __GNUC__ >= 4
		#define MYELIN_HELPER_DLL_IMPORT __attribute__ ((visibility("default")))
		#define MYELIN_HELPER_DLL_EXPORT __attribute__ ((visibility("default")))
		#define MYELIN_HELPER_DLL_LOCAL  __attribute__ ((visibility("hidden")))
	#else
		#define MYELIN_HELPER_DLL_IMPORT
		#define MYELIN_HELPER_DLL_EXPORT
		#define MYELIN_HELPER_DLL_LOCAL
	#endif
#endif



/* define MYELIN_API and MYELIN_LOCAL */
/* Myelin is a shared library */
#ifdef MYELIN_DLL
	/* Myelin is being built, export it */
	#ifdef MYELIN_DLL_EXPORTS
		#define MYELIN_API MYELIN_HELPER_DLL_EXPORT
	/* Myelin is being used, import it */
	#else
		#define MYELIN_API MYELIN_HELPER_DLL_IMPORT
	#endif /* MYELIN_DLL_EXPORTS */
	
	#define MYELIN_LOCAL MYELIN_HELPER_DLL_LOCAL

/* Myelin is not a shared library */
#else
	#define MYELIN_API
	#define MYELIN_LOCAL
#endif /* MYELIN_DLL */



#endif /* MYELIN_CONFIG_H_ */
