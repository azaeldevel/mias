
#include <string.h>
#include <cstring> 
#include <sstream>
#include <vector>
#include <cgicc/CgiEnvironment.h>
#include <cgicc/Cgicc.h>

#include "application.hh"


namespace mias
{

	

void BodyApplication::select_order(std::ostream& out)
{
		out << "\t\t\t<div id=\"order\">\n";
		{
			std::string where = "step >= " ;
			where += std::to_string((int)ServiceStep::created);
			where += " and step < ";
			where += std::to_string((int)ServiceStep::delivered);
			std::vector<muposysdb::MiasService*>* lstService = muposysdb::MiasService::select(*connDB,where,0,'A');
			if(lstService->size() > 0)
			{
				out << "\t\t\t\t<label for=\"order\"><b>Orden:</b></label><br>\n";
				out << "\t\t\t\t<select name=\"order\" id=\"orderList\" onchange=\"accepthref()\">\n";
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
			else
			{
				delete lstService;
				out << "\t\t\t\t<label ><b>Orden:</b></label><br>Ninguna\n";
			}
		}
		out << "\t\t\t</div>\n";
}
void BodyApplication::select_item(std::ostream& out)
{
		out << "\t\t\t<div id=\"order\">\n";
		{
			out << "\t\t\t\t<label ><b>Orden:</b></label><br>" << params.order << "\n";
		}
		out << "\t\t\t</div>\n";
		
		out << "\t\t\t<div id=\"item\">\n";
		{
			std::string where = "operation = ";
			where += std::to_string(params.order);
			where += " and step =";
			where += std::to_string((short)steping::Eat::created);
			std::vector<muposysdb::Progress*>* lstProgress = muposysdb::Progress::select(*connDB,where,0,'A');
			if(lstProgress->size() > 0)
			{
				out << "\t\t\t\t<label for=\"item\"><b>";
				out << to_text(params.station);
				out << ":</b></label><br>\n";
				out << "\t\t\t\t<select name=\"item\" id=\"itemList\" onchange=\"acceptinghref()\">\n";
				{
						out << "\t\t\t\t\t<option value=\"next\">next</option>\n";
						for(auto p : *lstProgress)
						{
							p->getStocking().downItem(*connDB);
							p->getStocking().getItem().downNumber(*connDB);
							p->getStocking().getItem().downBrief(*connDB);
							p->getStocking().getItem().downStation(*connDB);
							if((Station)p->getStocking().getItem().getStation() == params.station) out << "\t\t\t\t\t<option value=\"" << p->getStocking().getStocking() << "\">" << p->getStocking().getItem().getBrief() << "</option>\n";
						}
						for(auto p : *lstProgress)
						{
								delete p;
						}
						delete lstProgress;
				}
				out << "\t\t\t\t</select>\n";
			}
			else
			{
				delete lstProgress;
				out << "\t\t\t\t<label ><b>";
				out << to_text(params.station);
				out << ":</b></label><br>Ninguna\n";
			}
		}
		out << "\t\t\t</div>\n";
}
void BodyApplication::accepted_item(std::ostream& out)
{
		out << "\t\t\t<div id=\"order\">\n";
		{
			out << "\t\t\t\t<label><b>Orden:</b></label><br>" << params.order << "\n";
		}
		out << "\t\t\t</div>\n";
		out << "\t\t\t<div id=\"item\">\n";
		{
			std::string itemNumber;
			std::string where = "operation = ";
			where += std::to_string(params.order);
			//out << " where : " << where << "\n";
			std::vector<muposysdb::Progress*>* lstProgress = muposysdb::Progress::select(*connDB,where,0,'A');
			if(lstProgress->size() > 0)
			{
				//if(lstProgress->size() > 1) break;
				for(auto p : *lstProgress)
				{
					p->getStocking().downItem(*connDB);
					p->getStocking().getItem().downNumber(*connDB);
					//p->getStocking().getItem().downBrief(*connDB);
					//out << "\t\t\t\titem : " << p->getStocking().getItem().getItem().getID() << "\n";
					//out << "\t\t\t\titem : " <<  params.item << "\n";
					if(p->getStocking().getStocking() == params.item) 
					{
						//out << "\t\t\t\titem : x\n";
						itemNumber = p->getStocking().getItem().getNumber();
						break;
					}
				}
				for(auto p : *lstProgress)
				{
					delete p;
				}
				delete lstProgress;
			}
			out << "\t\t\t\t<label><b>";
			out << to_text(params.station);
			out << ":</b></label><br>" << itemNumber << "\n";
		}
		out << "\t\t\t</div>\n";
}
void BodyApplication::restoring_order(std::ostream& out)
{
		out << "\t\t\t<div id=\"order\">\n";
		{
			out << "\t\t\t\tOrden : " << params.order << " \n";
		}
		out << "\t\t\t</div>\n";	
}
void BodyApplication::select_order_restore(std::ostream& out)
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
						//p->downName(*connDB);
						//p->getOperation().getStocking().downItem(*connDB);
						//p->getStocking().getItem().downNumber(*connDB);
						//p->getStocking().getItem().downBrief(*connDB);
						//p->getOperation().getStocking().getItem().downStation(*connDB);
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
void BodyApplication::select_step_restore(std::ostream& out)
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

void BodyApplication::select_item_restore(std::ostream& out)
{
		out << "\t\t\t<div id=\"restoreItem\">\n";
		{
			std::string where = "operation = ";
			where += std::to_string((int)params.order);
			where += " and step = ";
			where += std::to_string((int)params.step);
			//out << " where : " << where << "\n";
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
