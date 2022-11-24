
#include <string.h>
#include <cstring> 
#include <sstream>
#include <vector>
#include <cgicc/CgiEnvironment.h>
#include <cgicc/Cgicc.h>

#include "application.hh"


namespace mias
{

void BodyApplication::programs_pizza(std::ostream& out)
{
	//std::cout << "step : " << params.step << "\n";
	/*
	for(auto const & p : params)
	{
		std::cout << "param : " << p.first << " -> " << p.second << "\n";
	}
	*/
	if(params.step == (short)steping::Eat::none and params.order == -1)
	{
		select_order(out);
	}
	else if(params.step == (short)steping::Eat::none and params.order > 0 and not params.restoring)
	{
		select_item(out);
	}	
	else if(params.step == (short)steping::Eat::accepted and params.order > 0 and not params.restoring)
	{
		accepted_item(out);
	}
	else if(params.restoring)
	{
		restoring_order(out);
	}
}

void BodyApplication::panel_pizza(std::ostream& out) 
{
	out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi\"></a></div>\n";
	out << "\t\t\t<div class=\"space\"></div>\n";	
	//out << "Step : " << params.order  << "\n";	
	if(params.step == (short)steping::Eat::none and params.order == -1)
	{
		out << "\t\t\t<div id=\"restoreOrder\">\n";
		{
			std::string where = "step > ";
			where += std::to_string((int)ServiceStep::created);
			where += " and step < ";
			where += std::to_string((int)ServiceStep::delivered);
			std::vector<muposysdb::MiasService*>* lstService = muposysdb::MiasService::select(*connDB,where,0,'A');
			if(lstService) if(lstService->size() > 0)
			{
				out << "\t\t\t\t<label for=\"order\"><b>Orden:</b></label><br>\n";
				out << "\t\t\t\t<select name=\"restoreOrder\" id=\"restoreOrderList\" onchange=\"restoreOrderhref()\">\n";
				{
					out << "\t\t\t\t\t<option value=\"next\">next</option>\n";
					for(auto p : *lstService)
					{
						p->downName(*connDB);
						out << "\t\t\t\t\t<option value=\"" << p->getOperation().getOperation().getID() << "\">" << p->getOperation().getOperation().getID() << "</option>\n";
					}
					for(auto p : *lstService)
					{
						delete p;
					}
					delete lstService;
				}
				out << "\t\t\t\t</select>\n";
			}
		}
		out << "\t\t\t</div>\n";
	}
	else if(params.restoring and params.step == (short)steping::Eat::none and params.order > 0)
	{
		out << "\t\t\t<div id=\"restoreStep\">\n";
		{
			out << "\t\t\t\t<select name=\"restoreStep\" id=\"restoreStepList\" onchange=\"restoreStephref()\">\n";
			{
				out << "\t\t\t\t\t<option value=\"next\">next</option>\n";	
				for(short i = (short) steping::Eat::accept; i < (short) steping::Eat::finalized; i++ )
				{
					out << "\t\t\t\t\t<option value=\"" << to_string((steping::Eat)i) <<  "\">" << to_text((steping::Eat)i) << "</option>\n";					
				}
			}
			out << "\t\t\t\t</select>\n";
		}
		out << "\t\t\t</div>\n";
	}
	else if(params.restoring and params.step > (short)steping::Eat::none and params.step < (short)steping::Eat::finalized and params.order > 0)
	{
		out << "\t\t\t<div id=\"restoreItem\">\n";
		{
			std::string where = "operation = ";
			where += std::to_string(params.order);
			where += " and step = ";
			where += std::to_string(params.step);
			out << " where : " << where << "\n";
			std::vector<muposysdb::Progress*>* lstProgress = muposysdb::Progress::select(*connDB,where,0,'A');
			if(lstProgress) if(lstProgress->size() > 0)
			{
				out << "\t\t\t\t<select name=\"restoreItemName\" id=\"restoreItemList\" onchange=\"toContinue()\">\n";
				{
						out << "\t\t\t\t\t<option value=\"next\">next</option>\n";
						for(auto p : *lstProgress)
						{
							p->getStocking().downItem(*connDB);
							p->getStocking().getItem().downNumber(*connDB);
							p->getStocking().getItem().downBrief(*connDB);
							out << "\t\t\t\t\t<option value=\"" << p->getStocking().getStocking() << "\">" << p->getStocking().getItem().getBrief() << "</option>\n";
						}
						for(auto p : *lstProgress)
						{
								delete p;
						}
						delete lstProgress;
				}
			out << "\t\t\t\t</select>\n";
			}
		}
		out << "\t\t\t</div>\n";
	}	
}

}
