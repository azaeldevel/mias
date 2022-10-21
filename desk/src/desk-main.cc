
#include <gtkmm.h>
#include <iostream>
#include <exception>


#include "config.h"

#ifdef ENABLE_NLS
#  include <libintl.h>
#endif

#include "desk.hh"


int main (int argc, char *argv[])
{
	/*
	bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);
	*/
	
	Gtk::Main kit(argc, argv);

	//Load the Glade file and instiate its widgets:
	Glib::RefPtr<Gtk::Builder> builder;
	try
	{
		builder = Gtk::Builder::create();
		std::string fileui;
		
		fileui = DATA_DIR;
		fileui += "/muposys/desk/muposys-desk.ui";
		builder->add_from_file(fileui);
#ifdef MIAS_DESK_ENABLE_TDD
		fileui = PACKAGE_SRC_DIR;
#else
		fileui = PACKAGE_DATA_DIR;
#endif
		fileui += "/mias-desk.ui";
		builder->add_from_file(fileui);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (const Glib::FileError& ex)
	{
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	try
	{
		mias::Mias* Main = 0;
#ifdef MIAS_DESK_ENABLE_TDD
		builder->get_widget_derived("Main", Main,true);
#else
		builder->get_widget_derived("Main", Main);
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
