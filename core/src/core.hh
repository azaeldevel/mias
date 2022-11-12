
#ifndef MIAS_CORE_CORE_HH
#define MIAS_CORE_CORE_HH

namespace mias
{
	enum class ServiceStep
	{
		none,
		created,
		working,
		retarded,
		cooked,
		waiting,
		delivered
	};
}

#endif
