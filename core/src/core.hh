
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
		salad,
	};
	
	namespace steping
	{
		enum class Pizza
		{
			none,
			created,
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


const char* to_string(steping::Pizza);
const char* to_text(steping::Pizza);
const char* to_string(Station s);
const char* to_string(ServiceStep s);
const char* to_text(ServiceStep s);
void to_step(const char* str, steping::Pizza& step);

}

#endif
