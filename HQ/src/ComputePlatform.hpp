
#ifndef _HQ_COMPUTEPLATFORM_HPP_
#define _HQ_COMPUTEPLATFORM_HPP_


#include <vector>
#include "ComputeUnit.hpp"
//#include "ThreadPool.hpp"

#include "HQ.hpp"

// From CE
#include "ComputeEngine.hpp"

#include <future>

namespace HQ {



	class ComputePlatform {

	public:


		ComputePlatform();


		//TODO: add enqueue member function
		// param: Task ?

		void enqueue(Task* task);

		// KAOCC: remove this, we should not expose the internal data
		ComputeUnit* getComputeUnit(size_t index) const;

		size_t getNumberOfComputeUnit() const;

		~ComputePlatform();

		ComputePlatform(const ComputePlatform&) = delete;
		ComputePlatform& operator=(const ComputePlatform&) = delete;
		ComputePlatform(ComputePlatform&&) = delete;

	private:


		// a helper function for std::async
		static void dispatch(ComputeUnit* cu, CE::Function const* func, size_t globalSize, size_t offset);

		// test
		//static const size_t NUM_OF_UNITS = 1;


		CE::ComputeEngine* ce{ nullptr };
		std::vector<ComputeUnit*> computeUnits;


		//TODO: add sync support

		// tmp
		// for async

		// KAOCC: check for thread safe ?
		//std::vector<std::future<void>> futures;

	};



}


#endif

