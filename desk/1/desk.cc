
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
        std::cout << "Logged 2\n";
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





    const Glib::ustring SearchItem::search_label = "Buscar...";

	SearchItem::SearchItem(mps::ID& n) : number(n)
	{
		init();
	}
	void SearchItem::init()
	{
		number = -1;
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
            return;
        }
        catch (const std::exception& e)
        {
            Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
            dlg.set_secondary_text(e.what());
            dlg.run();
            return;
        }
        catch (...)
        {
            Gtk::MessageDialog dlg("Error detectado durante conexion a BD",true,Gtk::MESSAGE_ERROR);
            dlg.set_secondary_text("Error desconocido en la creacion de la conexion a la base de datos");
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
			//std::cout << "key : Enter\n";
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
        //std::vector<muposysdb::CatalogItem*>* lstItem = muposysdb::CatalogItem::select(connDB,where);
        std::vector<mps::CatalogItem> lstItem;
        bool lstItemflag = false;
        try
        {
             lstItemflag = connDB.select(lstItem,where);
        }
        catch (const mps::cave::ExceptionDriver&)
        {
        }
        catch (...)
        {
        }

        if(lstItemflag)
        {
            Gtk::TreeModel::Row row;
            treemodel->clear();
            //std::cout << "i : " << lstItem->size() << "\n";
            for(size_t i = 0; i < lstItem.size(); i++)
            {
                row = *(treemodel->append());
                row[colums.id] = lstItem[i].id;
                row[colums.number] = lstItem[i].number;
                row[colums.name] = "nombre";
                row[colums.brief] = lstItem[i].brief;
            }
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

