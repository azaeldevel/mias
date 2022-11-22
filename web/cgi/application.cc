
#include <string.h>
#include <cstring> 
#include <sstream>
#include <vector>
#include <cgicc/CgiEnvironment.h>
#include <cgicc/Cgicc.h>

#include "application.hh"


namespace mps
{
	GetParams::GetParams()
	{
		build();
	}
	
	
	const char* GetParams::find(const char* k) const
	{
		const_iterator it = std::map<std::string, std::string>::find(k);
		
		if(it != end()) return it->second.c_str();
		
		return NULL;
	}
	void GetParams::build()
	{
		std::string qs, str,param_pair,param,name,value,param_element;
		qs = getenv("QUERY_STRING");
		std::stringstream sqs(qs);
		
		//std::cout << qs << "\n";
		std::getline(sqs,str,'?');
		//std::cout << "GetParams::build str "<< str << "\n<br>";
		std::stringstream sparam_list(str),sparam_pair;
		while(std::getline(sparam_list,param_pair,'&'))
		{
			sparam_pair.clear();
			name="";
			value="";
			sparam_pair << param_pair;
			//std::cout << "GetParams::build param_pair "<< param_pair << "\n<br>";
			if(std::getline(sparam_pair,name,'=')) std::getline(sparam_pair,value,'=');
			//std::cout << " name : " << name << "\n";
			//std::cout << " value : " << value << "\n";		
			insert(make_pair(name,value));
		}
	}
	
	
	
}





namespace mias
{
	
	GetParams::GetParams()
	{
		const char* param = find("station");
		if(param)
		{
			station = mias::Station::pizza;
		}
		else
		{
			station = mias::Station::none;
		}
		
		param = find("order");
		if(param)
		{
			if(strcmp(param,"next") == 0)
			{
				order = 0;
			}
			else
			{
				order = std::stol(param);
			}
		}
		else
		{
			order = -1;
		}
		
		param = find("step");
		if(param)
		{
			to_step(param,(steping::Pizza&)step);
		}
		
		param = find("item");
		if(param)
		{
			item = std::stol(param);
		}
		
		param = find("restoring");
		if(param)
		{
			restoring = true;
		}
		else
		{
			restoring = false;
		}
		
	}
	
	
	
	
	
BodyApplication::BodyApplication(const GetParams& p) : params(p)
{
}
void BodyApplication::programs(std::ostream& out) 
{
	switch(params.station)
	{
		case Station::pizza:
			programs_pizza(out);
			break;
		default:
			out << "\t\t\t<div id=\"pizza\"><a href=\"application.cgi?station=pizza&step=none\">Pizza</a></div>\n";
			out << "\t\t\t<div id=\"stove\"><a href=\"application.cgi?station=stove&step=none\">Estufa</a></div>\n";
			out << "\t\t\t<div id=\"oven\"><a href=\"application.cgi?station=oven&step=none\">Horno</a></div>\n";
	}
}
void BodyApplication::programs_pizza(std::ostream& out)
{
	//std::cout << "step : " << params.step << "\n";
	/*
	for(auto const & p : params)
	{
		std::cout << "param : " << p.first << " -> " << p.second << "\n";
	}
	*/
	if(params.step == (short)steping::Pizza::none and params.order == -1)
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
					if(lstService)
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
				}
				out << "\t\t\t\t</select>\n";
			}
			else
			{
				out << "\t\t\t\t<label ><b>Orden:</b></label><br>Ninugna\n";
			}
		}
		out << "\t\t\t</div>\n";
	}
	else if(params.step == (short)steping::Pizza::none and params.order > 0 and not params.restoring)
	{
		out << "\t\t\t<div id=\"order\">\n";
		{
			out << "\t\t\t\tOrden : " << params.order << " \n";
		}
		out << "\t\t\t</div>\n";
		
		out << "\t\t\t<div id=\"item\">\n";
		{
			std::string where = "operation = ";
			where += std::to_string(params.order);
			where += " and step =";
			where += std::to_string((short)steping::Pizza::created);
			std::vector<muposysdb::Progress*>* lstProgress = muposysdb::Progress::select(*connDB,where,0,'A');
			if(lstProgress->size() > 0)
			{
				out << "\t\t\t\t<label for=\"item\"><b>Pizza:</b></label><br>\n";
				out << "\t\t\t\t<select name=\"item\" id=\"itemList\" onchange=\"acceptinghref()\">\n";
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
			else
			{
				out << "\t\t\t\t<label ><b>Pizza:</b></label><br>Ninugna\n";
			}
		}
		out << "\t\t\t</div>\n";
	}	
	else if(params.step == (short)steping::Pizza::accepted and not params.restoring)
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
			out << "\t\t\t\t<label><b>Pizza:</b></label><br>" << itemNumber << "\n";
		}
		out << "\t\t\t</div>\n";
	}
	else if(params.restoring)
	{
		out << "\t\t\t<div id=\"order\">\n";
		{
			out << "\t\t\t\tOrden : " << params.order << " \n";
		}
		out << "\t\t\t</div>\n";
	}
	
}
void BodyApplication::panel(std::ostream& out) 
{	
	switch(params.station)
	{
		case Station::pizza:
			panel_pizza(out);
			break;
		default:
			out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi\"></a></div>\n";
			out << "\t\t\t<div class=\"space\"></div>\n";	
			out << "\t\t\t<div id=\"system\"><a href=\"system.html\"></a></div>\n";	
	}
}
void BodyApplication::panel_pizza(std::ostream& out) 
{	
	out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi\"></a></div>\n";
	out << "\t\t\t<div class=\"space\"></div>\n";	
	out << "\t\t\t<div id=\"system\"><a href=\"system.html\"></a></div>\n";	
	//out << "Step : " << params.order  << "\n";	
	if(params.step == (short)steping::Pizza::none and params.order == -1)
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
	else if(params.restoring and params.step == (short)steping::Pizza::none and params.order > 0)
	{
		out << "\t\t\t<div id=\"restoreStep\">\n";
		{
			out << "\t\t\t\t<select name=\"restoreStep\" id=\"restoreStepList\" onchange=\"restoreStephref()\">\n";
			{
				out << "\t\t\t\t\t<option value=\"next\">next</option>\n";	
				for(short i = (short) steping::Pizza::accept; i < (short) steping::Pizza::finalized; i++ )
				{
					out << "\t\t\t\t\t<option value=\"" << to_string((steping::Pizza)i) <<  "\">" << to_text((steping::Pizza)i) << "</option>\n";					
				}
			}
			out << "\t\t\t\t</select>\n";
		}
		out << "\t\t\t</div>\n";
	}
	else if(params.restoring and params.step > (short)steping::Pizza::none and params.step < (short)steping::Pizza::finalized and params.order > 0)
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
std::ostream& BodyApplication::operator >> (std::ostream& out)
{
	/*if(params.step.compare(step(steping::Pizza::accept)) == 0)
	{
		return out;
	}*/
	
	out << "\t<div id=\"menu\">\n";		

		out << "\t\t<div id=\"panel\">\n";
			this->panel(out);
		out << "\t\t</div>\n";	

		out << "\t\t<div class=\"space\"></div>\n";

		out << "\t\t<div id=\"programs\">\n";
			this->programs(out);
		out << "\t\t</div>\n";

	out << "\t</div>\n";
	if(params.station != Station::none)
	{
		out << "\t<div id=\"work\">\n";		
		{
			muposysdb::CatalogItem* item = NULL;
			std::string where = "operation = ";
			where += std::to_string(params.order);
			//out << " where : " << where << "\n";
			std::vector<muposysdb::Progress*>* lstProgress = muposysdb::Progress::select(*connDB,where,0,'A');
			if(lstProgress) if(lstProgress->size() > 0)
			{
				for(auto p : *lstProgress)
				{
					p->getStocking().downItem(*connDB);
					p->getStocking().getItem().downNumber(*connDB);
					p->getStocking().getItem().downBrief(*connDB);
					if(p->getStocking().getStocking() == params.item)
					{
						item = new muposysdb::CatalogItem(p->getStocking().getItem());
						//item->downItem(*connDB);
						//item->downNumber(*connDB);
						item->downBrief(*connDB);						
					}
				}
				for(auto p : *lstProgress)
				{
					delete p;
				}
				delete lstProgress;
			}
			out << "\t<div id=\"brief\">\n";		
			{
				out << "\t<div id=\"itemBrief\">\n";		
				{
					if(item)
					{
						out << "\t" << to_text(params.station) << " : "<< item->getBrief() << "<br>\n";
					}
				}
				out << "\t</div>\n";
			}
			out << "\t</div>\n";
			delete item;
		}
		out << "\t</div>\n";
		
		out << "\t<div id=\"commands\">\n";	
		{
			out << "\t<div id=\"left\">\n";		
			{
				switch((steping::Pizza)params.step)
				{
					case steping::Pizza::none: 
						
						break;
					case steping::Pizza::accept:
						
						break;
					case steping::Pizza::accepted:
						
						break;
					case steping::Pizza::preparing: 
						
						break;
					case steping::Pizza::prepared: 
						
						break;
					case steping::Pizza::baking: 
						
						break;
					case steping::Pizza::baked: 
						
						break;
					case steping::Pizza::finalized:
						
						break;	
					case steping::Pizza::cancel:
						
						break;
				}
			}
			out << "\t</div>\n";
			if(params.step > (short)steping::Pizza::accept)
			{
				out << "\t<div id=\"right\">\n";	
				switch((steping::Pizza)params.step)
				{
					case steping::Pizza::none: 
						
						break;
					case steping::Pizza::accept:
						
						break;
					case steping::Pizza::accepted:
						out << "\t<a id=\"cmdBaking\" class=\"cmd\" onclick=\"toBaking()\">Hornear</a>";
						out << "\t<a id=\"cmdPreparing\" class=\"cmd\" onclick=\"toPrepare()\">Preparar</a>";
						break;
					case steping::Pizza::preparing: 
						out << "\t<a id=\"cmdBaking\" class=\"cmd\" onclick=\"toBaking()\">Hornear</a>";
						out << "\t<a id=\"cmdPrepared\" class=\"cmd\" onclick=\"toPrepared()\">Preparada</a>";
						break;
					case steping::Pizza::prepared: 
						out << "\t<a id=\"cmdFinalized\" class=\"cmd\" onclick=\"toFinalized()\">Completada</a>";	
						out << "\t<a id=\"cmdBaking\" class=\"cmd\" onclick=\"toBaking()\">Hornear</a>";
						break;
					case steping::Pizza::baking: 
						out << "\t<a id=\"cmdFinalized\" class=\"cmd\" onclick=\"toFinalized()\">Completada</a>";	
						out << "\t<a id=\"cmdBaked\" class=\"cmd\" onclick=\"toBaked()\">Horneada</a>";
						break;
					case steping::Pizza::baked: 
						out << "\t<a id=\"cmdFinalized\" class=\"cmd\" onclick=\"toFinalized()\">Completada</a>";	
						break;
					case steping::Pizza::finalized:
						out << "\t<a id=\"cmdBegin\" class=\"cmd\" onclick=\"toBegin()\">Inicio</a>";
						break;	
					case steping::Pizza::cancel:
						
						break;
				}
				out << "\t</div>\n";
			}
		}
		out << "\t</div>\n";
	}
	return out;
}
void BodyApplication::set(mps::Connector& c)
{
	connDB = &c;
}




Application::~Application()
{
}
void Application::init()
{
	head.css("css/mias.css");	
	head.addscript("js/mias.js");
	((BodyApplication&)*body).set(connDB);
}
Application::Application(BodyApplication& b,const GetParams& p) : params(p),mps::Application(b)
{
	head.title = "Multi-Porpuse Software System";
	init();
}
Application::Application(BodyApplication& b,const std::string& t,const GetParams& p) : params(p),mps::Application(b,t)
{
	init();
}
/*std::ostream& Application::operator >> (std::ostream& out)
{
	mps::Application::operator >>(out);
	
	return out;
}*/
int Application::main(std::ostream& out)
{
	mps::contenttype(out,"text","html");
	
	if(not has_session())
	{
		head.redirect(0,"login.html?failure");
		head >> out;
		return EXIT_SUCCESS;
	}
	
	switch((steping::Pizza)params.step)
	{
		case steping::Pizza::none:
			
			break;
		case steping::Pizza::accept:
		{
			//out << "Procesando solicitud de acceptacion...\n";
			long order = pizza_accepting();
			cgicc::Cgicc cgi;
			//cgicc::CgiInput:
			const cgicc::CgiEnvironment& cgienv = cgi.getEnvironment();
			
			std::string strgets = "station=";
			strgets += to_string(params.station);
			strgets += "&order=";
			if(params.order == 0)
			{
				strgets += std::to_string(order);
			}
			else
			{
				strgets += std::to_string(params.order);
			}
			strgets += "&step=accepted";
			strgets += "&item=";
			strgets += std::to_string(params.item);
			std::string url = "application.cgi?";
			url += strgets;
			head.redirect(0,url.c_str());
			//out << "url : " << url << "<br>\n";
			//out << "done<br>\n";
			head >> out;
			connDB.commit();
			return EXIT_SUCCESS;
		}
		case steping::Pizza::accepted:
			pizza_steping(steping::Pizza::accepted);
			break;
		case steping::Pizza::prepare:
		{
			//out << "Procesando solicitud de acceptacion...\n";
			pizza_steping(steping::Pizza::prepare);
			cgicc::Cgicc cgi;
			//cgicc::CgiInput:
			const cgicc::CgiEnvironment& cgienv = cgi.getEnvironment();
			
			std::string strgets = "station=";
			strgets += to_string(params.station);
			strgets += "&order=";
			strgets += std::to_string(params.order);
			strgets += "&step=preparing";
			strgets += "&item=";
			strgets += std::to_string(params.item);
			std::string url = "application.cgi?";
			url += strgets;
			head.redirect(0,url.c_str());
			//out << "url : " << url << "<br>\n";
			//out << "done<br>\n";
			head >> out;
			connDB.commit();
			return EXIT_SUCCESS;
		}
		case steping::Pizza::preparing:
			pizza_steping(steping::Pizza::prepared);
			connDB.commit();
			break;
		case steping::Pizza::prepared:
			pizza_steping(steping::Pizza::prepared);
			connDB.commit();
			break;
		case steping::Pizza::bake:
			pizza_steping(steping::Pizza::bake);
			connDB.commit();
			break;
		case steping::Pizza::baking:
			pizza_steping(steping::Pizza::baking);
			connDB.commit();
			break;
		case steping::Pizza::baked:
			pizza_steping(steping::Pizza::baked);
			connDB.commit();
			break;
		case steping::Pizza::finalized:
			pizza_steping(steping::Pizza::finalized);
			connDB.commit();
			break;
		case steping::Pizza::cancel:
			pizza_steping(steping::Pizza::cancel);
			connDB.commit();
			break;
	}
	
	(*this) >> out;

	return EXIT_SUCCESS;
}


/*
void params_get(std::map<std::string, std::string>& lst)
{
	std::string qs, str,param_pair,param,name,value,param_element;
	qs = getenv("QUERY_STRING");
	std::stringstream sqs(qs);
	
	//std::cout << qs << "\n";
	std::getline(sqs,str,'?');
	//std::cout << str << "\n";
	std::stringstream sparam_list(str),sparam_pair;
	while(std::getline(sparam_list,param_pair,'&'))
	{
		sparam_pair << param_pair;
		std::getline(sparam_pair,name,'=');
		//std::cout << " name : " << name << "\n";
		std::getline(sparam_pair,value,'=');
		//std::cout << " value : " << value << "\n";		
		lst.insert(make_pair(name,value));
	}
}*/


long Application::pizza_accepting()
{
	long order = params.order;
	std::string where = "step = ";
	where += std::to_string((int)ServiceStep::created);
	if(params.order > 0)
	{
		where += " and operation = ";
		where += std::to_string(params.order);
	}
	std::vector<muposysdb::MiasService*>* lstService = muposysdb::MiasService::select(connDB,where,1,'A');
	if(lstService)
	{
		for(auto s : *lstService)
		{
			s->downStep(connDB);
		}
		
		if(lstService->size() == 1)
		{
			order = lstService->front()->getOperation().getOperation().getID();
			lstService->front()->upStep(connDB,(short)ServiceStep::working);
		}
		else
		{
			//throw Exception((unsigned int)Exception::DB_READ_FAIL,__FILE__,__LINE__);
		}
		
		for(auto s : *lstService)
		{
			delete s;
		}
		delete lstService;
	}
	
	pizza_steping(steping::Pizza::accept);
		
	return order;
}
/*void Application::pizza_preparing()
{
	std::string whereItem = "operation = ";
	whereItem += std::to_string(params.order);	
	whereItem += " and stocking = ";
	whereItem += std::to_string(params.item);
	std::vector<muposysdb::Progress*>* lstItem = muposysdb::Progress::select(connDB,whereItem,0,'A');
	if(lstItem)
	{
		if(lstItem->size() == 1)
		{
			lstItem->front()->upStep(connDB,(short)steping::Pizza::preparing);
		}
		else
		{
			//throw Exception((unsigned int)Exception::DB_READ_FAIL,__FILE__,__LINE__);
		}
		
		for(auto s : *lstItem)
		{
			delete s;
		}
		delete lstItem;		
	}
	connDB.commit();
}*/
void Application::pizza_steping(steping::Pizza to_step)
{
	short updated;
	long order = params.order;
	std::string where;
	where += "operation = ";
	where += std::to_string(params.order);
	std::vector<muposysdb::MiasService*>* lstService = muposysdb::MiasService::select(connDB,where,1,'A');
	if(lstService)
	{
		for(auto s : *lstService)
		{
			s->downUpdated(connDB);
		}
		if(lstService->size() == 1)
		{
			updated = lstService->front()->getUpdated();
			lstService->front()->upUpdated(connDB,updated + 1);
		}
		else
		{
			//throw Exception((unsigned int)Exception::DB_READ_FAIL,__FILE__,__LINE__);
		}
		
		for(auto s : *lstService)
		{
			delete s;
		}
		delete lstService;
	}
	
	
	std::string whereItem = "operation = ";
	whereItem += std::to_string(params.order);	
	whereItem += " and stocking = ";
	whereItem += std::to_string(params.item);
	std::vector<muposysdb::Progress*>* lstItem = muposysdb::Progress::select(connDB,whereItem,0,'A');
	if(lstItem)
	{
		if(lstItem->size() == 1)
		{
			lstItem->front()->upStep(connDB,(short)to_step);
		}
		else
		{
			//throw Exception((unsigned int)Exception::DB_READ_FAIL,__FILE__,__LINE__);
		}
		
		for(auto s : *lstItem)
		{
			delete s;
		}
		delete lstItem;		
	}
}

}
