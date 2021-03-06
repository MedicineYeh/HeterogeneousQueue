
#ifndef _CE_BUFFER_HPP_
#define _CE_BUFFER_HPP_

#include "CE_common.hpp"


namespace CE {

	class CE_API Buffer
	{
	public:

		virtual size_t getSize() const = 0;

		Buffer() = default;
		Buffer(Buffer const&) = delete;
		Buffer& operator = (Buffer const&) = delete;

		// check this !
		virtual ~Buffer() = default;

	};

}





#endif


