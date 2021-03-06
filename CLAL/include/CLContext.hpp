
#ifndef _CLAL_CLCONTEXT_HPP_
#define _CLAL_CLCONTEXT_HPP_

#include <vector>

#include "CLReferenceCount.hpp"


#include "CLEvent.hpp"
//#include "CLProgram.hpp"
#include "CLBuffer.hpp"

namespace CLAL {

	class CLCommandQueue;
	class CLDevice;
	class CLProgram;

	class CLContext : public ReferenceCount<cl_context, clRetainContext, clReleaseContext> {



	public:

		// KAOCC: need to setup proper parameter

		// For single device
		static CLContext create(CLDevice device, cl_context_properties* props = nullptr);

		// For multiple device
		static CLContext create(const std::vector<CLDevice>& devices, cl_context_properties* props = nullptr);

		// For OpenCL primitive function
		static CLContext create(cl_context context, cl_device_id* primDevices, cl_command_queue* primCQs, size_t numDevices);

		// KAOCC: do we need public ctor with no parameter?
		CLContext() = delete;


		size_t getDeviceCount() const;
		CLDevice getDevice(size_t index) const;


		// For Buffer

		// KAOCC: setup parameter
		template <typename T> CLBuffer<T> createBuffer(size_t elementCount, cl_mem_flags flags) const;
		template <typename T> CLBuffer<T> createBuffer(size_t elementCount, cl_mem_flags flags, void* data) const;

		// write / read  buffers
		template <typename T> CLEvent writeBuffer(unsigned int index, CLBuffer<T> buffer, T const* hostBuffer, size_t elemCount) const;
		template <typename T> CLEvent writeBuffer(unsigned int index, CLBuffer<T> buffer, T const* hostBuffer, size_t offset, size_t elemCount) const;
		template <typename T> CLEvent readBuffer(unsigned int index, CLBuffer<T> buffer, T* hostBuffer, size_t elemCount) const;
		template <typename T> CLEvent readBuffer(unsigned int index, CLBuffer<T> buffer, T* hostBuffer, size_t offset, size_t elemCount) const;
		

		// Map / Unmap buffers
		template <typename T> CLEvent mapBuffer(unsigned int idx, CLBuffer<T> buffer, cl_map_flags flags, T** mappedData) const;
		template <typename T> CLEvent mapBuffer(unsigned int idx, CLBuffer<T> buffer, cl_map_flags flags, size_t offset, size_t elemCount, T** mappedData) const;
		template <typename T> CLEvent unmapBuffer(unsigned int idx, CLBuffer<T> buffer, T* mappedData) const;


		// For program and execution

		CLProgram createProgram(const std::vector<char>& sourceCode, char const* buildOpts = nullptr) const;
		CLEvent execute1D(unsigned int idx, size_t globalSize, size_t localSize, cl_kernel kernel);
		CLEvent execute1D(unsigned int idx, size_t globalSize, size_t localSize, cl_kernel kernel, CLEvent depEvent);


		// For C.Q.
		void finish(size_t index);
		void flush(size_t index);
		CLCommandQueue getCommandQueue(size_t index) const;





		virtual ~CLContext();



	private:

		// KAOCC: check the parameters

		// private ctors
		// wrap cl_context
		CLContext(cl_context context, const std::vector<CLDevice>& devices, const std::vector<CLCommandQueue>& cqs);

		// Pass by value (vector) !! Let the compiler decides.
		CLContext(cl_context context, std::vector<CLDevice> devices);

		//CLContext(cl_context context, const std::vector<CLDevice>& devices);


		// Create C.Q. for each devices
		void createCQs();

		std::vector<CLDevice> devices;
		std::vector<CLCommandQueue> commandQueues;

	};

	template<typename T>
	CLBuffer<T> CLContext::createBuffer(size_t elementCount, cl_mem_flags flags) const {
		return CLBuffer<T>::create(*this, flags, elementCount);
	}


	template<typename T>
	CLBuffer<T> CLContext::createBuffer(size_t elementCount, cl_mem_flags flags, void * data) const {
		return CLBuffer<T>::create(*this, flags, elementCount, data);
	}

	template<typename T>
	CLEvent CLContext::writeBuffer(unsigned int index, CLBuffer<T> buffer, T const * hostBuffer, size_t elemCount) const {
		return buffer.writeDeviceBuffer(commandQueues[index], hostBuffer, elemCount);
	}

	template<typename T>
	CLEvent CLAL::CLContext::writeBuffer(unsigned int index, CLBuffer<T> buffer, T const * hostBuffer, size_t offset, size_t elemCount) const {
		return buffer.writeDeviceBuffer(commandQueues[index], hostBuffer, offset, elemCount);
	}


	template<typename T>
	CLEvent CLContext::readBuffer(unsigned int index, CLBuffer<T> buffer, T * hostBuffer, size_t elemCount) const {
		return buffer.readDeviceBuffer(commandQueues[index], hostBuffer, elemCount);
	}

	template<typename T>
	CLEvent CLAL::CLContext::readBuffer(unsigned int index, CLBuffer<T> buffer, T * hostBuffer, size_t offset, size_t elemCount) const {
		return buffer.readDeviceBuffer(commandQueues[index], hostBuffer, offset, elemCount);
	}

	template<typename T>
	CLEvent CLContext::mapBuffer(unsigned int index, CLBuffer<T> buffer, cl_map_flags flags, T ** mappedData) const {

		return buffer.mapDeviceBuffer(commandQueues[index], flags, mappedData);
	}

	template<typename T>
	CLEvent CLContext::mapBuffer(unsigned int index, CLBuffer<T> buffer, cl_map_flags flags, size_t offset, size_t elemCount, T ** mappedData) const {

		return buffer.mapDeviceBuffer(commandQueues[index], flags, offset, elemCount, mappedData);
	}

	template<typename T>
	CLEvent CLContext::unmapBuffer(unsigned int idx, CLBuffer<T> buffer, T * mappedData) const {
		return buffer.unmapDeviceBuffer(commandQueues[idx], mappedData);
	}






}




#endif


