
#include <string.h>
#include <cstring> 
#include <sstream>
#include <vector>
#include <cgicc/CgiEnvironment.h>
#include <cgicc/Cgicc.h>

#include "application.hh"


namespace mias
{

void BodyApplication::programs_stove(std::ostream& out)
{
	if(params.step == steping::Eat::none and params.order == -1)
	{
		select_order(out);
	}
	else if(params.step == steping::Eat::none and params.order > 0 and not params.restoring)
	{
		select_item(out);
	}	
	else if(params.step == steping::Eat::accepted and params.order > 0 and not params.restoring)
	{
		accepted_item(out);
	}
	else if(params.restoring)
	{
		restoring_order(out);
	}
}

void BodyApplication::panel_stove(std::ostream& out) 
{
	out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi\"></a></div>\n";
	out << "\t\t\t<div class=\"space\"></div>\n";	
	//out << "Step : " << params.order  << "\n";	
	if(params.step == steping::Eat::none and params.order == -1)
	{
		select_order_restore(out);
	}
	else if(params.restoring and params.step == steping::Eat::none and params.order > 0)
	{
		select_step_restore(out);
	}
	else if(params.restoring and params.step > steping::Eat::none and params.step < steping::Eat::finalized and params.order > 0)
	{
		select_item_restore(out);
	}
}

}
