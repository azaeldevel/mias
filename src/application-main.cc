

#include "application.hh"
#include <iostream>

int main()
{	
	//std::cout << "Mia's Pizza & Pasta\n";
	mias::BodyApplication body;
	mias::Application app(body,"Mia's Pizza & Pasta");
	app.main();
	
	return 0;
}