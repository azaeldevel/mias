
#include <string.h>
#include <cstring> 
#include <sstream>
#include <vector>


#include "application.hh"


namespace mias
{

	GetParams::GetParams()
	{
		std::map<std::string, std::string> params;
		params_get(params);
		
		std::map<std::string, std::string>::iterator it = params.find("station");		
		if(it->second.compare("pizza") == 0)
		{
			station = mias::Station::pizza;
		}
		else
		{
			station = mias::Station::none;
		}
		
		
	}
	
	
	
	
	
BodyApplication::BodyApplication()
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
			out << "\t\t\t<div id=\"pizza\"><a href=\"/application.cgi?station=pizza\">Pizza</a></div>\n";
			out << "\t\t\t<div id=\"stove\"><a href=\"/application.cgi?station=stove\">Estufa</a></div>\n";
			out << "\t\t\t<div id=\"Horno\"><a href=\"/application.cgi?station=oven\">Horno</a></div>\n";
	}
}
void BodyApplication::programs_pizza(std::ostream& out)
{
	out << "\t\t\t<div id=\"order\">\n";
	{
		out << "\t\t\t\t<select name=\"order\" id=\"orderList\">\n";
		{
			out << "\t\t\t\t\t<option value=\"next\">next</option>\n";
			
			std::vector<muposysdb::MiasService*>* lstService = muposysdb::MiasService::select(*connDB,"",0,'A');
			if(lstService)
			{
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
	out << "\t\t\t</div>\n";
	
	/*out << "\t\t\t<div id=\"item\">";
	{
		out << "<select name=\"order\" id=\"orderList\">\n";
		{
			out << "<option value=\"next\">next</option>";
			
			std::vector<muposysdb::Progress*>* lstProgress = muposysdb::Progress::select(*connDB,"",0,'A');
			if(lstProgress)
			{
				for(auto p : *lstProgress)
				{
					p->getStocking().getItem().downNumber(*connDB);
					out << "<option value=\"" << p->getStocking().getStocking() << "\">" << p->getStocking().getItem().getNumber() << "</option>\n";
				}
				for(auto p : *lstProgress)
				{
						delete p;
				}
				delete lstProgress;
			}
		}
		out << "</select>\n";
	}
	out << "</div>\n";*/
}
void BodyApplication::panel(std::ostream& out) 
{
	out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\"></a></div>\n";

	out << "\t\t\t<div class=\"space\"></div>\n";
	
	out << "\t\t\t<div id=\"system\"><a href=\"/system.html\"></a></div>\n";	
}
std::ostream& BodyApplication::operator >> (std::ostream& out)
{
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
		out << "\t<div id=\"working\">\n";		
		{
			
		}
		out << "\t</div>\n";
		
		out << "\t<div id=\"commands\">\n";	
		{
			out << "\t<div id=\"left\">\n";		
			{
					
			}
			out << "\t</div>\n";
			out << "\t<div id=\"right\">\n";		
			{
				out << "\t<a id=\"cmd\" onclick=\"cmdhref()\">Aceptar</a>";
			}
			out << "\t</div>\n";
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
	head.css("/css/mias.css");	
	head.addscript("/js/mias.js");
	((BodyApplication&)*body).set(connDB);
}
Application::Application(BodyApplication& b) : mps::Application(b)
{
	head.title = "Multi-Porpuse Software System";
	init();
}
Application::Application(BodyApplication& b,const std::string& t) : mps::Application(b,t)
{
	init();
}
std::ostream& Application::operator >> (std::ostream& out)
{
	mps::Application::operator >>(out);
	
	return out;
}
int Application::main(std::ostream& out)
{
	mps::contenttype(out,"text","html");
	
	if(not has_session())
	{
		head.redirect(0,"/login.html?failure");
		head >> out;
		return EXIT_SUCCESS;
	}
	
	(*this) >> out;

	return EXIT_SUCCESS;
}



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
}






}
