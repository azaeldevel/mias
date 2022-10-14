
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
	tree_model->signal_row_changed().connect(sigc::mem_fun(*this, &TableSaling::row_changed));
	set_model(tree_model);
	
	append_column_editable("Cant.", columns.quantity);
	Gtk::CellRendererSpin* cell_quantity = static_cast<Gtk::CellRendererSpin*>(get_column_cell_renderer(get_n_columns() - 1));
	Gtk::TreeViewColumn* col_quantity = get_column(get_n_columns() - 1);
	cell_quantity->property_editable() = true;
	//col_quantity->set_cell_data_func(*cell_quantity,sigc::mem_fun(*this,&TableSaling::treeviewcolumn_validated_on_cell_data_quantity));
	//cell_quantity->signal_editing_started().connect(sigc::mem_fun(*this,&TableSaling::cellrenderer_validated_on_editing_started_quantity));
	//cell_quantity->signal_edited().connect(sigc::mem_fun(*this, &TableSaling::cellrenderer_validated_on_edited_quantity));	
	append_column("Present.", columns.presentation);
	append_column_editable("Number", columns.number);
	Gtk::CellRendererText* cell_number = static_cast<Gtk::CellRendererText*>(get_column_cell_renderer(get_n_columns() - 1));
	Gtk::TreeViewColumn* col_number = get_column(get_n_columns() - 1);
	//col_number->set_cell_data_func(*cell_number,sigc::mem_fun(*this,&TableSaling::treeviewcolumn_validated_on_cell_data_number));
	cell_number->property_editable() = true;
	cell_number->signal_editing_started().connect(sigc::mem_fun(*this,&TableSaling::cellrenderer_validated_on_editing_started_number));
	cell_number->signal_edited().connect(sigc::mem_fun(*this, &TableSaling::cellrenderer_validated_on_edited_number));
	
	append_column("Artículo", columns.name);
	append_column_numeric_editable("Costo", columns.cost,"%.2f");
	
	
	newrow();
	
	/*column_validated.set_title("editando..)");
	column_validated.pack_start(cell_render);
	append_column(column_validated);
	column_validated.set_cell_data_func(cell_render, sigc::mem_fun(*this,&TableSaling::treeviewcolumn_validated_on_cell_data));
	cell_render.property_editable() = true;
	cell_render.signal_editing_started().connect(sigc::mem_fun(*this,&TableSaling::cellrenderer_validated_on_editing_started) );
	cell_render.signal_edited().connect( sigc::mem_fun(*this, &TableSaling::cellrenderer_validated_on_edited) );*/
		
	
	//loading data
	/*
	Gtk::TreeModel::Row row = *(tree_model->append());
	row[columns.id] = 1;
	row[columns.item] = 1;
	row[columns.amount] = 1;
	row[columns.presentation] = "Pz";
	row[columns.number] = "ppp";
	row[columns.name] = "Chica - Peperoni";
	row[columns.cost] = 115;
	
	row = *(tree_model->append());
	row[columns.id] = 2;
	row[columns.item] = 1;
	row[columns.amount] = 1;
	row[columns.presentation] = "Pz";
	row[columns.number] = "gmx";
	row[columns.name] = "Grande - Mexiana";
	row[columns.cost] = 235;
	*/
}
TableSaling::~TableSaling()
{
}
TableSaling::ModelColumns::ModelColumns()
{
	add(id);
	add(item);
	add(quantity);
	add(presentation);
	add(number);
	add(name);
	add(cost);
}

void TableSaling::row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter)
{
	std::cout << "Size : " << tree_model->children().size() << "\n";		
	const Gtk::TreeModel::iterator last = --(tree_model->children().end());
	if(last == iter) newrow();
}

/*
void TableSaling::treeviewcolumn_validated_on_cell_data( Gtk::CellRenderer* renderer , const Gtk::TreeModel::iterator& iter)
{
	//Get the value from the model and show it appropriately in the view:
	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		Glib::ustring model_value = row[columns.number_validated];

		//This is just an example.
		//In this case, it would be easier to use append_column_editable() or
		//append_column_numeric_editable()
		char buffer[32];
		sprintf(buffer, "%d", model_value);

		Glib::ustring view_text = buffer;
		cell_render.property_text() = "---" + view_text + "---";
	}
}
void TableSaling::cellrenderer_validated_on_editing_started( Gtk::CellEditable* cell_editable, const Glib::ustring&)
{
	
	octetos::db::maria::Connector connector;
	if(not connector.connect(muposysdb::datconex)) throw octetos::db::SQLException("Fallo la conexión a la Base de datos",__FILE__,__LINE__);
	
	if(validate_retry)
	{
		auto celleditable_validated = cell_editable;
		
		auto pEntry = dynamic_cast<Gtk::Entry*>(celleditable_validated);
		if(pEntry)
		{
			pEntry->set_text(invalid_text_for_retry);
			validate_retry = false;
			invalid_text_for_retry.clear();
		}
	}
}
void TableSaling::cellrenderer_validated_on_edited(const Glib::ustring& path_string, const Glib::ustring& new_text)
{
	Gtk::TreePath path(path_string);
	
	if(new_text.size() > 3)
	{
		std::cout << "Error : " << new_text << "\n";
		
		invalid_text_for_retry = new_text;
		validate_retry = true;
		
		set_cursor(path, column_validated,cell_render, true);
	}
	else
	{
		Gtk::TreeModel::iterator iter = tree_model->get_iter(path);
		if(iter)
		{
			Gtk::TreeModel::Row row = *iter;
			row[columns.number_validated] = new_text;
		}
	}
}
*/

void TableSaling::treeviewcolumn_validated_on_cell_data_number( Gtk::CellRenderer* renderer , const Gtk::TreeModel::iterator& iter)
{
	if(iter)
	{
		Gtk::TreeModel::Row row = *iter;
		Glib::ustring model_value = row[columns.number];
		
		static_cast<Gtk::CellRendererText*>(renderer)->property_text() = model_value;
	}
}
void TableSaling::cellrenderer_validated_on_editing_started_number( Gtk::CellEditable* cell_editable, const Glib::ustring& path)
{
	Gtk::TreeModel::iterator iter = tree_model->get_iter(path);
	Gtk::TreeModel::Row row = *iter;
	
	octetos::db::maria::Connector connector;
	if(not connector.connect(muposysdb::datconex)) throw octetos::db::SQLException("Falló la conexión a la Base de datos",__FILE__,__LINE__);
	
	std::vector<muposysdb::Catalog_Items*>* lstCatItems = NULL;
	
	auto pEntry = dynamic_cast<Gtk::Entry*>(cell_editable);
	if(pEntry)
	{
		std::string where = "number = '" + pEntry->get_text() + "'";
		lstCatItems = muposysdb::Catalog_Items::select(connector,where);
		//std::cout << "where : " << where << "\n";
	}
	
	row[columns.number_validated]  = false;
	if(not lstCatItems) return;
	
	if(lstCatItems->size() == 1)
	{			
		if(lstCatItems->front()->downName(connector))
		{
			row[columns.name] = lstCatItems->front()->getName();
			row[columns.number_validated] = true;
		}
	}
	for(muposysdb::Catalog_Items* p : *lstCatItems)
	{
		delete p;
	}
	delete lstCatItems;
}
void TableSaling::cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& new_text)
{
	Gtk::TreePath path(path_string);
	
	octetos::db::maria::Connector connector;
	if(not connector.connect(muposysdb::datconex)) throw octetos::db::SQLException("Falló la conexión a la Base de datos",__FILE__,__LINE__);
		
	std::string where = "number = '" + new_text + "'";
	std::vector<muposysdb::Catalog_Items*>* lstCatItems = muposysdb::Catalog_Items::select(connector,where);
	//std::cout << "where : " << where << "\n";
	
	if(not lstCatItems) return;
	
	if(lstCatItems->size() == 1)
	{
		lstCatItems->front()->downName(connector);
		lstCatItems->front()->downValue(connector);
		lstCatItems->front()->downPresentation(connector);
		
			Gtk::TreeModel::iterator iter = tree_model->get_iter(path);
			if(iter)
			{
				Gtk::TreeModel::Row row = *iter;
				//Put the new value in the model:
				row[columns.number] = new_text;
				row[columns.name] = lstCatItems->front()->getName();
				row[columns.presentation] = lstCatItems->front()->getPresentation();
				row[columns.cost] = row[columns.quantity] * lstCatItems->front()->getValue();
			}
	}
	for(muposysdb::Catalog_Items* p : *lstCatItems)
	{
		delete p;
	}
	delete lstCatItems;
}



void TableSaling::treeviewcolumn_validated_on_cell_data_quantity( Gtk::CellRenderer* cell_editable , const Gtk::TreeModel::iterator& iter)
{
	Gtk::Entry* entry = dynamic_cast<Gtk::Entry*>(cell_editable);
	Gtk::CellRendererSpin* cell = dynamic_cast<Gtk::CellRendererSpin*>(cell_editable);
	Gtk::TreeModel::Row row = *iter;
	row[columns.quantity_valid] = false;
	
	unsigned long number;
	try
	{
		number = std::stoul((std::string)entry->get_text());
	}
	catch(const std::invalid_argument& e)
	{
		row[columns.quantity_valid] = false;
		cell->property_text() = "#";
		return;
	}
	catch(const std::out_of_range& e)
	{
		row[columns.quantity_valid] = false;
		cell->property_text() = "#";
		return;		
	}
	
	cell->property_text() = entry->get_text();
}
void TableSaling::cellrenderer_validated_on_editing_started_quantity( Gtk::CellEditable* cell_editable, const Glib::ustring& path)
{	
	Gtk::TreeModel::iterator iter = tree_model->get_iter(path);
	Gtk::Entry* entry = dynamic_cast<Gtk::Entry*>(cell_editable);
	Gtk::TreeModel::Row row = *iter;
	row[columns.quantity_valid] = false;
	
	unsigned long number;
	try
	{
		number = std::stoul(entry->get_text());
	}
	catch(const std::invalid_argument& e)
	{
		row[columns.quantity_valid] = false;
		return;
	}
	catch(const std::out_of_range& e)
	{
		row[columns.quantity_valid] = false;
		return;		
	}
	
	row[columns.quantity_valid] = true;
}
void TableSaling::cellrenderer_validated_on_edited_quantity(const Glib::ustring& path_string, const Glib::ustring& new_text)
{
	Gtk::TreePath path(path_string);
	
	octetos::db::maria::Connector connector;
	if(not connector.connect(muposysdb::datconex)) throw octetos::db::SQLException("Falló la conexión a la Base de datos",__FILE__,__LINE__);
		
	std::string where = "number = '" + new_text + "'";
	std::vector<muposysdb::Catalog_Items*>* lstCatItems = muposysdb::Catalog_Items::select(connector,where);
	//std::cout << "where : " << where << "\n";
	
	if(not lstCatItems) return;
	
	if(lstCatItems->size() == 1)
	{
		lstCatItems->front()->downName(connector);
		lstCatItems->front()->downValue(connector);
		lstCatItems->front()->downPresentation(connector);
		
			Gtk::TreeModel::iterator iter = tree_model->get_iter(path);
			if(iter)
			{
				Gtk::TreeModel::Row row = *iter;
				//Put the new value in the model:
				row[columns.number] = new_text;
				row[columns.name] = lstCatItems->front()->getName();
				row[columns.presentation] = lstCatItems->front()->getPresentation();
				row[columns.cost] = row[columns.quantity] * lstCatItems->front()->getValue();
			}
	}
	for(muposysdb::Catalog_Items* p : *lstCatItems)
	{
		delete p;
	}
	delete lstCatItems;
}


void TableSaling::newrow()
{
	tree_model->append();
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

