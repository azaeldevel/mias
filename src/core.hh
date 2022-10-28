
#ifndef MUPOSYS_CORE_CORE_HH
#define MUPOSYS_CORE_CORE_HH

namespace mps
{
	namespace steps
	{
		enum class Orden
		{
			none,
			created,
			paid,
			cooking,
			ready,
			finalized,
		};
		enum class Pizza
		{
			accepted,
			preparing,
			baking,
		};
		enum class Oven
		{
			joined,
			baking,
			cooked,
			extracted,
		};
		enum class Stove
		{
			accepted,
			preparing,
			cooking,
			extracted,
		};
	}
}

#endif