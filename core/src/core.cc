
#include <string.h>
#include <string>


#include "core.hh"

namespace mias
{


	const char* to_string(steping::Eat s)
	{
		switch(s)
		{
			case steping::Eat::none: return "none";
			case steping::Eat::accept: return "accept";
			case steping::Eat::accepted: return "accepted";
			case steping::Eat::prepare: return "prepare";
			case steping::Eat::preparing: return "preparing";
			case steping::Eat::prepared: return "prepared";
			case steping::Eat::cook: return "cook";
			case steping::Eat::cooking: return "cooking";
			case steping::Eat::cooked: return "cooked";
			case steping::Eat::finalized: return "finalized";		
			case steping::Eat::cancel: return "cancel";	
		}
		
		return "unknow";
	}
	const char* to_text(steping::Eat s)
	{
		switch(s)
		{
			case steping::Eat::none: return "Ninguno";
			case steping::Eat::accept: return "Aceptar";
			case steping::Eat::accepted: return "Aceptado";
			case steping::Eat::prepare: return "Preparar";
			case steping::Eat::preparing: return "Preparando";
			case steping::Eat::prepared: return "Preparado";
			case steping::Eat::cook: return "Cocinar";
			case steping::Eat::cooking: return "Cocinando";
			case steping::Eat::cooked: return "Cocinando";
			case steping::Eat::finalized: return "Finalizado";		
			case steping::Eat::cancel: return "Cancel";
		}
		
		return "Unknow";
	}
	
	steping::Eat to_step(const char* s)
	{
		if(strcmp("none",s) == 0)
		{
			return steping::Eat::none;
		}
		else if(strcmp("accept",s) == 0)
		{
			return steping::Eat::accept;
		}
		else if(strcmp("accepted",s) == 0)
		{
			return steping::Eat::accepted;
		}
		else if(strcmp("prepare",s) == 0)
		{
			return steping::Eat::prepare;
		}
		else if(strcmp("preparing",s) == 0)
		{
			return steping::Eat::preparing;
		}
		else if(strcmp("prepared",s) == 0)
		{
			return steping::Eat::prepared;
		}
		else if(strcmp("cook",s) == 0)
		{
			return steping::Eat::cook;
		}
		else if(strcmp("cooking",s) == 0)
		{
			return steping::Eat::cooking;
		}
		else if(strcmp("cooked",s) == 0)
		{
			return steping::Eat::cooked;
		}
		else if(strcmp("finalized",s) == 0)
		{
			return steping::Eat::finalized;
		}
		else if(strcmp("cancel",s) == 0)
		{
			return steping::Eat::cancel;
		}
		
		return steping::Eat::none;
	}



	
	const char* to_string(steping::Pizza s)
	{
		switch(s)
		{
			case steping::Pizza::none: return "none";
			case steping::Pizza::accept: return "accept";
			case steping::Pizza::accepted: return "accepted";
			case steping::Pizza::prepare: return "prepare";
			case steping::Pizza::preparing: return "preparing";
			case steping::Pizza::prepared: return "prepared";
			case steping::Pizza::bake: return "bake";
			case steping::Pizza::baking: return "baking";
			case steping::Pizza::baked: return "baked";
			case steping::Pizza::finalized: return "finalized";		
			case steping::Pizza::cancel: return "cancel";	
		}
		
		return "unknow";
	}
	const char* to_text(steping::Pizza s)
	{
		switch(s)
		{
			case steping::Pizza::none: return "Ninguno";
			case steping::Pizza::accept: return "Aceptar";
			case steping::Pizza::accepted: return "Aceptado";
			case steping::Pizza::prepare: return "Preparar";
			case steping::Pizza::preparing: return "Preparando";
			case steping::Pizza::prepared: return "Preparado";
			case steping::Pizza::bake: return "Hornear";
			case steping::Pizza::baking: return "Horneando";
			case steping::Pizza::baked: return "Horneado";
			case steping::Pizza::finalized: return "Finalizado";		
			case steping::Pizza::cancel: return "Cancel";
		}
		
		return "Unknow";
	}
	const char* to_string(ServiceStep s)
	{
		switch(s)
		{
			case ServiceStep::none: return "none";
			case ServiceStep::created: return "created";
			case ServiceStep::working: return "working";
			case ServiceStep::retarded: return "retarded";
			case ServiceStep::cooked: return "cooked";
			case ServiceStep::waiting: return "waiting";
			case ServiceStep::delivered: return "delivered";
			case ServiceStep::cancel: return "cancel";
		}
		
		return "unknow";
	}
	const char* to_text(ServiceStep s)
	{
		switch(s)
		{
			case ServiceStep::none: return "Ninguno";
			case ServiceStep::created: return "Creado";
			case ServiceStep::working: return "En proceso";
			case ServiceStep::retarded: return "Retrasedo";
			case ServiceStep::cooked: return "Cocinando";
			case ServiceStep::waiting: return "Esperando";
			case ServiceStep::delivered: return "Entregado";
			case ServiceStep::cancel: return "Cancelado";
		}
		
		return "unknow";
	}
	const char* to_string(Station s)
	{
		switch(s)
		{
			case Station::none: return "none";	
			case Station::pizza: return "pizza";	
			case Station::stove: return "stove";	
			case Station::oven: return "oven";
		}
		
		return "unknow";
	}
	const char* to_text(Station s)
	{
		switch(s)
		{
			case Station::none: return "Ninguna";	
			case Station::pizza: return "Pizza";	
			case Station::stove: return "Estufa";	
			case Station::oven: return "Horno";
		}
		
		return "unknow";
	}
	void to_step(const char* str, steping::Pizza& step)
	{
		if(strcmp(str,"none") == 0)
		{
			step = steping::Pizza::none;
		}
		else if(strcmp(str,"accept") == 0)
		{
			step = steping::Pizza::accept;
		}
		else if(strcmp(str,"accepted") == 0)
		{
			step = steping::Pizza::accepted;
		}
		else if(strcmp(str,"prepare") == 0)
		{
			step = steping::Pizza::prepare;
		}
		else if(strcmp(str,"preparing") == 0)
		{
			step = steping::Pizza::preparing;
		}
		else if(strcmp(str,"prepared") == 0)
		{
			step = steping::Pizza::prepared;
		}
		else if(strcmp(str,"bake") == 0)
		{
			step = steping::Pizza::bake;
		}
		else if(strcmp(str,"baking") == 0)
		{
			step = steping::Pizza::baking;
		}
		else if(strcmp(str,"baked") == 0)
		{
			step = steping::Pizza::baked;
		}
		else if(strcmp(str,"finalized") == 0)
		{
			step = steping::Pizza::finalized;
		}
		else if(strcmp(str,"cancel") == 0)
		{
			step = steping::Pizza::cancel;
		}
	}

}