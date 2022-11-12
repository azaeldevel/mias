

#include "application.hh"
#include <iostream>


int main()
{	
	//mps::contenttype(std::cout,"text","html");
	/*
	mias::Station station;	
	std::map<std::string, std::string> params;
	mias::params_get(params);
	
	if(params.empty())
	{
		station = mias::Station::none;
	}
	else
	{
		std::map<std::string, std::string>::iterator it = params.find("station");
		if(it->second.compare("pizza") == 0)
		{
			station = mias::Station::pizza;
			//std::cout << "Pizza detected";
		}
		else
		{
			station = mias::Station::none;
		}
	}
	*/
	
	mias::BodyApplication body;
	//std::cout << "Step 2n";
	mias::Application app(body,"Mia's Pizza & Pasta");
	//std::cout << "Step 3\n";
	app.main();
	
	return 0;
}
