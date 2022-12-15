
#include <string.h>
#include <cstring>
#include <sstream>
#include <vector>

#include "application.hh"

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
		else
		{
			step = Eating::none;
		}

		param = find("item");
		if(param)
		{
			item = std::stol(param);
		}
		else
		{
			item = -1;
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

		param = find("session");
		if(param)
		{
			session = param;
		}
	}


GetParams::operator std::string()const
{
	std::string str;
	
	if(not session.empty()) str = "session=" + session;

	if(station != Station::none) 
	{
		if(not session.empty()) str += "&";
		std::string strstation = "station=";
		strstation += to_string(station);
		str += strstation;
	}

	if(order > 0) 
	{
		if(not session.empty()) str += "&";
		std::string strorder = "order=";
		strorder += std::to_string(order);
		str += strorder;
	}
	else if(order == 0) 
	{
		if(not session.empty()) str += "&";
		std::string strorder = "order=next";
		str += strorder;
	}

	
	if(step != Eating::none) 
	{
		if(not session.empty()) str += "&";
		std::string strstep = "step=";
		strstep += to_string(step);
		str += strstep;
	}
	else
	{
		if(not session.empty()) str += "&";
		std::string strstep = "step=none";
		str += strstep;
	}
		
	if(item > 0) 
	{
		if(not session.empty()) str += "&";
		std::string stritem = "item=";
		stritem += std::to_string(item);
		str += stritem;
	}
		
	if(restoring) 
	{
		if(not session.empty()) str += "&";
		str += "restoring";
	}
	
	return str;
}


BodyApplication::BodyApplication(const GetParams& p) : params(p),mps::BodyApplication(p)
{
}
void BodyApplication::programs(std::ostream& out)
{
	if(params.station == Station::pizza or params.station == Station::stove)
	{
		if(params.step == Eating::none and params.order == -1)
		{
			select_order(out);
		}
		else if(params.step == Eating::none and params.order > 0 and not params.restoring)
		{
			select_item(out);
		}
		else if(params.step == Eating::accepted and params.order > 0 and not params.restoring)
		{
			accepted_item(out);
		}
		else if(params.restoring)
		{
			restoring_order(out);
		}
	}
	else if(params.station == Station::oven)
	{

	}
	else
	{
		out << "\t\t\t<div id=\"pizza\"><a href=\"application.cgi?station=pizza&step=none&session=" << params.session << "\"></a></div>\n";
		out << "\t\t\t<div id=\"stove\"><a href=\"application.cgi?station=stove&step=none&session=" << params.session << "\"></a></div>\n";
		out << "\t\t\t<div id=\"oven\"><a href=\"application.cgi?station=oven&step=none&session=" << params.session << "\"></a></div>\n";
	}
}

void BodyApplication::panel(std::ostream& out)
{
	if(params.station == Station::pizza or params.station == Station::stove)
	{
		out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi?session=" << params.session << "\"></a></div>\n";
		//out << "\t\t\t<div class=\"space\"></div>\n";
		if(params.step == Eating::none and params.order == -1)
		{
			select_order_restore(out);
		}
		else if(params.restoring and params.step == Eating::none and params.order > 0)
		{
			select_step_restore(out);
		}
		else if(params.restoring and params.step > Eating::none and params.step < Eating::finalized and params.order > 0)
		{
			select_item_restore(out);
		}
	}
	else if(params.station == Station::oven)
	{

	}
	else
	{
		out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi?session=" << params.session << "\"></a></div>\n";
		//out << "\t\t\t<div class=\"space\"></div>\n";
		out << "\t\t\t<div id=\"system\"><a href=\"system.html?session=" << params.session << "\"></a></div>\n";
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
	//out << application->get_user() << "\n";
	if(params.station == Station::pizza or params.station == Station::stove)
	{
		print_common(out);
		print_common_commands(out);
	}
	else if(params.station == Station::oven)
	{
		print_oven(out);
	}
	return out;
}

const char* BodyApplication::to_text(Eating s)
{
		switch(s)
		{
			case Eating::cook:
				if(params.station == Station::pizza)
				{
					return "Hornear";
				}
				else if(params.station == Station::stove)
				{
					return "Freir";
				}
				break;
			case Eating::cooking:
				if(params.station == Station::pizza)
				{
					return "Horneando";
				}
				else if(params.station == Station::stove)
				{
					return "Friendo";
				}
				break;
			case Eating::cooked:
				if(params.station == Station::pizza)
				{
					return "Horneado";
				}
				else if(params.station == Station::stove)
				{
					return "Frito";
				}
				break;
		}

		return mias::to_text(s);
}

std::ostream& BodyApplication::print_common(std::ostream& out)
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
					p->downStocking(*connDB);
					p->getStocking().downItem(*connDB);
					p->getStocking().getItem().downNumber(*connDB);
					p->getStocking().getItem().downBrief(*connDB);
					if(p->getStocking().getID() == params.item)
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
						out << "\t" << mias::to_text(params.station) << " : "<< item->getBrief() << "<br>\n";
					}
				}
				out << "\t</div>\n";
			}
			out << "\t</div>\n";
			delete item;
		}
		out << "\t</div>\n";

	return out;
}
std::ostream& BodyApplication::print_common_commands(std::ostream& out)
{
		out << "\t<div id=\"commands\">\n";
		{
			out << "\t<div id=\"left\">\n";
			{

			}
			out << "\t</div>\n";
			out << "\t<div id=\"right\">\n";
			{
				switch(params.step)
				{
					case Eating::none:
						out << "\t<a id=\"cmdBegin\" class=\"cmd\" onclick=\"toBegin()\">Inicio</a>";
						break;
					case Eating::accept:
						out << "\t<a id=\"cmdBegin\" class=\"cmd\" onclick=\"toBegin()\">Inicio</a>";
						break;
					case Eating::accepted:
						out << "\t<a id=\"cmdBegin\" class=\"cmd\" onclick=\"toBegin()\">Inicio</a>";
						out << "\t<a id=\"cmdPreparing\" class=\"cmd\" onclick=\"toPreparing()\">" << to_text(Eating::preparing) << "</a>";
						out << "\t<a id=\"cmdCooking\" class=\"cmd\" onclick=\"toCooking()\">" << to_text(Eating::cooking) << "</a>";
						//out << "\t<a id=\"cmdCooked\" class=\"cmd\" onclick=\"toCooked()\">" << to_text(Eating::cooked) << "</a>";
						//out << "\t<a id=\"cmdPreparing\" class=\"cmd\" onclick=\"toPreparing()\">" << to_text(Eating::preparing) << "</a>";
						break;
					case Eating::prepare:
						out << "\t<a id=\"cmdCooking\" class=\"cmd\" onclick=\"toCooking()\">" << to_text(Eating::cooking) << "</a>";
						out << "\t<a id=\"cmdPreparing\" class=\"cmd\" onclick=\"toPreparing()\">" << to_text(Eating::preparing) << "</a>";
						break;
					case Eating::preparing:
						out << "\t<a id=\"cmdCooking\" class=\"cmd\" onclick=\"toCooking()\">" << to_text(Eating::cooking) << "</a>";
						out << "\t<a id=\"cmdPrepared\" class=\"cmd\" onclick=\"toPrepared()\">Preparada</a>";
						break;
					case Eating::prepared:
						out << "\t<a id=\"cmdBegin\" class=\"cmd\" onclick=\"toBegin()\">Inicio</a>";
						out << "\t<a id=\"cmdCooking\" class=\"cmd\" onclick=\"toCooking()\">" << to_text(Eating::cooking) << "</a>";
						out << "\t<a id=\"cmdFinalized\" class=\"cmd\" onclick=\"toFinalized()\">Completada</a>";
						break;
					case Eating::cooking:
						out << "\t<a id=\"cmdBegin\" class=\"cmd\" onclick=\"toBegin()\">Inicio</a>";
						//out << "\t<a id=\"cmdCooked\" class=\"cmd\" onclick=\"toCooked()\">" << to_text(Eating::cooked) << "</a>";
						out << "\t<a id=\"cmdFinalized\" class=\"cmd\" onclick=\"toFinalized()\">Completada</a>";
						break;
					case Eating::cooked:
						out << "\t<a id=\"cmdBegin\" class=\"cmd\" onclick=\"toBegin()\">Inicio</a>";
						out << "\t<a id=\"cmdFinalized\" class=\"cmd\" onclick=\"toFinalized()\">Completada</a>";
						break;
					case Eating::finalized:
						out << "\t<a id=\"cmdBegin\" class=\"cmd\" onclick=\"toBegin()\">Inicio</a>";
						break;
					case Eating::cancel:

						break;
				}
				out << "\t</div>\n";
			}
		}
		out << "\t</div>\n";

	return out;
}
std::ostream& BodyApplication::print_oven(std::ostream& out)
{
	out << "\t<div id=\"work\">\n";
	out << "\t\t<div id=\"list_oven\">\n";
	{
		std::string whereService = "step > " ;
		whereService += std::to_string((int)ServiceStep::created);
		whereService += " and step < ";
		whereService += std::to_string((int)ServiceStep::delivered);
		std::vector<muposysdb::MiasService*>* lstService = muposysdb::MiasService::select(*connDB,whereService,0,'A');
		if(lstService->size() > 0)
		{
			for(auto s : *lstService)
			{
				s->downName(*connDB);

				std::string whereProcess;
				whereProcess = "operation = ";
				whereProcess += std::to_string(s->getOperation().getID());
				whereProcess += " and step >= ";
				whereProcess += std::to_string((short)Eating::cook);
				whereProcess += " and step < ";
				whereProcess += std::to_string((short)Eating::finalized);
				std::vector<muposysdb::Progress*>* lstProgress = muposysdb::Progress::select(*connDB,whereProcess,0,'A');
				if(lstProgress->size() > 0)
				{
					for(auto p : *lstProgress)
					{
						p->downStocking(*connDB);
						p->getStocking().downItem(*connDB);
						p->getStocking().getItem().downNumber(*connDB);
						p->getStocking().getItem().downBrief(*connDB);
						p->getStocking().getItem().downStation(*connDB);

						if((Station)p->getStocking().getItem().getStation() != Station::pizza) continue;

						out << "\t\t\t<div id=\"item_" << p->getStocking().getID() << "\" class=\"oven_item\">\n";
						{
							out << "\t\t\t\t<div class=\"oven_item_name\">\n";
							{
								out << "\t\t\t\t\t" << p->getStocking().getItem().getBrief() << " - " << s->getOperation().getID() << "\n";
							}
							out << "\t\t\t\t</div>\n";
							out << "\t\t\t\t<div class=\"oven_item_cmd\">\n";
							{
								out << "\t\t\t\t\t<a id=\"cmdFinalized\" class=\"cmd\" onclick=\"toOvenFinalized("<< s->getOperation().getID() << "," <<  p->getStocking().getID() << ")\">" << to_text(Eating::finalized) << "</a>\n";
							}
							out << "\t\t\t\t</div>\n";
						}
						out << "\t\t\t</div>\n";
					}
					for(auto p : *lstProgress)
					{
						delete p;
					}
					delete lstProgress;
				}
			}
			for(auto s : *lstService)
			{
				delete s;
			}
			delete lstService;
		}
	}
	out << "\t\t</div\n";
	out << "\t</div\n";

	return out;
}














Application::~Application()
{
}
void Application::init()
{
	head.css("css/mias.css");
	head.addscript("js/mias.js");
	((BodyApplication&)*body).set(connDB);
	((BodyApplication&)*body).set(*this);
}
Application::Application(BodyApplication& b,const GetParams& p) : params(p),mps::Application(b,p)
{
	head.title = "Multi-Porpuse Software System";
	init();
}
Application::Application(BodyApplication& b,const std::string& t,const GetParams& p) : params(p),mps::Application(b,t,p)
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
		out << "Params : " << (std::string)params << "\n";
		head.print(out);
		return EXIT_SUCCESS;
	}

	switch(params.step)
	{
		case Eating::none:
			
			break;
		case Eating::accept:
		{
			//out << "Procesando solicitud de acceptacion...\n";
			long order = accepting();

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
			strgets += "&session=";
			strgets += params.session;
			std::string url = "application.cgi?";
			url += strgets;
			head.redirect(0,url.c_str());
			//out << "url : " << url << "<br>\n";
			//out << "done<br>\n";
			head.print(out);
			connDB.commit();
			return EXIT_SUCCESS;
		}
		case Eating::accepted:
			steping(Eating::accepted);
			break;
		case Eating::prepare:
			steping(Eating::prepare);
			break;
		case Eating::preparing:
			steping(Eating::prepared);
			connDB.commit();
			break;
		case Eating::prepared:
			steping(Eating::prepared);
			connDB.commit();
			break;
		case Eating::cook:
			steping(Eating::cook);
			connDB.commit();
			break;
		case Eating::cooking:
			steping(Eating::cooking);
			connDB.commit();
			break;
		case Eating::cooked:
			steping(Eating::cooked);
			connDB.commit();
			break;
		case Eating::finalized:
			steping(Eating::finalized);
			connDB.commit();
			break;
		case Eating::cancel:
			steping(Eating::cancel);
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
			order = lstService->front()->getOperation().getID();
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
	
	
	/*std::string whereProgress = "item = " + std::to_string(params.item);
	std::vector<muposysdb::Progress*>* lstProgress = muposysdb::Progress::select(*connDB,whereProgress);
	if(lstProgress->size() > 0)
	{
		if(lstProgress->front()->upWroker(*connDB,))
		
		for(auto p : *lstProgress)
		{
			delete p;
		}
		delete lstProgress;
	}*/

	steping(Eating::accept);

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
			lstItem->front()->upStep(connDB,(short)Eating::preparing);
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
void Application::steping(Eating to_step)
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
			throw Exception((unsigned int)Exception::DB_READ_FAIL,__FILE__,__LINE__);
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
