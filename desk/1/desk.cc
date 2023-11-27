
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



namespace oct::mias::v1
{


    Mias::Mias()
    {
        init();
    }
    Mias::Mias(bool d) : mps::Restaurant(d)
    {
        init();
    }
    void Mias::init()
    {
        //std::cout << " Mias::init step 1\n";
        add_events(Gdk::KEY_PRESS_MASK);
        set_title("Mia's Pizza & Pasta");
        set_default_size(800,640);
        btSales.set_icon_name("document-new");
        btSales.set_sensitive(false);
        tbMain.add(btSales);
        show_all_children();

        //std::cout << " Mias::init step 2\n";

        btSales.signal_clicked().connect(sigc::mem_fun(*this, &Mias::on_click_sales));
        on_logged_listener(sigc::mem_fun(*this,&Mias::on_logged));

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
        //std::cout << " Mias::on_click_sales step 1\n";
        Sales* snow = new Sales(this,o);
        //std::cout << " Mias::on_click_sales step 2\n";
        sale.push_back(snow);
        nbMain.append_page(*snow);
        //std::cout << " Mias::on_click_sales step 3\n";
        Glib::ustring title = "Order - " + std::to_string(o);
        //std::cout << " Mias::on_click_sales step 4\n";
        nbMain.set_tab_label_text((Gtk::Widget&)*snow,title);
        //std::cout << " Mias::on_click_sales step 5\n";
        snow->set(get_user());
        //std::cout << " Mias::on_click_sales step 6\n";
        snow->show_all();
        //std::cout << " Mias::on_click_sales step 7\n";

        return *snow;
    }
    void Mias::on_logged()
    {
#ifdef OCTETOS_MIAS_DESK_V1_TDD
        //std::cout << "Logged 2\n";
#endif
        btSales.set_sensitive(true);
    }










    Sales::Sales(Mias* m) : pending(m),user(NULL)
    {
        init();
    }
    Sales::Sales(Mias* m,long o) : saling(o),pending(m),user(NULL)
    {
        //std::cout << "Sales::Sales(app," << o << ")\n";
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
    void Sales::set(const mps::User& u)
    {
        user = &u;
        saling.set(u);
    }








    Saling::Saling() : Gtk::Box(Gtk::ORIENTATION_VERTICAL),user(NULL)
    {
        init();
    }
    Saling::Saling(long o) : Gtk::Box(Gtk::ORIENTATION_VERTICAL),table(o),user(NULL)
    {
        //std::cout << "Saling::Saling(" << o << ")\n";
        init();
    }
    void Saling::init()
    {
        pack_start(table,false,false);
    }
    Saling::~Saling()
    {
    }
    void Saling::set(const mps::User& u)
    {
        user = &u;
        table.set(u);
    }





    PendingServices::PendingServices(Mias* m) : Gtk::Box(Gtk::ORIENTATION_VERTICAL),servicies(m),mias(m)
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









}

