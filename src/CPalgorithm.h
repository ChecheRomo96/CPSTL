#ifndef CROSS_PLATFORM_ALGORITHM_H
#define CROSS_PLATFORM_ALGORITHM_H
	
	namespace cpstd{

			#ifdef min
			#undef min
			#endif

			template <class T> 
			const T& min(const T& a, const T& b) {
			  return !(b<a)?a:b;     // or: return !comp(b,a)?a:b; for version (2)
			}

			template <class T, class U> 
			const T& min(const T& a, const U& b) {
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

            	using std::sort;  // Alias the first function

			    template <class RandomAccessIterator, class Compare>
			    void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
			        std::sort(first, last, comp);
			    }



            #else

			template <typename RandomAccessIterator, typename Compare>
			RandomAccessIterator partition(RandomAccessIterator low, RandomAccessIterator high, Compare comp) {
			    auto pivot = *(high - 1);  // Choose the last element as the pivot
			    auto i = low - 1;

			    for (auto j = low; j < high - 1; ++j) {
			        if (comp(*j, pivot)) {
			            i++;
			            std::iter_swap(i, j);
			        }
			    }

			    std::iter_swap(i + 1, high - 1);
			    return i + 1;
			}

			template <typename RandomAccessIterator, typename Compare>
			void qsort(RandomAccessIterator low, RandomAccessIterator high, Compare comp) {
			    if (low < high) {
			        auto pivotIndex = partition(low, high, comp);

			        qsort(low, pivotIndex, comp);
			        qsort(pivotIndex + 1, high, comp);
			    }
			}

			template <typename RandomAccessIterator, typename Compare>
			void sort(RandomAccessIterator low, RandomAccessIterator high, Compare comp) {
			    qsort(low, high, comp);
			}

			namespace {
			    // Using a lambda function as the binary predicate
			    auto lessThan = [](int a, int b) { return a < b; };
			}

			template  <typename RandomAccessIterator>
			void sort(RandomAccessIterator low, RandomAccessIterator high) {
			    qsort(low, high, lessThan);
			}

            #endif

	  	//
	  	///////////////////////////////////////////////////////////////////////////////
  	}

#endif//CROSS_PLATFORM_ALGORITHM_H