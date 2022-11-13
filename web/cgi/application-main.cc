

#include "application.hh"
#include <iostream>


int main()
{	
	//mps::contenttype(std::cout,"text","html");
	
	//std::cout << "Step 1\n";
	mias::GetParams params;
	//std::cout << "Step 2\n";
	mias::BodyApplication body(params);
	//std::cout << "Step 3\n";
	mias::Application app(body,"Mia's Pizza & Pasta",params);
	//std::cout << "Step 4\n";
	app.main();
	
	return 0;
}
