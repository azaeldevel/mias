
#include <gtkmm/application.h>
#include <muposys/core/muposysdb.hpp>

#include "desk.hh"






namespace mps
{
	SearchItem::SearchItem(Glib::ustring& n) : number(n)
	{
		init();
	}
	void SearchItem::init()
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
		
		set_title("Buscar...");
		
		btCancel.signal_clicked().connect(sigc::mem_fun(*this,&SearchItem::on_bt_cancel_clicked));
		btOK.signal_clicked().connect(sigc::mem_fun(*this,&SearchItem::on_bt_ok_clicked));
		signal_response().connect(sigc::mem_fun(*this, &SearchItem::on_response));
		btOK.set_image_from_icon_name("gtk-ok");
		btCancel.set_image_from_icon_name("gtk-cancel");
		
		//
		//entry->signal_search_changed().connect(sigc::mem_fun(*this, &SearchItem::on_search_text_changed));
		
		//
		get_vbox()->pack_start(bar,false,true);
		bar.connect_entry(entry);
		get_vbox()->pack_start(panel,false,true);
		get_vbox()->pack_start(boxButtons,false,true);
		boxButtons.pack_start(btOK,false,true);
		boxButtons.pack_start(btCancel,false,true);
				
		set_default_size(340,200);
		entry.show();
		bar.show();
		show_all_children();
	}
	

	void SearchItem::on_bt_cancel_clicked()
	{
		response(Gtk::RESPONSE_CANCEL);
	}
	void SearchItem::on_bt_ok_clicked()
	{
		response(Gtk::RESPONSE_OK);
	}
	void SearchItem::on_response(int res)
	{
		if(res == Gtk::RESPONSE_OK)
		{
			hide();
		}
		else
		{
			switch (res)
			{
			case Gtk::RESPONSE_CLOSE:
			case Gtk::RESPONSE_CANCEL:
			case Gtk::RESPONSE_DELETE_EVENT:
				hide();
				break;
			}
		}
	}
	
	muposysdb::CatalogItem* SearchItem::searching(const Glib::ustring& s)
	{
		
		
		return NULL;
	}
	void SearchItem::on_search_text_changed()
	{
		std::cout << "searching : " << entry.get_text() << "\n";
	}
	
	
	
	
	
}



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
	
	item = Gtk::make_managed<Gtk::MenuItem>("Cencelar", true);
	item->signal_activate().connect(sigc::mem_fun(*this, &TableServicies::on_menu_cancel_popup));
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
	add(updated);	
}

void TableServicies::on_show()
{
	Gtk::TreeView::on_show();
	
	menu.set(*this);
}
void TableServicies::load()
{
	bool flcleared = false;
	//std::cout << "TableServicies::load\n";
	//std::cout << "TableServicies::load : cleaned model\n";
	std::string whereOrder;
	whereOrder = "step >= ";
	whereOrder += std::to_string((int)ServiceStep::created);
	whereOrder += " and step < ";
	whereOrder += std::to_string((int)ServiceStep::delivered);
	//std::cout << "TableServicies::load : where :  " << whereOrder << "\n";
	std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder,0,'A');
	//std::cout << "TableServicies::load : query done.\n";
	//Gtk::TreeModel::iterator itRow;
    if(lstOprs)
	{
		if(tree_model->children().size() != lstOprs->size()) 	
		{
			tree_model->clear();
			flcleared = true;
		}
		int finalized,working;
		float percen;
		//std::cout << "\torder count : " << lstOprs->size() << "\n";
		for(int i = 0; i < lstOprs->size(); i++)
		{
			if(lstOprs->at(i)->downUpdated(connDB))
			{
				if(not flcleared) 
				{
					auto itRow = *tree_model->children()[i];
					//std::cout << "TableServicies::load : Service " << itRow[columns.service] << "\n";
					if(lstOprs->at(i)->getUpdated() == itRow[columns.updated] and lstOprs->at(i)->getOperation().getOperation().getID() ==  itRow[columns.service]) continue;
				}
			}
			lstOprs->at(i)->downStep(connDB);
			
			//std::cout << "TableServicies::load : order " << p->getOperation().getOperation().getID() << "\n";
			std::string whereItem;
			whereItem = "operation = ";
			whereItem += std::to_string(lstOprs->at(i)->getOperation().getOperation().getID());
			//std::cout << "\tTableServicies::load : " << whereItem << "\n";
			std::vector<muposysdb::Progress*>* lstProgress = muposysdb::Progress::select(connDB,whereItem,0,'A');
			//std::cout << "\tTableServicies::load : query done.\n";
			
			float percen_order;
			finalized = 0;
			working = 0;
			percen_order = 0;
			int totals_items;
			if(lstProgress)
			{
				totals_items = lstProgress->size();
				for(auto progress_item : *lstProgress)
				{
					//std::cout << "\n";
					if(progress_item->getStocking().downItem(connDB))
					{
						//std::cout << "\t\titem : " << progress_item->getStocking().getItem().getItem().getID() << "\n";
					}
					
					if(progress_item->downStep(connDB))
					{
						//std::cout << "\t\tstep : " << (int)progress_item->getStep() << "\n";
					}
					
					if(progress_item->getStep() < (int)steping::Eat::created or progress_item->getStep() > (int)steping::Eat::finalized) 
					{
						//std::cout << "\t\tstep : jumping item\n";
						continue;
					}
					
					if(progress_item->getStocking().getItem().downStation(connDB))
					{
						/*if((Station)progress_item->getStocking().getItem().getStation() == Station::pizza) std::cout << "\t\tStation : pizza\n";
						else std::cout << "\t\tStation : unknow\n";*/
					}
					
					if((steping::Eat)progress_item->getStep() < steping::Eat::finalized) working++;
					if((steping::Eat)progress_item->getStep() == steping::Eat::finalized) finalized++;
					
					short precen_total = (int)steping::Eat::finalized - (int)steping::Eat::created;
					if(precen_total > 0)
					{
							float percen_item;
							int percen_partial = (int)progress_item->getStep() - (int)steping::Eat::created;
							//std::cout << "\t\tpercen_partial = " << percen_partial << "\n";
							//std::cout << "\t\tprecen_total = " << precen_total << "\n";
							percen_item = float(percen_partial * 100);
							percen_item /= float(precen_total);
							//std::cout << "\t\tpercen_item = " << percen_item << "\n";
							percen_order += percen_item;
					}
					
				}
			}
			//std::cout << "\tpercen_order : " << percen_order <<  "\n";
			percen_order /= float(totals_items);
			//std::cout << "\tpercen_order : " << percen_order <<  "\n";
			
			if(working > 0)
			{
				lstOprs->at(i)->upStep(connDB,(unsigned char)ServiceStep::working);
			}
			if(working == lstOprs->size())
			{
				lstOprs->at(i)->upStep(connDB,(unsigned char)ServiceStep::waiting);
			}
			
			lstOprs->at(i)->downName(connDB);
			Gtk::TreeModel::Row row;	
			row = *(tree_model->append());
			row[columns.service] = lstOprs->at(i)->getOperation().getOperation().getID();
			//std::cout << "columns.service : " << p->getOperation().getOperation().getID() << "\n";
			if(not lstOprs->at(i)->getName().empty()) 	row[columns.name] = lstOprs->at(i)->getName();
			else row[columns.name] = "Desconocido";
			//std::cout << "\tpercen : " << percen_order <<  "\n";
			row[columns.progress] = (int)percen_order;
			row[columns.step_number] = (ServiceStep)lstOprs->at(i)->getStep();
			row[columns.updated] = lstOprs->at(i)->getUpdated();
		}
	}
	connDB.commit();
	
	Gtk::TreeModel::Row row;	
	for(const Gtk::TreeModel::iterator& it : tree_model->children())
	{
		row = *it;
		row[columns.step] = to_text(row[columns.step_number]);
	}
}

void TableServicies::reload()
{
	tree_model->clear();
	load();
}
bool TableServicies::is_reloadable()
{
	//std::cout << "TableServicies::is_reloadable\n";
	bool flret = false;
	std::vector<muposysdb::Progress*>* lstProgress;
	//std::cout << "TableServicies::is_reloadable : cleaned model\n";
	std::string whereOrder;
	whereOrder = "step >= ";
	whereOrder += std::to_string((int)ServiceStep::created);
	whereOrder += " and step < ";
	whereOrder += std::to_string((int)ServiceStep::delivered);
	//std::cout << "TableServicies::load : " << whereOrder << "\n";
	std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder,0,'A');
	//std::cout << "TableServicies::is_reloadable : query done.\n";
    if(lstOprs)
	{
		int maxItOprs;
		if(this->lstOprs) 
		{
			if(this->lstOprs->size() != lstOprs->size()) 
			{
				flret = true;//reload
				//std::cout << "is_reloadable : true devido a las listas de ordenes son de diferente tamaño\n";
			}
			maxItOprs = std::min(this->lstOprs->size(),lstOprs->size());
		}
		else
		{
			maxItOprs = lstOprs->size();
		}
		//std::cout << "maxItOprs : " << maxItOprs << "\n";
		for(auto p : *lstOprs)
		{
			p->downStep(connDB);
			p->downName(connDB);
		}
		
		for(int i = 0; i < maxItOprs; i++)
		{
			if(this->lstOprs) if(this->lstOprs->at(i)->getOperation().getOperation().getID() != lstOprs->at(i)->getOperation().getOperation().getID()) 
			{
				flret = true;//reload
				//std::cout << "is_reloadable : true devido a que el i-esmo elemento de cada lista no corrresponde\n";
			}
			
			if(this->lstOprs) if(this->lstOprs->at(i)->getStep() != lstOprs->at(i)->getStep())
			{
				flret = true;//reload
				//std::cout << "is_reloadable : true devido a que el i-esmo elemento de cada lista no corrresponde en el Step\n";
			}
		}
		//std::cout << "TableServicies::is_reloadable : readin items.\n";
		for(auto p : *lstOprs)
		{
			std::string whereItem;
			whereItem = "operation = ";
			whereItem += std::to_string(p->getOperation().getOperation().getID());
			whereItem += " and step >= ";
			whereItem += std::to_string((int)steping::Eat::accept);
			whereItem += " and step <=  ";
			whereItem += std::to_string((int)steping::Eat::finalized);
			/*whereItem += " and stocking = ";
			whereItem += std::to_string((int)steping::Eat::finalized);*/
			//std::cout << "\tTableServicies::is_reloadable Progress : " << whereItem << "\n";
			lstProgress = muposysdb::Progress::select(connDB,whereItem,0,'A');
			//std::cout << "\tTableServicies::is_reloadable : query done.\n";
			if(lstProgress)
			{
				int maxItProgress;
				if(this->lstProgress) 
				{
					if(this->lstProgress->size() != lstProgress->size()) 
					{
						//std::cout << "is_reloadable : true devido a que el i-esmo elemento de cada lista de progreso no corrresponde en el tamaño\n";
						//std::cout << "this->lstProgress->size() = " << this->lstProgress->size() << ", lstProgress->size() = " <<  lstProgress->size() << "\n";
						flret = true;//reload
					}
					maxItProgress = std::min(this->lstProgress->size(),lstProgress->size());
				}
				else
				{
					maxItProgress = lstProgress->size();
				}
				//std::cout << "maxItProgress : " << maxItProgress << "\n";
				for(auto p : *lstProgress)
				{
					p->downStep(connDB);
					p->getStocking().downItem(connDB);
					p->getStocking().getItem().downStation(connDB);
				}
				
				for(int i = 0; i < maxItProgress; i++)
				{
					if(this->lstProgress) if(this->lstProgress->at(i)->getStep() != lstProgress->at(i)->getStep())
					{
						flret = true;//reload
						//std::cout << "is_reloadable : true devido a que el i-esmo elemento de cada lista no corrresponde con el Step\n";
					}
				}
			}
		}
	}
	//std::cout << "TableServicies::is_reloadable : ending done.\n";
	if(flret)
	{
		//std::cout << "TableServicies::is_reloadable : free lstOprs.\n";
		if(this->lstOprs)
		{
			for(auto p : *this->lstOprs)
			{
				delete p;
			}
			delete this->lstOprs;
		}
		//std::cout << "TableServicies::is_reloadable : free lstProgress.\n";
		if(this->lstProgress)
		{
			for(auto p : *this->lstProgress)
			{
				delete p;
			}
			delete this->lstProgress;
		}
		//std::cout << "TableServicies::is_reloadable : copying new params.\n";
		this->lstOprs = lstOprs;
		this->lstProgress = lstProgress;
	}
	else if(not this->lstOprs and not this->lstProgress)
	{
		this->lstOprs = lstOprs;
		this->lstProgress = lstProgress;
		flret = true;
		//std::cout << "is_reloadable : true devido a que no hay registros cargados\n";
	}
	
	connDB.commit();
	//std::cout << "is_reloadable : " << (flret? "true" : "false")<< "\n";
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
						if((short)steping::Eat::none < step and step <= (short)steping::Eat::finalized )
						{
							 progress_percentage = ((short)steping::Eat::finalized) - step;
							 //std::cout << " : progress = " << progress_percentage << "\n";
							 progress_percentage /= float(steping::Eat::finalized);
							 //std::cout << " : progress = " << progress_percentage << "\n";
							 progress_service += progress_percentage;
						}
						else if(step == (short)steping::Eat::finalized )
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
bool TableSaling::on_key_press_event(GdkEventKey* event)
{
	std::cout << "on_key_press_event\n";
	if (event->type == GDK_KEY_PRESS and event->keyval == GDK_KEY_F4)
	{
		std::cout << "on_key_press_event F4 begin\n";
		Glib::ustring number;
		mps::SearchItem search(number);
		int res = search.run();
		std::cout << "on_key_press_event F4 end\n";
	}
	return false;
}




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
		//std::cout << "Can't start a worker thread while another one is running." << std::endl;
	}
	else
	{
		// Start a new worker thread.
		//std::cout << "Starting..\n" << std::endl;
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
		//std::cout << "Can't stop a worker thread. None is running." << std::endl;
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
	//std::cerr << "TableServicies::on_menu_cooked_popup\n";
	bool flag = false;
	if(serviceSelected > 0) //If anything is selected
	{
		std::string whereOrder;
		whereOrder = "operation = ";
		whereOrder += std::to_string(serviceSelected);
		//std::cerr << "whereOrder : " << whereOrder << "\n";
		std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder,0,'A');
		if(lstOprs)
		{
			if(lstOprs->size() != 1)
			{
				//std::cerr << "Falo consulta hace MiasService, hay " << lstOprs->size() << ", respuestas cuabndo deve de haber una\n";
				//std::cerr << "Filtro  " << whereOrder << "\n";
				lstOprs->front()->upStep(connDB,(unsigned char)ServiceStep::cooked);
				flag = true;
			}
			for(auto p : *lstOprs)
			{
				delete p;
			}
			delete lstOprs;
		}
	}
	connDB.commit();
	if(flag) reload();
}
void TableServicies::on_menu_waiting_popup()
{
	//std::cerr << "TableServicies::on_menu_cooked_popup\n";
	bool flag = false;
	if(serviceSelected > 0) //If anything is selected
	{
		std::string whereOrder;
		whereOrder = "operation = ";
		whereOrder += std::to_string(serviceSelected);
		//std::cerr << "whereOrder : " << whereOrder << "\n";
		std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder,0,'A');
		if(lstOprs)
		{
			if(lstOprs->size() == 1)
			{
				//std::cerr << "Falo consulta hace MiasService, hay " << lstOprs->size() << ", respuestas cuabndo deve de haber una\n";
				//std::cerr << "Filtro  " << whereOrder << "\n";
				lstOprs->front()->upStep(connDB,(unsigned char)ServiceStep::waiting);
				flag = true;
			}
			for(auto p : *lstOprs)
			{
				delete p;
			}
			delete lstOprs;
		}
	}
	connDB.commit();
	if(flag) reload();
}
void TableServicies::on_menu_deliver_popup()
{
	//std::cerr << "TableServicies::on_menu_deliver_popup\n";
	bool flag = false;
	if(serviceSelected > 0) //If anything is selected
	{
		std::string whereOrder;
		whereOrder = "operation = ";
		whereOrder += std::to_string(serviceSelected);
		std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder,0,'A');
		if(lstOprs)
		{
			if(lstOprs->size() == 1)
			{
				//std::cerr << "Falo consulta hace MiasService, hay " << lstOprs->size() << ", respuestas cuabndo deve de haber una\n";
				//std::cerr << "Filtro  " << whereOrder << "\n";
				lstOprs->front()->upStep(connDB,(unsigned char)ServiceStep::delivered);
				flag = true;
			}
			for(auto p : *lstOprs)
			{
				delete p;
			}
			delete lstOprs;
		}
	}
	connDB.commit();
	if(flag) reload();	
}
void TableServicies::on_menu_cancel_popup()
{
	//std::cerr << "TableServicies::on_menu_deliver_popup\n";
	bool flag = false;
	if(serviceSelected > 0) //If anything is selected
	{
		std::string whereOrder;
		whereOrder = "operation = ";
		whereOrder += std::to_string(serviceSelected);
		std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder,0,'A');
		if(lstOprs)
		{
			if(lstOprs->size() == 1)
			{
				//std::cerr << "Falo consulta hace MiasService, hay " << lstOprs->size() << ", respuestas cuabndo deve de haber una\n";
				//std::cerr << "Filtro  " << whereOrder << "\n";
				lstOprs->front()->upStep(connDB,(unsigned char)ServiceStep::cancel);
				flag = true;
			}
			for(auto p : *lstOprs)
			{
				delete p;
			}
			delete lstOprs;
		}
	}
	connDB.commit();
	if(flag)reload();
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
		caller->load();
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
		//std::cout << "Selected service : " << rowSelected[columns.service] << " \n";
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
				if(not stocking->insert(connDB,stock,*cat_item,1))
				{
					Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
					dlg.set_secondary_text("Durante la escritura de Stoking.");
					dlg.run();
					return;
				}
				operationProgress = new muposysdb::Progress;
				if(not operationProgress->insert(connDB,*stocking,*operation,(signed char)steping::Eat::created))
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
			if(not stocking->insert(connDB,stock,*cat_item,quantity))
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

