


#include "desk.hh"



namespace oct::mias::v1
{





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

    }
    void TableServicies::on_menu_waiting_popup()
    {

    }
    void TableServicies::on_menu_deliver_popup()
    {

    }
    void TableServicies::on_menu_cancel_popup()
    {

    }

    TableServicies::Updater::Updater() : m_shall_stop(false), m_has_stopped(false)
    {
        /*
        try
        {
            connDB_flag = connDB.connect(muposysdb::datconex);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << "\n";
            return;
        }
        */
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
            return false;
        }

        return true;
    }



}
