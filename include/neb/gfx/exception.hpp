#include <exception>

struct exception: std::exception
	{
		virtual const char *		what()
		{
			return "graphics exception";
		}
	};

