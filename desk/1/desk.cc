
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


//#include <gtkmm/application.h>

#include "desk.hh"





namespace oct::mias::v1
{










    Sales::Sales(Mias* m)
    {
        init();
    }
    void Sales::init()
    {
        //add1(pending);
        //add2(saling);
    }
    Sales::~Sales()
    {
    }





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
    }



}

