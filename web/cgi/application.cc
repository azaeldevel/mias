
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
		if(not std::getline(sqs,str,'?')) return;
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
			station = to_station(param);
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
			step = to_step(param);
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
	if(params.station > Station::none)
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
	else
	{
		out << "\t\t\t<div id=\"pizza\"><a href=\"application.cgi?station=pizza&step=none\">Pizza</a></div>\n";
		out << "\t\t\t<div id=\"stove\"><a href=\"application.cgi?station=stove&step=none\">Estufa</a></div>\n";
		out << "\t\t\t<div id=\"oven\"><a href=\"application.cgi?station=oven&step=none\">Horno</a></div>\n";
	}
}

void BodyApplication::panel(std::ostream& out) 
{	

	//out << "Step : " << params.order  << "\n";	
	if(params.station > Station::none)
	{
		out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi\"></a></div>\n";
		out << "\t\t\t<div class=\"space\"></div>\n";	
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
	else
	{
		out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi\"></a></div>\n";
		out << "\t\t\t<div class=\"space\"></div>\n";	
		out << "\t\t\t<div id=\"system\"><a href=\"system.html\"></a></div>\n";	
	}
}
std::ostream& BodyApplication::print(std::ostream& out)
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
				switch((steping::Eat)params.step)
				{
					case steping::Eat::none: 
						
						break;
					case steping::Eat::accept:
						
						break;
					case steping::Eat::accepted:
						
						break;
					case steping::Eat::preparing: 
						
						break;
					case steping::Eat::prepared: 
						
						break;
					case steping::Eat::cooking: 
						
						break;
					case steping::Eat::cooked: 
						
						break;
					case steping::Eat::finalized:
						
						break;	
					case steping::Eat::cancel:
						
						break;
				}
			}
			out << "\t</div>\n";
			out << "\t<div id=\"right\">\n";	
			{
				switch((steping::Eat)params.step)
				{
					case steping::Eat::none: 
						out << "\t<a id=\"cmdBegin\" class=\"cmd\" onclick=\"toBegin()\">Inicio</a>";
						break;
					case steping::Eat::accept:
						
						break;
					case steping::Eat::accepted:
						out << "\t<a id=\"cmdCooking\" class=\"cmd\" onclick=\"toCooking()\">" << to_text(steping::Eat::cooking) << "</a>";
						out << "\t<a id=\"cmdPreparing\" class=\"cmd\" onclick=\"toPrepare()\">Preparar</a>";
						break;
					case steping::Eat::preparing: 
						out << "\t<a id=\"cmdCooking\" class=\"cmd\" onclick=\"toCooking()\">" << to_text(steping::Eat::cooking) << "</a>";
						out << "\t<a id=\"cmdPrepared\" class=\"cmd\" onclick=\"toPrepared()\">Preparada</a>";
						break;
					case steping::Eat::prepared: 
						out << "\t<a id=\"cmdFinalized\" class=\"cmd\" onclick=\"toFinalized()\">Completada</a>";	
						out << "\t<a id=\"cmdCooking\" class=\"cmd\" onclick=\"toCooking()\">" << to_text(steping::Eat::cooking) << "</a>";
						break;
					case steping::Eat::cooking: 
						out << "\t<a id=\"cmdFinalized\" class=\"cmd\" onclick=\"toFinalized()\">Completada</a>";	
						out << "\t<a id=\"cmdCooked\" class=\"cmd\" onclick=\"toCooked()\">" << to_text(steping::Eat::cooked) << "</a>";
						break;
					case steping::Eat::cooked: 
						out << "\t<a id=\"cmdFinalized\" class=\"cmd\" onclick=\"toFinalized()\">Completada</a>";	
						break;
					case steping::Eat::finalized:
						out << "\t<a id=\"cmdBegin\" class=\"cmd\" onclick=\"toBegin()\">Inicio</a>";
						break;	
					case steping::Eat::cancel:
						
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
		head.print(out);
		return EXIT_SUCCESS;
	}
	
	switch((steping::Eat)params.step)
	{
		case steping::Eat::none:
			
			break;
		case steping::Eat::accept:
		{
			//out << "Procesando solicitud de acceptacion...\n";
			long order = accepting();
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
			head.print(out);
			connDB.commit();
			return EXIT_SUCCESS;
		}
		case steping::Eat::accepted:
			steping(steping::Eat::accepted);
			break;
		case steping::Eat::prepare:
		{
			//out << "Procesando solicitud de acceptacion...\n";
			steping(steping::Eat::prepare);
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
			head.print(out);
			connDB.commit();
			return EXIT_SUCCESS;
		}
		case steping::Eat::preparing:
			steping(steping::Eat::prepared);
			connDB.commit();
			break;
		case steping::Eat::prepared:
			steping(steping::Eat::prepared);
			connDB.commit();
			break;
		case steping::Eat::cook:
			steping(steping::Eat::cook);
			connDB.commit();
			break;
		case steping::Eat::cooking:
			steping(steping::Eat::cooking);
			connDB.commit();
			break;
		case steping::Eat::cooked:
			steping(steping::Eat::cooked);
			connDB.commit();
			break;
		case steping::Eat::finalized:
			steping(steping::Eat::finalized);
			connDB.commit();
			break;
		case steping::Eat::cancel:
			steping(steping::Eat::cancel);
			connDB.commit();
			break;
	}
	
	this->print(out);

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


long Application::accepting()
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
	
	steping(steping::Eat::accept);
		
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
			lstItem->front()->upStep(connDB,(short)steping::Eat::preparing);
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
void Application::steping(steping::Eat to_step)
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
