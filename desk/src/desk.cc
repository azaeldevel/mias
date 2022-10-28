
#include <gtkmm/application.h>
#include <muposys/muposysdb.hpp>

#include "desk.hh"

namespace mias
{
Mias::Mias()
{
	init();	
}
Mias::Mias(bool d) : mps::Restaurant(d)
{
	init();	
}
/*
Mias::Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& b) : mps::Restaurant(cobject,b)
{
	init();	
}
Mias::Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& b,bool d) : mps::Restaurant(cobject,b,d)
{
	init();	
}
*/
void Mias::init()
{	
	add_events(Gdk::KEY_PRESS_MASK);		
	set_title("Mia's Pizza & Pasta");
	set_default_size(800,640);
	nbMain.append_page(sale);
	
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
		
	std::vector<muposysdb::CatalogItem*>* lstCatItems = muposysdb::CatalogItem::select(connector,"");
	std::vector<muposysdb::CatalogItem*>::const_iterator it = lstCatItems->begin();
	Gtk::TreeModel::Row row;
	for(unsigned int  i = 0; i < lstCatItems->size();i++)
	{
		row = *(refModel->append());
		
		it[i]->downNumber(connector);
		it[i]->downBrief(connector);
		
		row[columns.id] = i + 1;
		row[columns.number] = it[i]->getNumber();
		row[columns.name] = it[i]->getBrief();
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
			const muposysdb::CatalogItem* reg = row[columns.db];
			item->set_text(reg->getBrief()) ;
			
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






TableServicies::TableServicies() : connDB_flag(false)
{
	init();	
}
void TableServicies::init()
{	
	try
	{
		connDB_flag = connDB.connect(muposysdb::datconex);
	}
	catch(const std::exception& e)
	{
		Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text(e.what());
		dlg.run();
		return;
	}
	
	
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
	/*Gtk::TreeModel::Row row = *(tree_model->append());
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
	row[columns.progress] = 5;*/
	
	
	load();
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


void TableServicies::load()
{
	Gtk::TreeModel::Row row;
	std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,"",0,'D');
    if(lstOprs)
	{
		for(auto p : *lstOprs)
		{
			//std::cout << p->getOperation().getID() << std::endl;
			p->downName(connDB);
			
			//>>>			
			row = *(tree_model->append());
			row[columns.service] = p->getOperation().getOperation().getID();
			if(not p->getName().empty()) 	row[columns.name] = p->getName();
			else row[columns.name] = "Desconocido";
			row[columns.progress] = 0;
		}
		for(auto p : *lstOprs)
		{
				delete p;
		}
		delete lstOprs;
	}	
}







TableSaling::TableSaling()
{
	init();
}
void TableSaling::init()
{
	btSave.signal_clicked().connect( sigc::mem_fun(*this,&TableSaling::on_save_clicked));
	
	boxAditional.pack_start(boxName);
	{
			boxName.pack_start(lbName);
			boxName.pack_start(inName);
			lbName.set_text("Nombre : ");
	}
}
TableSaling::~TableSaling()
{
	
}

void TableSaling::on_save_clicked()
{
	save();
}
void TableSaling::save()
{
	if(inName.get_text().size() == 0)
	{
		Gtk::MessageDialog dlg("Validacion de datos",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text("Capture el nombre del cliente, por favor.");
		dlg.run();	
	}
	if(tree_model->children().size() == 0)
	{
		Gtk::MessageDialog dlg("Validacion de datos",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text("Capture los productos que seran vendidos, por favor.");
		dlg.run();	
	}
	//std::cout << "saving..\n";
	Gtk::TreeModel::Row row;
	muposysdb::Ente *ente_service,*ente_operation;
	muposysdb::Stock stock(9);
	muposysdb::Stocking* stocking;
	muposysdb::CatalogItem* cat_item;
	muposysdb::Operation* operation;
	//muposysdb::Progress* operationProgress;
	const Gtk::TreeModel::iterator& last = (tree_model->children().end());	
	int quantity,item;
	ente_service = new muposysdb::Ente;
	if(not ente_service->insert(connDB))
	{
			Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura del ID Stoking.");
			dlg.run();
			return;
	}
	operation = new muposysdb::Operation;
	if(not operation->insert(connDB,*ente_service))
	{
			Gtk::MessageDialog dlg("Error detectado en acceso a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura de Stoking Production.");
			dlg.run();
			return;			
	}
	if(not operation->upStep(connDB,(short)ServiceProgress::created))
	{
			Gtk::MessageDialog dlg("Error detectado en acceso a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura de Stoking Production para step.");
			dlg.run();
			return;		
	}
	
	ente_operation = new muposysdb::Ente;
	if(not ente_operation->insert(connDB))
	{
			Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura del ID Stoking.");
			dlg.run();
			return;
	}
	for(const Gtk::TreeModel::const_iterator& it : tree_model->children())
	{
		if(last == it) break;
		row = *it;
		
		quantity = row[columns.quantity];
		if(quantity == 0) break;
		
		item = row[columns.item];
		
		cat_item = new muposysdb::CatalogItem(item);
		
		cat_item->downType(connDB);
		if(cat_item->getType().compare("service") == 0)
		{
			for(unsigned int i = 0; i < quantity; i++ )
			{
				stocking = new muposysdb::Stocking;
				if(not stocking->insert(connDB,stock,*cat_item,-1))
				{
					Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
					dlg.set_secondary_text("Durante la escritura de Stoking.");
					dlg.run();
					return;
				}
				/*operationProgress = new muposysdb::Progress;
				if(not operationProgress->insert(connDB,*stocking,*operation,0))
				{
					Gtk::MessageDialog dlg("Error detectado en acceso a BD",true,Gtk::MESSAGE_ERROR);
					dlg.set_secondary_text("Durante la escritura de Stoking Production.");
					dlg.run();
					return;			
				}
				delete operationProgress;*/
				delete stocking;
			}
		}
		else
		{
			stocking = new muposysdb::Stocking;
			if(not stocking->insert(connDB,stock,*cat_item,-quantity))
			{
				Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
				dlg.set_secondary_text("Durante la escritura de Stoking.");
				dlg.run();
				return;
			}
			delete stocking;
		}
		
		delete cat_item;
	}
	
	delete ente_service;
	delete ente_operation;	
	
	muposysdb::Sale* sale;
	for(const Gtk::TreeModel::const_iterator& it : tree_model->children())
	{
		if(last == it) break;
		row = *it;
		
		quantity = row[columns.quantity];
		if(quantity == 0) break;
		
		item = row[columns.item];
		cat_item = new muposysdb::CatalogItem(item);
		
		sale = new muposysdb::Sale;
		if(not sale->insert(connDB,*operation,stock,*cat_item,quantity))
		{
			Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura de Stoking.");
			dlg.run();
			return;
		}
		
		delete cat_item;
	}
	
	muposysdb::MiasService service;
	if(not service.insert(connDB,*operation,inName.get_text()))
	{
		Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text("Durante la escritura de Stoking.");
		dlg.run();
		return;
	}
	
	delete operation;
	
	connDB.commit();	
	clear();
	
	Gtk::MessageDialog dlg("Operacion completada.",true,Gtk::MESSAGE_INFO);
	dlg.set_secondary_text("La Venta se realizo satisfactoriamente.");
	dlg.run();	
}






}

