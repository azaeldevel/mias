

#include "desk.hh"

namespace oct::mias::v1
{




    TableSaling::TableSaling() : rdllevar("Llevar"),rdaqui("Aquí"),frame("Final"),user(NULL)
    {
        //std::cout << "mias::TableSaling::TableSaling()\n";
        init();
    }
    TableSaling::TableSaling(long o) : mps::TableSaling(o),rdllevar("Llevar"),rdaqui("Aquí"),frame("Final"),user(NULL)
    {
        //std::cout << "mias::TableSaling::TableSaling(" << o << ")\n";
        init();
        //std::cout << "mias::TableSaling::loading..(" << o << ")\n";
        load_order(o);
    }
    TableSaling::TableSaling(long o,mps::Crud c) : mps::TableSaling(o),rdllevar("Llevar"),rdaqui("Aquí"),frame("Final"),user(NULL)
    {
        //std::cout << "mias::TableSaling::TableSaling(" << o << ")\n";
        init();
        load_order(o);
    }
    void TableSaling::init()
    {
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
            //Gtk::TreeViewColumn* col_number = table.get_column(2);
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
    }
    void TableSaling::set(const mps::User& u)
    {
        user = &u;
    }
    void TableSaling::cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& strnumb)
    {
    }




    void TableSaling::load_order(long order)
    {
    }

    bool TableSaling::on_key_press_event(GdkEventKey* event)
    {
        std::cout << "on_key_press_event\n";
        if (event->type == GDK_KEY_PRESS and event->keyval == GDK_KEY_F4)
        {
            //std::cout << "on_key_press_event F4 begin\n";
            mps::ID number;
            SearchItem search(number);
            if(search.run() == Gtk::RESPONSE_OK)
            {
                std::cout << "number : " << number  << "\n";
                Glib::RefPtr<Gtk::TreeSelection> refSelection = table.get_selection();
                Gtk::TreeModel::iterator iter = refSelection->get_selected();
                if(iter) //If anything is selected
                {
                    mps::cave::mmsql::Connection connDB;
                    mps::cave::mmsql::Data dtm = mps::default_dtm();
                    try
                    {
                        connDB_flag = connDB.connect(dtm, true);
                    }
                    catch (const mps::cave::ExceptionDriver& e)
                    {
                        Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text(e.what());
                        dlg.run();
                        return true;
                    }
                    catch (const std::exception& e)
                    {
                        Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text(e.what());
                        dlg.run();
                        return true;
                    }
                    catch (...)
                    {
                        Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text("Error desconocido en la creacion de la conexion a la base de datos");
                        dlg.run();
                        return true;
                    }

                    Glib::ustring where;
                    where += "id = '" + std::to_string(number) + "'" ;
                    std::vector<mps::CatalogItem> lstItem;
                    bool lstItemflag = false;
                    try
                    {
                         lstItemflag = connDB.select(lstItem,where);
                    }
                    catch (const mps::cave::ExceptionDriver& e)
                    {
                        Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text(e.what());
                        dlg.run();
                        return true;
                    }
                    catch (const std::exception& e)
                    {
                        Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text(e.what());
                        dlg.run();
                        return true;
                    }
                    catch (...)
                    {
                        Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text("Error desconocido en la creacion de la conexion a la base de datos");
                        dlg.run();
                        return true;
                    }

                    if(lstItemflag and lstItem.size() == 1)
                    {
                        std::cout << "writing in model..\n";
                        Gtk::TreeModel::Row row = *iter;
                        set_data(row,lstItem[0]);
                    }
                    else
                    {
                        std::cout << "Hay " << lstItem.size() << " resultados ..\n";
                    }

                    connDB.close();
                }

            }
            else
            {

            }

        }

        return true;
    }



}
