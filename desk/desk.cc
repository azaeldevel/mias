
#include <gtkmm/application.h>

#include "desk.hh"

namespace mias
{

Mias::Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& b) : mps::Restaurant(cobject,b)
{
	init();	
}
Mias::Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& b,bool d) : mps::Restaurant(cobject,b,d)
{
	init();	
}
void Mias::init()
{	
	set_title("Mia's Pizza & Pasta");
	
	boxSlices = 0;
	builder->get_widget("boxSlices", boxSlices);
	
	boxSlices->pack_start(boxWork);	
	
	boxWork.pack_start(activities);
	activities.append_page(sales);
	
	
	show_all_children();
}
Mias::~Mias()
{
}





Sales::Sales()
{
	init();	
}
void Sales::init()
{	
	add1(pending);
	add2(saling);
	
	
}
Sales::~Sales()
{
}






Saling::Saling() : Gtk::Box(Gtk::ORIENTATION_VERTICAL)
{
	init();	
}
void Saling::init()
{	
	pack_start(capture,false,false);	
	capture.add(boxCapture);
	capture.set_label("Captura");
	
	boxCapture.pack_start(inAmount);
	boxCapture.pack_start(inPresentation);
	boxCapture.pack_start(cmbItem);
	boxCapture.pack_start(inCost);
	
}
Saling::~Saling()
{
}







PendingServices::PendingServices() : Gtk::Box(Gtk::ORIENTATION_VERTICAL)
{
	init();	
}
void PendingServices::init()
{	
	pack_start(lbTitle,false,false);
	lbTitle.set_text("Lista de Servicios : ");
	
}
PendingServices::~PendingServices()
{
}

}

