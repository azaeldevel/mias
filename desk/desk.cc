
#include <gtkmm/application.h>
#include <muposys/muposysdb.hpp>

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
	add_events(Gdk::KEY_PRESS_MASK);		
	
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





SearchItem::SearchItem() : Gtk::ComboBox(true)
{
	init();
}
void SearchItem::init()
{
	octetos::db::maria::Connector connector;
	if(not connector.connect(muposysdb::datconex)) throw octetos::db::SQLException("Fallo la conexión a la Base de datos",__FILE__,__LINE__);
	
	//set_icon_from_icon_name("edit-find");

	refModel = Gtk::ListStore::create(columns);
	set_model(refModel);
		
	std::vector<muposysdb::Catalog_Items*>* lstCatItems = muposysdb::Catalog_Items::select(connector,"");
	std::vector<muposysdb::Catalog_Items*>::const_iterator it = lstCatItems->begin();
	Gtk::TreeModel::Row row;
	for(unsigned int  i = 0; i < lstCatItems->size();i++)
	{
		row = *(refModel->append());
		
		it[i]->downNumber(connector);
		it[i]->downName(connector);
		
		row[columns.id] = i + 1;
		row[columns.number] = it[i]->getNumber();
		row[columns.name] = it[i]->getName();
		row[columns.db] = it[i];
		//std::cout << "number : " << it[i]->getNumber() << "\n";
		//std::cout << "name : " << it[i]->getName() << "\n";
	}
	
	set_cell_data_func(cell,sigc::mem_fun(*this, &SearchItem::on_cell_data_extra));
	pack_start(cell);
	signal_changed().connect( sigc::mem_fun(*this, &SearchItem::on_combo_changed) );
	signal_key_press_event().connect(sigc::mem_fun(*this,	&SearchItem::on_combo_key_presst) );
		
	item = get_entry();
	if (item)
	{
		//item->add_events(Gdk::KEY_PRESS_MASK);
		// The Entry shall receive focus-out events.
		item->add_events(Gdk::FOCUS_CHANGE_MASK);

		// Alternatively you can connect to m_Combo.signal_changed().
		item->signal_changed().connect(sigc::mem_fun(*this,	&SearchItem::on_entry_changed) );
		item->signal_activate().connect(sigc::mem_fun(*this,&SearchItem::on_entry_activate) );
		item->signal_focus_out_event().connect(sigc::mem_fun(*this,	&SearchItem::on_entry_focus_out_event) );
		//item->signal_key_press_event().connect(sigc::mem_fun(*this,	&SearchItem::on_entry_key_presst) );
		focusOut = item->signal_focus_out_event(). connect(sigc::mem_fun(*this, &SearchItem::on_entry_focus_out_event) );
	}
	
	connector.close();
}
SearchItem::~SearchItem()
{
	for(auto p : *lstCatItems)
	{
		        delete p;
	}
	delete lstCatItems;
	focusOut.disconnect();
}

SearchItem::ModelColumnsItem::ModelColumnsItem()
{
	add(id);
	add(number);
	add(name);
	add(db);
}

void SearchItem::on_cell_data_extra(const Gtk::TreeModel::const_iterator& iter)
{
  auto row = *iter;
  const Glib::ustring extra = row[columns.name];

  //Transform the value, deciding how to represent it as text:
  if(extra.empty())
    cell.property_text() = "(none)";
  else
    cell.property_text() = extra;
	//item->set_text(extra);
	//cell.property_foreground() = (extra == "yadda" ? "red" : "green");
}

void SearchItem::on_combo_changed()
{
	Gtk::TreeModel::iterator iter = get_active();
	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		if(row)
		{
			//Get the data for the selected row, using our knowledge of the tree
			//model:
			//int id = row[columns.id];
			//Glib::ustring name = row[columns.name];
			//set_active((int)row[columns.id]);
			const muposysdb::Catalog_Items* reg = row[columns.db];
			item->set_text(reg->getName()) ;
			
			//std::cout << " ID=" << get_active_row_number() << ", db=" << reg->getNumber() << std::endl;
		}
	}
	else
	{
		std::cout << "invalid iter" << std::endl;
	}
}
void SearchItem::on_entry_changed()
{
	if (item)
	{
		//std::cout << "on_entry_changed(): Row=" << get_active_row_number() << ", ID=" << item->get_text() << std::endl;
		//popdown();
		//set_focus_child(*item);
		//item->set_text(item->get_text());
		//item->grab_focus();
		popup ();
		//item->grab_focus_without_selecting();
	}
}

void SearchItem::on_entry_activate()
{
	if (item)
	{
		//std::cout << "on_entry_activate(): Row=" << get_active_row_number()  << ", ID=" << item->get_text() << std::endl;
	}
}

bool SearchItem::on_entry_focus_out_event(GdkEventFocus* /* event */)
{
	if (item)
	{
		//std::cout << "on_entry_focus_out_event(): Row=" << get_active_row_number() << ", ID=" << item->get_text() << std::endl;
		return true;
	}
	
	return false;
}
bool SearchItem::on_entry_key_presst(GdkEventKey* event)
{
	//if (event->type == GDK_KEY_PRESS and event->keyval >= GDK_KEY_A and event->keyval <= GDK_KEY_Z)
	{
		std::cout << "Char :" << (wchar_t) event->keyval << "\n";
		return true;
	}
  return false;
}
bool SearchItem::on_combo_key_presst(GdkEventKey* event)
{
	//if (event->type == GDK_KEY_PRESS and event->keyval >= GDK_KEY_A and event->keyval <= GDK_KEY_Z)
	{
		std::cout << "Char :" << (wchar_t) event->keyval << "\n";
		return true;
	}
  
	return false;
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
	inAmount.set_wrap();
	boxCapture.pack_start(item);
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

