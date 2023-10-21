
#ifndef OCTETOS_MIAS_DESK_V1_HH
#define OCTETOS_MIAS_DESK_V1_HH

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

#include <gtkmm.h>
#include <glibmm/i18n.h>

#include <thread>
#include <mutex>


#include <muposys/desk/1/desk.hh>


namespace oct::mias::v1
{
    namespace mps = oct::mps::v1;

    class Mias;


    class Sales //: public Gtk::Paned
    {
    public:
        Sales(Mias*);
        void init();
        virtual ~Sales();

    protected:

    private:
        Gtk::Label label1;
        Gtk::Label label2;
        //Saling saling;
        //PendingServices pending;
    };

    class Mias : public mps::Restaurant
    {
    public:
        Mias();
        Mias(bool devel);

        void init();
        virtual ~Mias();

        void on_click_sales();
        Sales& create_activity_sale();
        Sales& create_activity_sale(long);

    protected:


    private:
        std::vector<Sales*> sale;
        Gtk::ToolButton btSales;
    };



}

#endif
