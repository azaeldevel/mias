
#include <gtkmm/application.h>

#include "desk.hh"

namespace mps
{

Mias::Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Restaurant(cobject,refGlade)
{
	init();	
}
Mias::Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade,bool d) : Restaurant(cobject,refGlade,d)
{
	init();	
}
void Mias::init()
{
	boxClients = 0;
	builder->get_widget("boxClients", boxClients);
	
	sales = 0;
	builder->get_widget("Sales", sales);
	sales->show();
	
	boxClients->pack_start(notebook);
	sales->set_parent(*this);
	add(*sales);
	notebook.append_page(*sales);
	notebook.show();
}
Mias::~Mias()
{
}


}

