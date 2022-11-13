
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
	
	enum class Station
	{
		none,
		pizza,
		stove,
		oven,
	};
	
	namespace steping
	{
		enum class Pizza
		{
			none,
			accept,
			accepted,
			preparing,
			prepared,
			baking,//en el horno
			baked,
			finalized,
		};
		
		
	}
}

#endif
