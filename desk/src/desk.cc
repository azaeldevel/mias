
#include <gtkmm/application.h>
#include <muposys/core/muposysdb.hpp>

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






TableServicies::TableServicies() : connDB_flag(false),updaterThread(NULL),lstOprs(NULL),lstProgress(NULL)
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
	append_column("Estado", columns.step);
	//Gtk::CellRenderer* step_reder = static_cast<Gtk::CellRenderer*>(get_column_cell_renderer(get_n_columns() - 1));
	//Gtk::TreeViewColumn* step_column = get_column(get_n_columns() - 1);
	//step_column->set_cell_data_func(*step_reder,sigc::mem_fun(*this,&TableServicies::step_data));
	
	//load();
	dispatcher.connect(sigc::mem_fun(*this, &TableServicies::on_notification_from_worker_thread));
	update_start_stop_buttons();
	on_start_services();
	
	/*auto item = Gtk::make_managed<Gtk::MenuItem>("Hornear", true);
	item->signal_activate().connect(sigc::mem_fun(*this, &TableServicies::on_menu_cooked_popup));
	menu.append(*item);*/
	
	auto item = Gtk::make_managed<Gtk::MenuItem>("Esperando", true);
	item->signal_activate().connect(sigc::mem_fun(*this, &TableServicies::on_menu_waiting_popup));
	menu.append(*item);
	
	item = Gtk::make_managed<Gtk::MenuItem>("Entregar", true);
	item->signal_activate().connect(sigc::mem_fun(*this, &TableServicies::on_menu_deliver_popup));
	menu.append(*item);
	
	menu.accelerate(*this);
	menu.show_all();
	menu.set(*this);
}
TableServicies::~TableServicies()
{
	on_stop_services();
}

TableServicies::ModelColumns::ModelColumns()
{
	add(service);
	add(name);
	add(progress);	
	add(step);	
	add(step_number);	
}

void TableServicies::on_show()
{
	Gtk::TreeView::on_show();
	
	menu.set(*this);
}
void TableServicies::load()
{
	std::cout << "TableServicies::load\n";
	tree_model->clear();
	std::cout << "TableServicies::load : cleaned model\n";
	std::string whereOrder;
	whereOrder = "step >= ";
	whereOrder += std::to_string((int)ServiceStep::created);
	whereOrder += " and step < ";
	whereOrder += std::to_string((int)ServiceStep::delivered);
	std::cout << "TableServicies::load : WHERE :  " << whereOrder << "\n";
	std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder,0,'A');
	std::cout << "TableServicies::load : query done.\n";
    if(lstOprs)
	{
		int pendings,totals;
		float percen;
		for(auto p : *lstOprs)
		{
			p->downStep(connDB);
			std::cout << "TableServicies::load : order " << p->getOperation().getOperation().getID() << "\n";
			pendings = 0;
			totals = 0;
			std::string whereItem;
			whereItem = "operation = ";
			whereItem += std::to_string(p->getOperation().getOperation().getID());
			whereItem += " and step >= ";
			whereItem += std::to_string((int)steping::Pizza::accept);
			whereItem += " and step <=  ";
			whereItem += std::to_string((int)steping::Pizza::finalized);
			//std::cout << "\tTableServicies::load : " << whereItem << "\n";
			std::vector<muposysdb::Progress*>* lstProgress = muposysdb::Progress::select(connDB,whereItem,0,'A');
			std::cout << "\tTableServicies::load : query done.\n";
			if(lstProgress)
			{
				totals = lstProgress->size();
				for(auto progress_item : *lstProgress)
				{
					progress_item->getStocking().downItem(connDB);
					
					std::cout << "\titem : " << progress_item->getStocking().getItem().getItem().getID();
					progress_item->downStep(connDB);
					
					if((steping::Pizza)progress_item->getStep() == steping::Pizza::finalized) pendings++;
				}
			}
			for(auto p : *lstProgress)
			{
					delete p;
			}
			delete lstProgress;
			
			std::cout << "order : " << p->getOperation().getOperation().getID() << "\n";
			std::cout << "pendings : " << pendings << "\n";
			std::cout << "totals : " << totals << "\n";
			if(totals > 0)
			{
				percen = pendings * 100;
				percen /= totals;
				//std::cout << "percen : " << percen <<  "\n";
			}
			else
			{
				percen = 100;
			}
			
			if(pendings > 0)
			{
				p->upStep(connDB,(unsigned char)ServiceStep::working);
			}
			if(pendings == totals)
			{
				p->upStep(connDB,(unsigned char)ServiceStep::waiting);
			}
			
			p->downName(connDB);
			Gtk::TreeModel::Row row;	
			row = *(tree_model->append());
			row[columns.service] = p->getOperation().getOperation().getID();
			std::cout << "columns.service : " << p->getOperation().getOperation().getID() << "\n";
			if(not p->getName().empty()) 	row[columns.name] = p->getName();
			else row[columns.name] = "Desconocido";
			row[columns.progress] = percen;
			row[columns.step_number] = (ServiceStep)p->getStep();
		}
		for(auto p : *lstOprs)
		{
			delete p;
		}
		delete lstOprs;
	}
	connDB.commit();
	
	Gtk::TreeModel::Row row;	
	for(const Gtk::TreeModel::iterator& it : tree_model->children())
	{
		row = *it;
		row[columns.step] = to_text(row[columns.step_number]);
	}
}
bool TableServicies::is_reloadable()
{
	std::cout << "TableServicies::is_reloadable\n";
	bool flret = false;
	std::vector<muposysdb::Progress*>* lstProgress;
	std::cout << "TableServicies::is_reloadable : cleaned model\n";
	std::string whereOrder;
	whereOrder = "step >= ";
	whereOrder += std::to_string((int)ServiceStep::created);
	whereOrder += " and step < ";
	whereOrder += std::to_string((int)ServiceStep::delivered);
	//std::cout << "TableServicies::load : " << whereOrder << "\n";
	std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder,0,'A');
	std::cout << "TableServicies::is_reloadable : query done.\n";
    if(lstOprs)
	{
		int maxItOprs;
		if(this->lstOprs) 
		{
			if(this->lstOprs->size() != lstOprs->size()) flret = true;//reload
			maxItOprs = std::min(this->lstOprs->size(),lstOprs->size());
		}
		else
		{
			maxItOprs = lstOprs->size();
		}
		for(auto p : *lstOprs)
		{
			p->downStep(connDB);
			p->downName(connDB);
		}
		
		for(int i = 0; i < maxItOprs; i++)
		{
			if(this->lstOprs) if(this->lstOprs->at(i)->getOperation().getOperation().getID() != lstOprs->at(i)->getOperation().getOperation().getID()) flret = true;//reload
			if(this->lstOprs) if(this->lstOprs->at(i)->getStep() != lstOprs->at(i)->getStep()) flret = true;//reload
			if(flret) break;
		}
		std::cout << "TableServicies::is_reloadable : readin items.\n";
		for(auto p : *lstOprs)
		{
			std::string whereItem;
			whereItem = "operation = ";
			whereItem += std::to_string(p->getOperation().getOperation().getID());
			whereItem += " and step >= ";
			whereItem += std::to_string((int)steping::Pizza::accept);
			whereItem += " and step <=  ";
			whereItem += std::to_string((int)steping::Pizza::finalized);
			std::cout << "\tTableServicies::is_reloadable : " << whereItem << "\n";
			lstProgress = muposysdb::Progress::select(connDB,whereItem,0,'A');
			std::cout << "\tTableServicies::is_reloadable : query done.\n";
			if(lstProgress)
			{
				int maxItProgress;
				if(this->lstProgress) 
				{
					if(this->lstProgress->size() != lstProgress->size()) flret = true;//reload
					maxItProgress = std::min(this->lstProgress->size(),lstProgress->size());
				}
				else
				{
					maxItProgress = lstProgress->size();
				}
				for(auto p : *lstProgress)
				{
					p->downStep(connDB);
					p->getStocking().downItem(connDB);
					p->getStocking().getItem().downStation(connDB);
				}
				
				for(int i = 0; i < maxItProgress; i++)
				{
					std::cout << "\tTableServicies::is_reloadable : compare steps\n";
					if(this->lstProgress) if(this->lstProgress->at(i)->getStep() != lstProgress->at(i)->getStep()) flret = true;//reload
				}
			}
		}
	}
	std::cout << "TableServicies::is_reloadable : ending done.\n";
	if(flret)
	{
		std::cout << "TableServicies::is_reloadable : free lstOprs.\n";
		if(this->lstOprs)
		{
			for(auto p : *this->lstOprs)
			{
				delete p;
			}
			delete this->lstOprs;
		}
		std::cout << "TableServicies::is_reloadable : free lstProgress.\n";
		if(this->lstProgress)
		{
			for(auto p : *this->lstProgress)
			{
				delete p;
			}
			delete this->lstProgress;
		}
		std::cout << "TableServicies::is_reloadable : copying new params.\n";
		this->lstOprs = lstOprs;
		this->lstProgress = lstProgress;
	}
	else if(not this->lstOprs and not this->lstProgress)
	{
		this->lstOprs = lstOprs;
		this->lstProgress = lstProgress;
	}
	
	return flret;
}
/*
void TableServicies::load()
{
	tree_model->clear();
	Gtk::TreeModel::Row row;	
	std::string whereOrder = "step >= ";
	whereOrder += std::to_string((int)ServiceStep::created);
	whereOrder += " and step <= ";
	whereOrder += std::to_string((int)ServiceStep::delivered);
	std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder,0,'A');
	bool toWorkingService = false;
    if(lstOprs)
	{
		float progress_service;
		for(auto p : *lstOprs)
		{
			progress_service = 0;
			p->downName(connDB);
			
			//>>>			
			row = *(tree_model->append());
			row[columns.service] = p->getOperation().getOperation().getID();
			if(not p->getName().empty()) 	row[columns.name] = p->getName();
			else row[columns.name] = "Desconocido";
			
			std::string whereItem;
			whereItem = "operation = ";
			whereItem += std::to_string(p->getOperation().getOperation().getID());
			//std::cout << "where : " << whereItem << "\n";
			//std::cout << "Orden : " << p->getOperation().getOperation().getID() << "\n";
			std::vector<muposysdb::Progress*>* lstProgress = muposysdb::Progress::select(connDB,whereItem,0,'A');
			short finalizeds;
			if(lstProgress)
			{
				finalizeds = 0;
				for(auto progress_item : *lstProgress)
				{
					progress_item->getStocking().downItem(connDB);
					
					if(progress_item->downStep(connDB))
					{
						//std::cout << "\tStep download\n";
					}
					progress_item->getStocking().getItem().downStation(connDB);
					//s->getStocking().getItem();
					//s->getStocking().getItem().downNumber(connDB);
					//s->getStocking().getItem().downBrief(connDB);
					//std::cout << "\titem : " << progress_item->getStocking().getItem().getItem().getID();
					short step;
					if(progress_item->getStocking().getItem().getStation().compare("pizza") == 0)
					{
						//std::cout << " : pizza";
						float progress_percentage;
						step = progress_item->getStep();
						//std::cout << " : Step " << step;
						if((short)steping::Pizza::none < step and step <= (short)steping::Pizza::finalized )
						{
							 progress_percentage = ((short)steping::Pizza::finalized) - step;
							 //std::cout << " : progress = " << progress_percentage << "\n";
							 progress_percentage /= float(steping::Pizza::finalized);
							 //std::cout << " : progress = " << progress_percentage << "\n";
							 progress_service += progress_percentage;
						}
						else if(step == (short)steping::Pizza::finalized )
						{
							finalizeds++;
						}
						else
						{
							//TODO : si no esta en el rango deve genrar error
						}
					}
					//std::cout << "\n";
				}
				
				for(auto s : *lstProgress)
				{
					delete s;
				}
				delete lstProgress;	
			}
			
			//progress_service /= float(lstProgress->size());
			progress_service *= float(100);
			//std::cout << " : progress_service = " << progress_service << "\n";
			row[columns.progress] = progress_service;
		}
		
		for(auto p : *lstOprs)
		{
				delete p;
		}
		delete lstOprs;
	}
	connDB.commit();
}
*/




TableServicies::Menu::Menu() : parent(NULL)
{
}
TableServicies::Menu::Menu(TableServicies& p) : parent(&p)
{
}
/*void TableServicies::Menu::on_show()
{
	Gtk::Menu::show();
	if(parent->is_runnig) parent->on_stop_services();
}*/

bool 	TableServicies::Menu::on_enter_notify_event (GdkEventCrossing* crossing_event)
{
	if(parent->is_runnig) parent->on_stop_services();
		
	//std::cout << "Showing menu\n";
	return false;
}
/*void 	TableServicies::Menu::on_hide()
{
	std::cout << "Hiding menu\n";
	Gtk::Menu::on_hide();
	//if(parent->is_stop) parent->on_start_services();
	
}*/
void 	TableServicies::Menu::set(TableServicies& p)
{
	parent = &p;
}



void TableServicies::on_start_services()
{
	if (updaterThread)
	{
		std::cout << "Can't start a worker thread while another one is running." << std::endl;
	}
	else
	{
		// Start a new worker thread.
		std::cout << "Starting..\n" << std::endl;
		updaterThread = new std::thread
			(
				[this]
				{
					updater.do_work(this);
				}
			);
	}
  update_start_stop_buttons();
}

void TableServicies::on_stop_services()
{
	if (!updaterThread)
	{
		std::cout << "Can't stop a worker thread. None is running." << std::endl;
	}
	else
	{
	// Order the worker thread to stop.
		updater.stop_work();
		is_stop = true;
		is_runnig = false;
		updaterThread->detach();
		delete updaterThread;
		updaterThread = NULL;
	}
}

void TableServicies::update_start_stop_buttons()
{
	const bool thread_is_running = updaterThread != nullptr;

	is_runnig = thread_is_running;
	//std::cout << "is_runnig is " << (is_runnig? "true" : "false")<< "\n";
	is_stop = !thread_is_running;
	//std::cout << "is_stop is " << (is_stop? "true" : "false")<< "\n";
}

/*void TableServicies::update_widgets()
{
  double fraction_done;
  Glib::ustring message_from_worker_thread;
  m_Worker.get_data(&fraction_done, &message_from_worker_thread);

  m_ProgressBar.set_fraction(fraction_done);

  if (message_from_worker_thread != m_TextView.get_buffer()->get_text())
  {
    auto buffer = m_TextView.get_buffer();
    buffer->set_text(message_from_worker_thread);

    // Scroll the last inserted line into view. That's somewhat complicated.
    Gtk::TextIter iter = buffer->end();
    iter.set_line_offset(0); // Beginning of last line
    auto mark = buffer->get_mark("last_line");
    buffer->move_mark(mark, iter);
    m_TextView.scroll_to(mark);
    // TextView::scroll_to(iter) is not perfect.
    // We do need a TextMark to always get the last line into view.
  }
}*/

void TableServicies::on_quit_services()
{
	if (updaterThread)
	{
		// Order the worker thread to stop and wait for it to stop.
		updater.stop_work();
		if (updaterThread->joinable())
		updaterThread->join();
	}
	//hide();
}

// notify() is called from ExampleWorker::do_work(). It is executed in the worker
// thread. It triggers a call to on_notification_from_worker_thread(), which is
// executed in the GUI thread.
void TableServicies::notify()
{
	dispatcher.emit();
}

void TableServicies::on_notification_from_worker_thread()
{
	//std::cout << "on_notification_from_worker_thread in\n";
	if (updaterThread && updater.has_stopped())
	{
		// Work is done.
		if (updaterThread->joinable())
		updaterThread->join();
		delete updaterThread;
		updaterThread = nullptr;
		update_start_stop_buttons();
	}
	//std::cout << "on_notification_from_worker_thread out\n";
	//update_widgets();
}
void TableServicies::on_menu_cooked_popup()
{
	std::cerr << "TableServicies::on_menu_cooked_popup\n";
	if(serviceSelected > 0) //If anything is selected
	{
		std::string whereOrder;
		whereOrder = "operation = ";
		whereOrder += std::to_string(serviceSelected);
		std::cerr << "whereOrder : " << whereOrder << "\n";
		std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder,0,'A');
		if(lstOprs)
		{
			if(lstOprs->size() != 1)
			{
				std::cerr << "Falo consulta hace MiasService, hay " << lstOprs->size() << ", respuestas cuabndo deve de haber una\n";
				std::cerr << "Filtro  " << whereOrder << "\n";
				return;
			}
			lstOprs->front()->upStep(connDB,(unsigned char)ServiceStep::cooked);
			for(auto p : *lstOprs)
			{
				delete p;
			}
			delete lstOprs;
		}
		connDB.commit();
	}
	else
	{
		std::cerr << "TableServicies::on_menu_cooked_popup - No seleccion fila\n";
	}
}
void TableServicies::on_menu_waiting_popup()
{
	std::cerr << "TableServicies::on_menu_cooked_popup\n";
	if(serviceSelected > 0) //If anything is selected
	{
		std::string whereOrder;
		whereOrder = "operation = ";
		whereOrder += std::to_string(serviceSelected);
		std::cerr << "whereOrder : " << whereOrder << "\n";
		std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder,0,'A');
		if(lstOprs)
		{
			if(lstOprs->size() != 1)
			{
				std::cerr << "Falo consulta hace MiasService, hay " << lstOprs->size() << ", respuestas cuabndo deve de haber una\n";
				std::cerr << "Filtro  " << whereOrder << "\n";
				return;
			}
			lstOprs->front()->upStep(connDB,(unsigned char)ServiceStep::waiting);
			for(auto p : *lstOprs)
			{
				delete p;
			}
			delete lstOprs;
		}
		connDB.commit();
	}
	else
	{
		std::cerr << "TableServicies::on_menu_cooked_popup - No seleccion fila\n";
	}
}
void TableServicies::on_menu_deliver_popup()
{
	std::cerr << "TableServicies::on_menu_deliver_popup\n";
	if(serviceSelected > 0) //If anything is selected
	{
		std::string whereOrder;
		whereOrder = "operation = ";
		whereOrder += std::to_string(serviceSelected);
		std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder,0,'A');
		if(lstOprs)
		{
			if(lstOprs->size() != 1)
			{
				std::cerr << "Falo consulta hace MiasService, hay " << lstOprs->size() << ", respuestas cuabndo deve de haber una\n";
				std::cerr << "Filtro  " << whereOrder << "\n";
				return;
			}
			lstOprs->front()->upStep(connDB,(unsigned char)ServiceStep::delivered);
			for(auto p : *lstOprs)
			{
				delete p;
			}
			delete lstOprs;
		}
	}
	connDB.commit();
}


TableServicies::Updater::Updater() : m_shall_stop(false), m_has_stopped(false)
{	
	try
	{
		connDB_flag = connDB.connect(muposysdb::datconex);
	}
	catch(const std::exception& e)
	{
		/*Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text(e.what());
		dlg.run();*/
		std::cerr << e.what() << "\n";
		return;
	}
}

// Accesses to these data are synchronized by a mutex.
// Some microseconds can be saved by getting all data at once, instead of having
// separate get_fraction_done() and get_message() methods.
/*void TableServicies::Updater::get_data(double* fraction_done, Glib::ustring* message) const
{
  std::lock_guard<std::mutex> lock(m_Mutex);

  if (fraction_done)
    *fraction_done = m_fraction_done;

  if (message)
    *message = m_message;
}*/

void TableServicies::Updater::stop_work()
{
	std::lock_guard<std::mutex> lock(mutex);
	m_shall_stop = true;
}

bool TableServicies::Updater::has_stopped() const
{
	std::lock_guard<std::mutex> lock(mutex);
	return m_has_stopped;
}

void TableServicies::Updater::do_work(TableServicies* caller)
{
	{
		std::lock_guard<std::mutex> lock(mutex);
		m_has_stopped = false;
	} // The mutex is unlocked here by lock's destructor.

	while(not m_shall_stop)
	{
		if(caller->is_reloadable())
		{
			std::cout << "Updating view\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			caller->load();  
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		//caller->notify();
	}

	
	{
		std::lock_guard<std::mutex> lock(mutex);
		m_shall_stop = false;
		m_has_stopped = true;
	}
	
	/*std::cout << "Updating ending\n";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "notify\n";
	caller->notify();
	std::cout << "Updating endded\n";*/
}

bool TableServicies::on_button_press_event(GdkEventButton* button_event)
{
	bool return_value = false;
	if(is_runnig) on_stop_services();
	
	//Call base class, to allow normal handling,
	//such as allowing the row to be selected by the right-click:
	return_value = TreeView::on_button_press_event(button_event);

	//Then do our custom stuff:
	if( (button_event->type == GDK_BUTTON_PRESS) && (button_event->button == 3) )
	{
		Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = get_selection();
		Gtk::TreeModel::iterator itSelected = refTreeSelection->get_selected();
		Gtk::TreeModel::Row rowSelected = *itSelected;
		std::cout << "Selected service : " << rowSelected[columns.service] << " \n";
		serviceSelected = rowSelected[columns.service];
		menu.popup_at_pointer((GdkEvent*)button_event);
	}
	
	return return_value;
}
bool TableServicies::on_enter_notify_event (GdkEventCrossing* crossing_event)
{
	//std::cout << "is_runnig is " << (is_runnig? "true" : "false")<< "\n";
	if(is_runnig) on_stop_services();
	
	return false;
}
bool TableServicies::on_leave_notify_event (GdkEventCrossing* crossing_event)
{
	//std::cout << "is_stop is " << (is_stop? "true" : "false")<< "\n";
	if(is_stop) on_start_services();
	
	return false;
}
/*
bool TableServicies::on_button_release_event(GdkEventButton* button_event)
{
	if(is_stop)
	{
		on_start_button_clicked();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return false;
}*/










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
	muposysdb::Progress* operationProgress;
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
	/*if(not operation->upStep(connDB,(short)ServiceProgress::created))
	{
			Gtk::MessageDialog dlg("Error detectado en acceso a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura de Stoking Production para step.");
			dlg.run();
			return;		
	}*/
	
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
				operationProgress = new muposysdb::Progress;
				if(not operationProgress->insert(connDB,*stocking,*operation,0))
				{
					Gtk::MessageDialog dlg("Error detectado en acceso a BD",true,Gtk::MESSAGE_ERROR);
					dlg.set_secondary_text("Durante la escritura de Stoking Production.");
					dlg.run();
					return;
				}
				delete operationProgress;
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
	if(not service.upStep(connDB,(short)ServiceStep::created))
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

