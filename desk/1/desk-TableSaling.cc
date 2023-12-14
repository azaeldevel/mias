

#include "desk.hh"

namespace oct::mias::v1
{




    TableSaling::TableSaling() : rdllevar("Llevar"),rdaqui("Aquí"),frame("Final")
    {
        //std::cout << "mias::TableSaling::TableSaling()\n";
        init();
    }
    TableSaling::TableSaling(mps::Crud c) : mps::TableSaling(c),rdllevar("Llevar"),rdaqui("Aquí"),frame("Final")
    {
        //std::cout << "mias::TableSaling::TableSaling()\n";
        init();
    }
    void TableSaling::init()
    {
        mps::TableSaling::create_table<ModelColumns>();

        //table.append_column("Nombre", ((ModelColumns&)*columns).name);
        newrow();
        if(crud == mps::Crud::create)
        {

        }
        else if(crud == mps::Crud::read)
        {
            btSave.set_sensitive(false);
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
        if(columns) delete columns;

    }

    void TableSaling::on_save_clicked()
    {
        save();
    }
    void TableSaling::save()
    {
    }




    TableSaling::ModelColumns::ModelColumns()
    {
        add(name);
    }


    bool TableSaling::on_key_press_event(GdkEventKey* event)
    {
        bool connDB_flag;
        //std::cout << "on_key_press_event mias\n";
        if (event->type == GDK_KEY_PRESS and event->keyval == GDK_KEY_F4)
        {
            //std::cout << "on_key_press_event F4 begin\n";
            mps::ID number;
            mps::SearchItem search(number);
            if(search.run() == Gtk::RESPONSE_OK)
            {
                //std::cout << "number : " << number  << "\n";
                Glib::RefPtr<Gtk::TreeSelection> refSelection = table.get_selection();
                Gtk::TreeModel::iterator iter = refSelection->get_selected();
                if(iter) //If anything is selected
                {
                    mps::cave0::mmsql::Connection connDB;
                    mps::cave0::mmsql::Data dtm = mps::default_dtm0();
                    try
                    {
                        connDB_flag = connDB.connect(dtm, true);
                    }
                    catch (const mps::cave0::ExceptionDriver& e)
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

                    if(not connDB_flag)
                    {
                        std::cerr << "Fallo la conexion abase de datos en \"bool TableSaling::on_key_press_event(GdkEventKey* event)\"";
                        return true;
                    }

                    Glib::ustring where;
                    where += "id = '" + std::to_string(number) + "'" ;
                    std::vector<CatalogItem> lstItem;
                    bool lstItemflag = false;
                    try
                    {
                         lstItemflag = connDB.select(lstItem,where);
                    }
                    catch (const mps::cave0::ExceptionDriver& e)
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
                        //std::cout << "writing in model..\n";
                        Gtk::TreeModel::Row row = *iter;
                        if(row[columns->itemDB]) delete row[columns->itemDB];
                        else row[columns->itemDB] = new CatalogItem(lstItem[0]);
                        set_data(row,lstItem[0]);
                    }
                    else
                    {
                        Gtk::MessageDialog dlg("Deve seleccionar un item de la lista antes de continuar",true,Gtk::MESSAGE_ERROR);
                        dlg.set_secondary_text("No hay seleccion.");
                        dlg.run();
                        return true;
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

    void TableSaling::set_data(Gtk::TreeModel::Row& row,const CatalogItem& item)
    {
        mps::TableSaling::set_data(row,item);
        row[((ModelColumns&)*columns).name] = item.name;
    }

}
