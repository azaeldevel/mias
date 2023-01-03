
/**
 *  This file is part of mias.
 *  mias is a muposys's implementation.
 *  Copyright (C) 2022  Azael Reyes
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * */


#include <gtkmm/application.h>

#include "desk.hh"






namespace mps
{
	const Glib::ustring SearchItem::search_label = "Buscar...";
	
	SearchItem::SearchItem(long& n) : number(n)
	{
		init();
	}
	void SearchItem::init()
	{
		number = -1;
		
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

		set_title(search_label);
		
		//
		treemodel = Gtk::ListStore::create(colums);
		tree.set_model(treemodel);
		tree.append_column("Número", colums.number);
		tree.append_column("Nombre", colums.name);
		tree.append_column("Descripcción", colums.brief);
		scrolled.add(tree);
		scrolled.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
		get_vbox()->pack_start(scrolled);

		btCancel.signal_clicked().connect(sigc::mem_fun(*this,&SearchItem::on_bt_cancel_clicked));
		btOK.signal_clicked().connect(sigc::mem_fun(*this,&SearchItem::on_bt_ok_clicked));
		signal_response().connect(sigc::mem_fun(*this, &SearchItem::on_response));
		btOK.set_image_from_icon_name("gtk-ok");
		btCancel.set_image_from_icon_name("gtk-cancel");
		
		get_vbox()->pack_start(boxButtons,false,true);
		boxButtons.pack_start(btOK,false,true);
		boxButtons.pack_start(btCancel,false,true);

		set_default_size(340,200);
		show_all_children();
	}


	void SearchItem::on_bt_cancel_clicked()
	{
		response(Gtk::RESPONSE_CANCEL);
	}
	void SearchItem::on_bt_ok_clicked()
	{
		get_selection();
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

	bool SearchItem::on_key_press_event(GdkEventKey* event)
	{
		if (event->keyval >= 97 and event->keyval <= 122)//letras minisculas
		{
			//std::cout << "key : " << (char)event->keyval << "\n";
			text.push_back((char)event->keyval);
			searching(text);
		}
		else if (event->keyval >= 65 and event->keyval <= 90)//letras mayusculas
		{
			//std::cout << "key : " << (char)event->keyval << "\n";
			text.push_back((char)event->keyval);
			searching(text);
		}
		else if (event->keyval == 32)//space
		{
			//std::cout << "key : " << (char)event->keyval << "\n";
			text.push_back((char)event->keyval);
			searching(text);
		}
		else if (event->keyval == 45)//gion
		{
			//std::cout << "key : " << (char)event->keyval << "\n";
			text.push_back((char)event->keyval);
			searching(text);
		}
		else if (event->keyval == GDK_KEY_Return)
		{
			std::cout << "key : Enter\n";
			get_selection();
		}
		else if (event->keyval == GDK_KEY_Escape)
		{
			//std::cout << "key : Enter\n";
			text = "";
			set_title(search_label);
			treemodel->clear();
		}
		else if (event->keyval == GDK_KEY_BackSpace)
		{
			//std::cout << "key : Enter\n";
			Glib::ustring::iterator it = text.end();
			if(text.size() > 0) 
			{
				--it;
				text.erase(it);
				set_title(search_label + " " + text);
				searching(text);
			}
			else if(text.size() == 0)
			{
				treemodel->clear();
			}
				
		}
		else
		{
			//std::cout << "key : " << event->keyval << "\n";
		}
		
		return false;
	}

SearchItem::ModelColumns::ModelColumns()
{
	add(id);
	add(number);
	add(name);
	add(brief);
}

void SearchItem::searching(const Glib::ustring& s)
{
	//std::cout << "key : " << text << "\n";
	Glib::ustring where;
	where += "number LIKE '%";
	where += text + "%'";
	where += " or brief LIKE '%";
	where += text + "%'";
	where += " or name LIKE '%";
	where += text + "%'";
	where += " or size LIKE '%";
	where += text + "%'";
	//std::cout << "where : " << where << "\n";	
	set_title(search_label + " " + text);
	std::vector<muposysdb::CatalogItem*>* lstItem = muposysdb::CatalogItem::select(connDB,where);
	if(lstItem)
	{
		Gtk::TreeModel::Row row;
		treemodel->clear();
		//std::cout << "i : " << lstItem->size() << "\n";
		for(size_t i = 0; i < lstItem->size(); i++)
		{
			lstItem->at(i)->downNumber(connDB);
			lstItem->at(i)->downName(connDB);
			lstItem->at(i)->downBrief(connDB);
			
			row = *(treemodel->append());
			row[colums.id] = lstItem->at(i)->getID();
			row[colums.number] = lstItem->at(i)->getNumber();
			row[colums.name] = lstItem->at(i)->getName();
			row[colums.brief] = lstItem->at(i)->getBrief();
		}
		
		for(auto p : *lstItem)
		{
			delete p;
		}
		delete lstItem;
	}
}
void SearchItem::get_selection()
{
	Glib::RefPtr<Gtk::TreeSelection> refSelection = tree.get_selection();
	Gtk::TreeModel::iterator iter = refSelection->get_selected();
	if(iter) //If anything is selected
	{
		Gtk::TreeModel::Row row = *iter;
		number = row[colums.id];
		response(Gtk::RESPONSE_OK);
	}
	else if(treemodel->children().size() > 0)
	{
		Gtk::TreeModel::Row row = treemodel->children()[0];
		number = row[colums.id];
		response(Gtk::RESPONSE_OK);
	}
	
}

}



namespace mias
{


bool stepping(mps::Connector& connDB, long order,ServiceStep step)
{
	bool flret = false;
    std::string whereOrder;
    whereOrder = "operation = ";
    whereOrder += std::to_string(order);
    //std::cout << "stepping - Order : " << order << "\n";
    //std::cout << "stepping - whereOrder : " << whereOrder << "\n";
    std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder);
    if(lstOprs)
    {
        if(lstOprs->size() == 1)
        {
            if(lstOprs->front()->upStep(connDB,(short)step)) flret = true;
        }
        else
        {
            flret = false;
            //std::cout << " stepping lstOprs->size : " << lstOprs->size() << "\n";
        }
        for(auto p : *lstOprs)
        {
            delete p;
        }
        delete lstOprs;
    }

    return flret;
}

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
	//std::cout << " Mias::init step 1\n";
	add_events(Gdk::KEY_PRESS_MASK);
	set_title("Mia's Pizza & Pasta");
	set_default_size(800,640);
	btSales.set_icon_name("gtk-add");
	tbMain.add(btSales);
	show_all_children();
	
	//std::cout << " Mias::init step 2\n";
	
	btSales.signal_clicked().connect(sigc::mem_fun(*this, &Mias::on_click_sales));
	
	//std::cout << " Mias::init step 3\n";
}
Mias::~Mias()
{
	for(Sales* s : sale)
	{
		delete s;
	}
}

void Mias::on_click_sales()
{
	Sales* snow = new Sales(this);
	sale.push_back(snow);
	//std::cout << " Mias::on_click_sales step 1\n";
	nbMain.append_page(*snow);
	snow->set(get_user());
	//std::cout << " Mias::on_click_sales step 2\n";
	btSales.set_sensitive(false);
	nbMain.show_all_children();
	//sale.show_all_children();
	//std::cout << " Mias::on_click_sales step 3\n";
}
Sales& Mias::create_activity_sale()
{
    Sales* snow = new Sales(this);
	sale.push_back(snow);
	//std::cout << " Mias::on_click_sales step 1\n";
	nbMain.append_page(*snow);
	snow->set(get_user());
	snow->show_all();

	return *snow;
}
Sales& Mias::create_activity_sale(long o)
{
    Sales* snow = new Sales(this,o);
	sale.push_back(snow);
	//std::cout << " Mias::on_click_sales step 1\n";
	nbMain.append_page(*snow);
	Glib::ustring title = "Order - " + std::to_string(o);
	nbMain.set_tab_label_text((Gtk::Widget&)*snow,title);
	snow->set(get_user());
	snow->show_all();

	return *snow;
}



Sales::Sales(Mias* m) : user(NULL),pending(m)
{
	init();
}
Sales::Sales(Mias* m,long o) : user(NULL),pending(m),saling(o)
{
	std::cout << "Sales::Sales(app," << o << ")\n";
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
void Sales::set(const muposysdb::User& u)
{
	user = &u;
	saling.set(u);
}













Saling::Saling() : Gtk::Box(Gtk::ORIENTATION_VERTICAL),user(NULL)
{
	init();
}
Saling::Saling(long o) : Gtk::Box(Gtk::ORIENTATION_VERTICAL),user(NULL),table(o)
{
	std::cout << "Saling::Saling(" << o << ")\n";
	init();
}
void Saling::init()
{
	pack_start(table,false,false);
}
Saling::~Saling()
{
}
void Saling::set(const muposysdb::User& u)
{
	user = &u;
	table.set(u);
}





PendingServices::PendingServices(Mias* m) : Gtk::Box(Gtk::ORIENTATION_VERTICAL),mias(m),servicies(m)
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






TableServicies::TableServicies(Mias* m) : updaterThread(NULL),serviceSelected(0),mias(m)
{
	//std::cout << "TableServicies::TableServicies step 1\n";
	init();
	//std::cout << "TableServicies::TableServicies step 2\n";
}
void TableServicies::init()
{
	//std::cout << "TableServicies::init step 1\n";

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
	append_column("Estado", columns.step_str);

	dispatcher.connect(sigc::mem_fun(*this, &TableServicies::on_notification_from_worker_thread));
	update_start_stop_buttons();
	on_start_services();

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
	//std::cout << "TableServicies::init step 3\n";
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
	add(step_str);
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

    mps::Connector connDB;
	bool connDB_flag;
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

	std::string whereOrder;
	whereOrder = "step >= ";
	whereOrder += std::to_string((short)ServiceStep::created);
	whereOrder += " and step < ";
	whereOrder += std::to_string((short)ServiceStep::delivered);

	std::vector<muposysdb::MiasService*>* lstOprs = muposysdb::MiasService::select(connDB,whereOrder,0,'A');

	int counJobs = 0;
	//tree_model->clear();
    if(lstOprs)
	{
		if(tree_model->children().size() != lstOprs->size())
		{
			flcleared = true;
		}

		int working;
		float percen;
		//std::cout << "\torder count : " << lstOprs->size() << "\n";
		for(int i = 0; i < lstOprs->size(); i++)
		{
			//std::cout << "\ti : " << i << "\n";
			lstOprs->at(i)->downUpdated(connDB);
			lstOprs->at(i)->downName(connDB);
			lstOprs->at(i)->downStep(connDB);
			if(i < tree_model->children().size())
            {
                auto itRowUpdated = *tree_model->children()[i];
                if(lstOprs->at(i)->getOperation().getID() ==  itRowUpdated[columns.service] and lstOprs->at(i)->getUpdated() <= itRowUpdated[columns.updated]) continue;
            }
			//std::cout << "\ti : "  << i << "\n";
			//std::cout << "\ti : "  << i << "\n";

			//std::cout << "\tTableServicies::load : order " << lstOprs->at(i)->getOperation().getID() << "\n";
			std::string whereItem;
			whereItem = "operation = ";
			whereItem += std::to_string(lstOprs->at(i)->getOperation().getID());
			//std::cout << "\tTableServicies::load : " << whereItem << "\n";
			std::vector<muposysdb::Progress*>* lstProgress = muposysdb::Progress::select(connDB,whereItem,0,'A');
			//std::cout << "\tTableServicies::load : query done.\n";

			float percen_order;
			//finalized = 0;
			working = 0;
			percen_order = 0;
			int totals_items;
			if(lstProgress)
			{
				totals_items = lstProgress->size();
				for(auto progress_item : *lstProgress)
				{
					//std::cout << "\tTableServicies::load Step 1\n";
					if(progress_item->downStocking(connDB))
					{
						//std::cout << "\t\titem : " << progress_item->getStocking().getItem().getItem().getID() << "\n";
					}
					if(progress_item->getStocking().downItem(connDB))
					{
						//std::cout << "\t\titem : " << progress_item->getStocking().getItem().getItem().getID() << "\n";
					}

					//std::cout << "\tTableServicies::load Step 2\n";
					if(progress_item->downStep(connDB))
					{
						//std::cout << "\t\tstep : " << (int)progress_item->getStep() << "\n";
					}

					//std::cout << "\tTableServicies::load Step 3\n";
					if(progress_item->getStep() < (int)Eating::created or progress_item->getStep() > (int)Eating::finalized)
					{
						//std::cout << "\t\tstep : jumping item\n";
						continue;
					}

					//std::cout << "\tStep 4\n";
					if(progress_item->getStocking().getItem().downStation(connDB))
					{
						/*if((Station)progress_item->getStocking().getItem().getStation() == Station::pizza) std::cout << "\t\tStation : pizza\n";
						else std::cout << "\t\tStation : unknow\n";*/
					}
					if(progress_item->getStocking().getItem().getStation() != (short)Station::none) counJobs++;

					//std::cout << "\tStep 5\n";
					if((Eating)progress_item->getStep() < Eating::finalized and (Eating)progress_item->getStep() >  Eating::accepted ) working++;
					//if((Eating)progress_item->getStep() == Eating::finalized) finalized++;

					//std::cout << "\tStep 6\n";
					int precen_total = (int)Eating::finalized - (int)Eating::created;
					if(precen_total > 0)
					{
						float percen_item;
						int percen_partial = (int)progress_item->getStep() - (int)Eating::created;
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
				lstOprs->at(i)->upStep(connDB,(short)ServiceStep::working);
				//flreload = true;
			}
			if(percen_order > 99.0)
			{
				lstOprs->at(i)->upStep(connDB,(short)ServiceStep::waiting);
				//flreload = true;
			}


			Gtk::TreeModel::Row row;
			if(i < tree_model->children().size())
            {
                row = tree_model->children()[i];
            }
            else
            {
                row = *(tree_model->append());
            }
			row[columns.service] = lstOprs->at(i)->getOperation().getID();
			//std::cout << "columns.service : " << lstOprs->at(i)->getOperation().getID() << "\n";
			if(not lstOprs->at(i)->getName().empty()) 	row[columns.name] = lstOprs->at(i)->getName();
			else row[columns.name] = "Desconocido";
			//std::cout << "\tpercen : " << percen_order <<  "\n";
			row[columns.progress] = (int)(percen_order > 0 ? percen_order : 0);
			//std::cout << "columns.progress : " << percen_order << "\n";
			row[columns.step_number] = (ServiceStep)(short)lstOprs->at(i)->getStep();
			row[columns.updated] = lstOprs->at(i)->getUpdated();
			row[columns.step_str] = to_text((ServiceStep)lstOprs->at(i)->getStep());
			//std::cout << "columns.step : " << lstOprs->at(i)->getStep() << "\n";
			//std::cout << "columns.step : " << to_text((ServiceStep)lstOprs->at(i)->getStep()) << "\n";
		}
		connDB.commit();
	}
	connDB.close();
}

void TableServicies::reload()
{
	tree_model->clear();
	load();
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

bool TableServicies::Menu::on_enter_notify_event (GdkEventCrossing* crossing_event)
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
void TableServicies::Menu::set(TableServicies& p)
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
}
void TableServicies::on_menu_cooked_popup()
{
    std::cout << "on_menu_cooked_popup - serviceSelected : " << serviceSelected << " \n";
	if(serviceSelected < 0) return;

	bool connDB_flag;
	mps::Connector connDB;
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

	bool flag = stepping(connDB,serviceSelected,ServiceStep::cooked);

	if(flag)
    {
        connDB.commit();
        reload();
	}
	connDB.close();
}
void TableServicies::on_menu_waiting_popup()
{
    std::cout << "on_menu_waiting_popup - serviceSelected : " << serviceSelected << " \n";
	if(serviceSelected < 0) return;

	//std::cerr << "TableServicies::on_menu_cooked_popup\n";
    bool connDB_flag;
	mps::Connector connDB;
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

	bool flag = stepping(connDB,serviceSelected,ServiceStep::waiting);

	if(flag)
    {
        connDB.commit();
        reload();
	}
	connDB.close();
}
void TableServicies::on_menu_deliver_popup()
{
    std::cout << "on_menu_deliver_popup - serviceSelected : " << serviceSelected << " \n";
	if(serviceSelected < 0) return;

	//std::cerr << "TableServicies::on_menu_deliver_popup\n";
	bool connDB_flag;
	mps::Connector connDB;
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

	bool flag = stepping(connDB,serviceSelected,ServiceStep::delivered);

	if(flag)
    {
        connDB.commit();
        reload();
	}
	connDB.close();
}
void TableServicies::on_menu_cancel_popup()
{
    std::cout << "on_menu_cancel_popup - serviceSelected : " << serviceSelected << " \n";
	if(serviceSelected < 0) return;

	//std::cerr << "TableServicies::on_menu_deliver_popup\n";
	bool connDB_flag;
	mps::Connector connDB;
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

	bool flag = stepping(connDB,serviceSelected,ServiceStep::cancel);

	if(flag)
    {
        connDB.commit();
        reload();
	}
	connDB.close();
}

TableServicies::Updater::Updater() : m_shall_stop(false), m_has_stopped(false)
{
	/*try
	{
		connDB_flag = connDB.connect(muposysdb::datconex);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << "\n";
		return;
	}*/
}


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
}

bool TableServicies::on_button_press_event(GdkEventButton* button_event)
{
	bool return_value = false;
	if(is_runnig) on_stop_services();

	//Call base class, to allow normal handling,
	//such as allowing the row to be selected by the right-click:
	return_value = TreeView::on_button_press_event(button_event);

	//Then do our custom stuff:
	if((button_event->type == GDK_BUTTON_PRESS) && (button_event->button == 3))
	{
		Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = get_selection();
		Gtk::TreeModel::iterator itSelected = refTreeSelection->get_selected();
		Gtk::TreeModel::Row rowSelected = *itSelected;
		//std::cout << "Selected service : " << rowSelected[columns.service] << " \n";
		serviceSelected = rowSelected[columns.service];
		//std::cout << "serviceSelected : " << serviceSelected << " \n";
		menu.popup_at_pointer((GdkEvent*)button_event);
	}
	else if((button_event->type == GDK_DOUBLE_BUTTON_PRESS))
	{
		Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = get_selection();
		Gtk::TreeModel::iterator itSelected = refTreeSelection->get_selected();
		Gtk::TreeModel::Row rowSelected = *itSelected;
		//std::cout << "Selected service : " << rowSelected[columns.service] << " \n";
		serviceSelected = rowSelected[columns.service];

		//std::cout << "Doble-click detected\n";
		Sales& snow = mias->create_activity_sale(serviceSelected);
	}

	return return_value;
}
bool TableServicies::on_enter_notify_event (GdkEventCrossing* crossing_event)
{
	if(is_runnig) on_stop_services();

	return false;
}
bool TableServicies::on_leave_notify_event (GdkEventCrossing* crossing_event)
{
	if(is_stop) on_start_services();

	return false;
}
bool TableServicies::on_key_press_event(GdkEventKey* event)
{
	if (event->keyval == GDK_KEY_Return)
	{
		Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = get_selection();
		Gtk::TreeModel::iterator itSelected = refTreeSelection->get_selected();
		Gtk::TreeModel::Row rowSelected = *itSelected;
		//std::cout << "Selected service : " << rowSelected[columns.service] << " \n";
		serviceSelected = rowSelected[columns.service];
		//std::cout << "serviceSelected : " << serviceSelected << " \n";
		menu.popup_at_pointer((GdkEvent*)event);
	}
	
	return false;
}







TableSaling::TableSaling() : user(NULL),rdllevar("Llevar"),rdaqui("Aquí"),frame("Final")
{
    //std::cout << "mias::TableSaling::TableSaling()\n";
	init();
}
TableSaling::TableSaling(long o) : mps::TableSaling(o),user(NULL),rdllevar("Llevar"),rdaqui("Aquí"),frame("Final")
{
    //std::cout << "mias::TableSaling::TableSaling(" << o << ")\n";
	init();
	load_order(o);
}
void TableSaling::init()
{
    //std::cout << "mias::TableSaling::init mode : " << (short)crud << "\n";

	if(crud == mps::Crud::create)
    {
        btSave.signal_clicked().connect( sigc::mem_fun(*this,&TableSaling::on_save_clicked));
    }
    else if(crud == mps::Crud::read)
    {
        btSave.set_sensitive(false);
    }

    if(crud == mps::Crud::create)
    {
        Gtk::CellRendererText* cell_number = static_cast<Gtk::CellRendererText*>(table.get_column_cell_renderer(2));
        Gtk::TreeViewColumn* col_number = table.get_column(2);
        cell_number->property_editable() = true;
        cell_number->signal_edited().connect(sigc::mem_fun(*this, &TableSaling::cellrenderer_validated_on_edited_number));
    }
	
	boxAditional.pack_start(boxName);
	{
		boxName.pack_start(lbName);
		boxName.pack_start(inName);
		lbName.set_text("Nombre : ");
	}

	boxFloor.pack_end(frame);
	{
		frame.add(boxFrame);
		boxFrame.pack_start(rdllevar);
		boxFrame.pack_start(rdaqui);
		rdllevar.join_group(rdaqui);
		rdllevar.set_active(true);
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
	//std::cout << "saving :step 1\n";
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

	//std::cout << "saving :step 2\n";
	Gtk::TreeModel::Row row;
	//muposysdb::Ente *ente_service,*ente_operation;
	muposysdb::Stock stock(2);
	muposysdb::Stocking* stocking;
	muposysdb::CatalogItem* cat_item;
	muposysdb::Operation* operation;
	muposysdb::Progress* operationProgress;
	muposysdb::StockingCombined* combined;
	const Gtk::TreeModel::iterator& last = (tree_model->children().end());
	int quantity,item;
	//std::cout << "saving :step 3\n";
	operation = new muposysdb::Operation;
	if(not operation->insert(connDB))
	{
			Gtk::MessageDialog dlg("Error detectado en acceso a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura de Stoking Production.");
			dlg.run();
			return;
	}
	//std::cout << "saving :step 4\n";

	//std::cout << "saving :step 5\n";
	for(const Gtk::TreeModel::const_iterator& it : tree_model->children())
	{
		//std::cout << "saving :step 5.1\n";
		if(last == it) break;
		row = *it;

		//std::cout << "saving :step 5.2\n";
		quantity = row[columns.quantity];
		if(quantity == 0) break;

		item = row[columns.item];

		//std::cout << "saving :step 5.3\n";
		cat_item = new muposysdb::CatalogItem(item);

		//std::cout << "saving :step 5.4\n";
		cat_item->downType(connDB);
		//std::cout << "saving :step 5.5\n";
		if((ItemType)cat_item->getType() == ItemType::service)
		{
			for(unsigned int i = 0; i < quantity; i++ )
			{
				//std::cout << "saving :step 5.5.1\n";
				stocking = new muposysdb::Stocking;
				//std::cout << "saving :step 5.5.2\n";
				if(not stocking->insert(connDB,stock,*cat_item,1))
				{
					Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
					dlg.set_secondary_text("Durante la escritura de Stoking.");
					dlg.run();
					return;
				}
				//std::cout << "saving :step 5.5.3\n";
				operationProgress = new muposysdb::Progress;
				//std::cout << "saving :step 5.5.4\n";

				//std::cout << "TableSaling user : " << user << "\n";
				//muposysdb::User user(2);
				//if(not user) throw Exception(Exception::INTERNAL_ERROR,__FILE__,__LINE__);
				if(not operationProgress->insert(connDB,*stocking,*operation,(short)Eating::created))
				{
					Gtk::MessageDialog dlg("Error detectado en acceso a BD",true,Gtk::MESSAGE_ERROR);
					dlg.set_secondary_text("Durante la escritura de Stoking Production.");
					dlg.run();
					return;
				}

				std::vector<muposysdb::CatalogItem> items = get_items(row[columns.number]);
				if(items.size() == 2)
				{
					combined = new muposysdb::StockingCombined;
					combined->insert(connDB,*stocking,items[0],items[1]);
					delete combined;
				}

				//std::cout << "saving :step 5.5.5\n";
				delete operationProgress;
				//std::cout << "saving :step 5.5.6\n";
				delete stocking;
				//std::cout << "saving :step 5.5.7\n";
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
		//std::cout << "saving :step 5.6\n";
	}
	//std::cout << "saving :step 6\n";

	//delete ente_service;
	//delete ente_operation;

	//std::cout << "saving :step 7\n";
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
	//std::cout << "saving :step 8\n";

	muposysdb::MiasService service;
	if(not service.insert(connDB,*operation,inName.get_text()))
	{
		Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text("Durante la escritura de Stoking.");
		dlg.run();
		return;
	}
	//std::cout << "saving :step 9\n";
	if(not service.upStep(connDB,(short)ServiceStep::created))
	{
		Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
		dlg.set_secondary_text("Durante la escritura de Stoking.");
		dlg.run();
		return;
	}
	if(rdllevar.get_active())
	{
		if(not service.upLocation(connDB,(short)Location::deliver))
		{
			Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura de Stoking.");
			dlg.run();
			return;
		}
	}
	else if(rdaqui.get_active())
	{
		if(not service.upLocation(connDB,(short)Location::here))
		{
			Gtk::MessageDialog dlg("Error detectado en acces a BD",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Durante la escritura de Stoking.");
			dlg.run();
			return;
		}
	}
	//std::cout << "saving :step 10\n";
	delete operation;

	//std::cout << "saving :step 11\n";
	connDB.commit();
	clear();

	//std::cout << "saving :step 12\n";

	Gtk::MessageDialog dlg("Operacion completada.",true,Gtk::MESSAGE_INFO);
	dlg.set_secondary_text("La Venta se realizo satisfactoriamente.");
	dlg.run();
}
void TableSaling::clear()
{
	tree_model->clear();
	newrow();
	lbTotalAmount.set_text("");
	inName.set_text("");
}
void TableSaling::set(const muposysdb::User& u)
{
	user = &u;
}
void TableSaling::cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& strnumb)
{
	Gtk::TreePath path(path_string);
	Glib::ustring number,combinedstr;
	bool combined = false;
	const std::vector<Glib::ustring> numbers = split(strnumb);
	if(numbers.size() == 2)
	{
		combined = true;
		//std::cout << "firts : '" << numbers[0] << "'\n";
		//std::cout << "second : '" << numbers[1] << "'\n";
		if(numbers[0][0] != numbers[1][0])
		{
			Gtk::MessageDialog dlg("Error de entrada",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Ambos numero de Pizzas deben referirse a pizzas de las mismas medias");
			dlg.run();
		}
		std::vector<muposysdb::CatalogItem> items(2);
		items[0] = get_item(numbers[0]);
		items[1] = get_item(numbers[1]);
		if(items[0].getID() == items[1].getID())
		{
			Gtk::MessageDialog dlg("Error de entrada",true,Gtk::MESSAGE_ERROR);
			dlg.set_secondary_text("Ambos numero de Pizzas deben referirse a pizzas distintas");
			dlg.run();
		}

		combinedstr = strnumb.substr(0,1);
		combinedstr += "cb";
		//std::cout << "combined : " << combined << "\n";
		number = combinedstr;
	}
	else
	{
		number = strnumb;
	}
	
	Gtk::TreeModel::iterator iter = tree_model->get_iter(path);
	Gtk::TreeModel::Row row = *iter;
	if(iter) set_data(row,number,strnumb,combined);
	
}
void TableSaling::set_data(Gtk::TreeModel::Row& row,const Glib::ustring& back_number,const Glib::ustring& origin_number,bool combined = false)
{
	std::string where = "number = '" + back_number + "'";
	std::vector<muposysdb::CatalogItem*>* lstCatItems = muposysdb::CatalogItem::select(connDB,where);
	if(lstCatItems->size() == 1)
	{
		lstCatItems->front()->downBrief(connDB);
		lstCatItems->front()->downValue(connDB);
		lstCatItems->front()->downPresentation(connDB);
		
		row[columns.item] = lstCatItems->front()->getID();
		row[columns.number] = origin_number;
		if(combined)
		{
			row[columns.name] = get_brief(origin_number);
			row[columns.cost_unit] = get_price(origin_number);
		}
		else
		{
			row[columns.name] = lstCatItems->front()->getBrief();
			row[columns.cost_unit] = lstCatItems->front()->getValue();
		}
			
		row[columns.presentation] = lstCatItems->front()->getPresentation();
		row[columns.amount] = row[columns.quantity] * row[columns.cost_unit];
			
		for(muposysdb::CatalogItem* p : *lstCatItems)
		{
			delete p;
		}
		delete lstCatItems;
	}
}


std::vector<Glib::ustring> TableSaling::split(const Glib::ustring& number)
{
	Glib::ustring::size_type found = std::string(number).find("/");
	//std::cout << "TableSaling::split : found " << found << "\n";
	if(found != Glib::ustring::npos)
	{
		std::vector<Glib::ustring> numbers(2);
		numbers[0] = number.substr(0,found);
		numbers[1] = number.substr(found + 1, number.length() - 1);
		return numbers;
	}
	else
	{
		std::vector<Glib::ustring> numbers(1);
		numbers[0] = number;
		return numbers;
	}
}
muposysdb::CatalogItem TableSaling::get_item(const Glib::ustring& number)
{
	muposysdb::CatalogItem item(-1);
	std::string where = "number = '" + number + "'";
	std::vector<muposysdb::CatalogItem*>* lstCatItems = muposysdb::CatalogItem::select(connDB,where);

	if(lstCatItems->size() == 1) item = *lstCatItems->front();

	for(muposysdb::CatalogItem* p : *lstCatItems)
	{
		delete p;
	}
	delete lstCatItems;

	return item;
}
std::vector<muposysdb::CatalogItem> TableSaling::get_items(const Glib::ustring& str)
{
	const std::vector<Glib::ustring> numbers = split(str);
	if(numbers.size() == 2)
	{
		std::vector<muposysdb::CatalogItem> items(2);
		items[0] = get_item(numbers[0]);
		items[1] = get_item(numbers[1]);
		return items;
	}
	else
	{
		std::vector<muposysdb::CatalogItem> items(1);
		items[0] = get_item(numbers[0]);
		return items;
	}
}
Glib::ustring TableSaling::get_brief(const Glib::ustring& str)
{
	const std::vector<Glib::ustring> numbers = split(str);
	Glib::ustring combined,brief ,number;

	if(numbers.size() == 2)
	{
		if(numbers[0][0] != numbers[1][0])
		{
			//std::cout << "'"<< numbers[0] << "' != '" <<  numbers[1] << "'\n";
			return "";
		}
		std::vector<muposysdb::CatalogItem> items(2);
		items[0] = get_item(numbers[0]);
		items[1] = get_item(numbers[1]);
		if(items[0].getID() == items[1].getID()) return "";

		combined = str.substr(0,1);
		combined += "cb";
		//std::cout << "combined : " << combined << "\n";
		number = combined;
	}
	else
	{
		//std::cout << "TableSaling::get_brief : " << numbers.size() << "\n";
	}

	std::string where = "number = '" + number + "'";
	std::vector<muposysdb::CatalogItem*>* lstCatItems = muposysdb::CatalogItem::select(connDB,where);
	//std::cout << "where : " << where << "\n";
	if(lstCatItems->size() == 1)
	{
		lstCatItems->front()->downBrief(connDB);
		brief = lstCatItems->front()->getBrief();

		for(muposysdb::CatalogItem* p : *lstCatItems)
		{
			delete p;
		}
		delete lstCatItems;
	}

	return brief;
}
float TableSaling::get_price(const Glib::ustring& str)
{
	float price1,price2;

	const std::vector<Glib::ustring> numbers = split(str);
	std::vector<muposysdb::CatalogItem> items(2);
	items[0] = get_item(numbers[0]);
	items[1] = get_item(numbers[1]);

	std::string where = "number = '" + numbers[0] + "'";
	std::vector<muposysdb::CatalogItem*>* lstCatItems = muposysdb::CatalogItem::select(connDB,where);
	//std::cout << "where : " << where << "\n";
	if(lstCatItems->size() == 1)
	{
		lstCatItems->front()->downValue(connDB);
		price1 = lstCatItems->front()->getValue();

		for(muposysdb::CatalogItem* p : *lstCatItems)
		{
			delete p;
		}
		delete lstCatItems;
	}

	where = "number = '" + numbers[1] + "'";
	lstCatItems = muposysdb::CatalogItem::select(connDB,where);
	if(lstCatItems->size() == 1)
	{
		lstCatItems->front()->downValue(connDB);
		price2 = lstCatItems->front()->getValue();

		for(muposysdb::CatalogItem* p : *lstCatItems)
		{
			delete p;
		}
		delete lstCatItems;
	}

	return std::max(price1,price2) + 20.0;
}

void TableSaling::load_order(long order)
{
	tree_model->clear();
    std::string whereOrder;
    whereOrder = "operation = ";
    whereOrder += std::to_string(order);
    std::vector<muposysdb::Sale*>* lstSales = muposysdb::Sale::select(connDB,whereOrder,0,'A');
    if(lstSales)
    {
		Gtk::TreeModel::Row row;
		for(muposysdb::Sale* s : *lstSales)
		{
			s->downOperation(connDB);
			s->downItem(connDB);
			s->downAmount(connDB);
			row = *tree_model->append();
			
			row[columns.quantity] = s->getAmount();
			set_data(row,s->getItem().getID());
		}
		
		for(auto s : *lstSales)
		{
			delete s;
		}
		delete lstSales;
    }
}
bool TableSaling::on_key_press_event(GdkEventKey* event)
{
	//std::cout << "on_key_press_event\n";
	if (event->type == GDK_KEY_PRESS and event->keyval == GDK_KEY_F4)
	{
		//std::cout << "on_key_press_event F4 begin\n";
		long number;
		mps::SearchItem search(number);
		if(search.run() == Gtk::RESPONSE_OK)
		{
			//std::cout << "number : " << number  << "\n";
			Glib::RefPtr<Gtk::TreeSelection> refSelection = table.get_selection();
			Gtk::TreeModel::iterator iter = refSelection->get_selected();
			if(iter) //If anything is selected
			{
				mps::Connector connDB;
				bool connDB_flag;
				try
				{
					connDB_flag = connDB.connect(muposysdb::datconex);
				}
				catch(const std::exception& e)
				{
					Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
					dlg.set_secondary_text(e.what());
					dlg.run();
					return false;
				}
				
				muposysdb::CatalogItem item(number);
				item.downNumber(connDB);
				Gtk::TreeModel::Row row = *iter;
				set_data(row,item.getNumber(),item.getNumber());
				
				connDB.close();
			}
	
		}
		else
		{
			
		}
		
	}
	return false;
}
void TableSaling::set_data(Gtk::TreeModel::Row& row,long item)
{
	std::string where = "id = '" + std::to_string(item) + "'";
	std::vector<muposysdb::CatalogItem*>* lstCatItems = muposysdb::CatalogItem::select(connDB,where);
	if(lstCatItems->size() == 1)
	{
		lstCatItems->front()->downBrief(connDB);
		lstCatItems->front()->downValue(connDB);
		lstCatItems->front()->downPresentation(connDB);
		lstCatItems->front()->downNumber(connDB);
		
		row[columns.item] = lstCatItems->front()->getID();
		row[columns.number] = lstCatItems->front()->getNumber();
		row[columns.name] = lstCatItems->front()->getBrief();
		row[columns.cost_unit] = lstCatItems->front()->getValue();
		
		row[columns.presentation] = lstCatItems->front()->getPresentation();
		row[columns.amount] = row[columns.quantity] * row[columns.cost_unit];
			
		for(muposysdb::CatalogItem* p : *lstCatItems)
		{
			delete p;
		}
		delete lstCatItems;
	}
	
}

}

