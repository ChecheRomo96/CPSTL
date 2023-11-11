#ifndef CROSS_PLATFORM_ALGORITHM_H
#define CROSS_PLATFORM_ALGORITHM_H
	
	namespace cpstd{
		///////////////////////////////////////////////////////////////////////////////
		// Non-modifying sequence operations

			template <class T> 
			const T& min (const T& a, const T& b) {
			  return !(b<a)?a:b;     // or: return !comp(b,a)?a:b; for version (2)
			}

			template <class T, class U> 
			const T& min (const T& a, const U& b) {
			  return !(b<a)?a:b;     // or: return !comp(b,a)?a:b; for version (2)
			}
	  	//
	  	///////////////////////////////////////////////////////////////////////////////
	  	// Modifying sequence operations



	  	//
	  	///////////////////////////////////////////////////////////////////////////////
	  	// Sorting



	  	//
	  	///////////////////////////////////////////////////////////////////////////////
  	}

#endif//CROSS_PLATFORM_ALGORITHM_H