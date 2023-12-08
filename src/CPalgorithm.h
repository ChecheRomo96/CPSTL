#ifndef CROSS_PLATFORM_ALGORITHM_H
#define CROSS_PLATFORM_ALGORITHM_H
	
	namespace cpstd{


			template <class T> 
			const T& min (const T& a, const T& b) {
			  return !(b<a)?a:b;     // or: return !comp(b,a)?a:b; for version (2)
			}

			template <class T, class U> 
			const T& min (const T& a, const U& b) {
			  return !(b<a)?a:b;     // or: return !comp(b,a)?a:b; for version (2)
			}

			
			template <class InputIterator, class OutputIterator>
			OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
			    // Iterate over the range [first, last) and copy elements to the destination
			    while (first != last) {
			        *result = *first; // Copy element
			        ++result;         // Move to the next position in the destination
			        ++first;          // Move to the next position in the source
			    }

			    return result; // Return the iterator pointing to the end of the destination range
			}
			
		///////////////////////////////////////////////////////////////////////////////
		// Non-modifying sequence operations

	  	//
	  	///////////////////////////////////////////////////////////////////////////////
	  	// Modifying sequence operations


	  	//
	  	///////////////////////////////////////////////////////////////////////////////
	  	// Sorting


            #ifdef CPSTL_USING_STL
                template<typename T>
                using sort = std::sort<T>;
            #else
            #endif

	  	//
	  	///////////////////////////////////////////////////////////////////////////////
  	}

#endif//CROSS_PLATFORM_ALGORITHM_H