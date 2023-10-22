

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
    /*void TableSaling::clear()
    {
        tree_model->clear();
        newrow();
        lbTotalAmount.set_text("");
        inName.set_text("");
    }*/
    void TableSaling::set(const mps::User& u)
    {
        user = &u;
    }
    void TableSaling::cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& strnumb)
    {
    }
    void TableSaling::set_data(Gtk::TreeModel::Row& row,const Glib::ustring& back_number,const Glib::ustring& origin_number,bool combined = false)
    {
    }



    void TableSaling::load_order(long order)
    {
    }

    bool TableSaling::on_key_press_event(GdkEventKey* event)
    {

        return false;
    }



}
