
#include <gtkmm.h>
#include <iostream>
#include <exception>


#include "desk.hh"


int main (int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);

	try
	{
		oct::mias::v1::Mias* Main = 0;
#ifdef OCTETOS_MIAS_DESK_V1_TDD
		Main = new oct::mias::v1::Mias(true);
#else
		Main = new oct::mias::v1::Mias;
#endif
		if (Main) kit.run(*Main);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
