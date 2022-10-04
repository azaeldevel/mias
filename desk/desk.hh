
#ifndef MIAS_MAIN_HH
#define MIAS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>

#include "config.h"

#include <muposys/desk/desk.hh>



namespace mps
{

class Mias : public Restaurant
{
public:
	/**
	*
	**/
	Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade,bool);
	void init();
	virtual ~Mias();
	
protected:

private:
	Gtk::Notebook notebook;
	Gtk::Box* boxClients;
	Gtk::Window* sales;

};


}

#endif
