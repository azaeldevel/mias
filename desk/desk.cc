
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
	
	pack_start(table,false,false);
	
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
		
	pack_start(servicies);
	
}
PendingServices::~PendingServices()
{
}





TableSaling::TableSaling()
{
	init();	
}
void TableSaling::init()
{		
	
	tree_model = Gtk::ListStore::create(columns);
	set_model(tree_model);
	
	append_column("Cant.", columns.amount);
	append_column("Present.", columns.presentation);
	append_column("Articulo", columns.item);
	append_column("Costo", columns.cost);
	
	//loading data
	Gtk::TreeModel::Row row = *(tree_model->append());
	row[columns.amount] = 1;
	row[columns.presentation] = "Pz";
	row[columns.item] = "Chica - Peperoni";
	row[columns.cost] = 115;
	
	row = *(tree_model->append());
	row[columns.amount] = 1;
	row[columns.presentation] = "Pz";
	row[columns.item] = "Grande - Mexiana";
	row[columns.cost] = 235;
	
}
TableSaling::~TableSaling()
{
}
TableSaling::ModelColumns::ModelColumns()
{
	add(amount);
	add(presentation);
	add(item);	
	add(cost);
}




TableServicies::TableServicies()
{
	init();	
}
void TableServicies::init()
{		
	tree_model = Gtk::ListStore::create(columns);
	set_model(tree_model);
	
	append_column("Servicio", columns.service);
	append_column("Nombre", columns.name);	
	auto cell = Gtk::make_managed<Gtk::CellRendererProgress>();
	int cols_count = append_column("Progreso", *cell);
	auto pColumn = get_column(cols_count - 1);
	if(pColumn)
	{
		pColumn->add_attribute(cell->property_value(), columns.progress);
	}
	  
	  
	//loading data
	Gtk::TreeModel::Row row = *(tree_model->append());
	row[columns.service] = 1;
	row[columns.name] = "Julio";
	row[columns.progress] = 75;
	
	row = *(tree_model->append());
	row[columns.service] = 2;
	row[columns.name] = "María";
	row[columns.progress] = 15;
	
	row = *(tree_model->append());
	row[columns.service] = 3;
	row[columns.name] = "Azael";
	row[columns.progress] = 5;
}
TableServicies::~TableServicies()
{
}

TableServicies::ModelColumns::ModelColumns()
{
	add(service);
	add(name);
	add(progress);	
}



}

