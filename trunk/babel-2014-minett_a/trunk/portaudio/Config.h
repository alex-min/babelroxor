
/**-------------------------------------------------------------------------------

	bRep Kernel
	Copyright (C) 2010, Poncin Matthieu
	All rights reserved.

	This work is licensed under the Creative Commons
	Attribution-Share Alike 2.0 France License.
	To view a copy of this license, visit :
	http://creativecommons.org/licenses/by-sa/2.0/fr/

    cree le :        18/10/2010

--------------------------------------------------------------------------------*/
/**-------------------------------------------------------------------------------

    Config for multiplatform managing

--------------------------------------------------------------------------------*/

#ifndef UTILS_API_CONFIG_H_
#define UTILS_API_CONFIG_H_

    //#define DYNAMIC_LINK
    //#define EXPORT_API

/// define Operating System
	#if !defined(SYSTEM_WINDOWS) && !defined(SYSTEM_LINUX) && !defined(SYSTEM_MACOS) && !defined(SYSTEM_FREEBSD)
		#if defined(_WIN32) || defined(__WIN32__) || defined(__WIN64) || defined(__WIN64__)     /// Windows
			#define SYSTEM_WINDOWS
		#elif defined(linux) || defined(__linux)                                                /// Linux
			#define SYSTEM_LINUX
		#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh) /// MacOS
			#define SYSTEM_MACOS
		#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
			#define SYSTEM_FREEBSD
		#else                                                                                   /// Unsupported system
			#error This operating system is not supported on the API_NAME
		#endif
	#endif


/// linking option (static or shared)
    #ifdef SYSTEM_WINDOWS                                       /// windows
        #ifdef DYNAMIC_LINK                                     /// dynamic
            #ifdef EXPORT_API
                #define LINK_OPTION_UTILS     __declspec(dllexport)
            #else
                #define LINK_OPTION_UTILS     __declspec(dllimport)
            #endif
        #else                                                   /// static (do nothing)
            #define LINK_OPTION_UTILS
        #endif
    #else                                                       /// othes os (do nothing)
        #define LINK_OPTION_UTILS
    #endif

#endif
