


#include "desk.hh"



namespace oct::mias::v1
{

    //>>>>>>>>>>>>>>>>>>>>>TODO agregar las funciones de menu que actulizan la informacion de la base de datos



    TableServicies::TableServicies(Mias* m) : mias(m)
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

    }
    TableServicies::~TableServicies()
    {
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




}
