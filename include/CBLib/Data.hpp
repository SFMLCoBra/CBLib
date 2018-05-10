#ifndef CB_DATA_HPP
#define CB_DATA_HPP

#include <iostream>

#ifdef _DEBUG
 #define CB_DEFAULT_ERROR_MSG(message) (std::cerr		\
		 << "ERROR-MESSAGE: " << message << std::endl   \
		 << "FILE: "		  << __FILE__ << std::endl  \
		 << "LINE: "		  << __LINE__ << std::endl  \
		 << "FUNCTION: "	  << __func__ << std::endl);

 #define CB_DEBUG_MSG(message) (std::cout << message << std::endl);

#else
#define CB_DEFAULT_ERROR_MSG(message)
#define CB_DEBUG_MSG(message)
#endif

#endif