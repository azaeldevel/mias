
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
		delivered,
		cancel,
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
			prepare,
			preparing,
			prepared,
			bake,
			baking,//en el horno
			baked,
			finalized,
			cancel,
		};
		
		
	}
}

#endif
