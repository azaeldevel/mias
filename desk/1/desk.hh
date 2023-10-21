
#ifndef MIAS_CORE_DESK_HH
#define MIAS_CORE_DESK_HH

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

#include <mias/core/1/core.hh>
#include <muposys/desk/1/desk.hh>



namespace oct::mias::v1
{
    class Mias;

    namespace mps = oct::mps::v1;



    class TableSaling : public mps::TableSaling
    {
    public:
        TableSaling();
        TableSaling(long order);
        //TableSaling(long order,mps::Crud);
        void init();
        virtual ~TableSaling();

        virtual void clear();
        void set(const mps::User& user);

    protected:
        virtual void save();
        void on_save_clicked();
        bool on_key_press_event(GdkEventKey* key_event) override;
        void cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& new_text);
        /**
         * \brief escribe los datos los datos el regstro currepondientes al item
         * \param back_number es el numero usado internamente, el cual sera escrito en la base de datos
         * \param orign_number es el numero escrito por el usuario
         * */
        void set_data(Gtk::TreeModel::Row&,const Glib::ustring& back_number,const Glib::ustring& orign_number,bool combined);
        void set_data(Gtk::TreeModel::Row&,long);
        float get_combine_price(long order);

        //virtual void load_order(long);

        Gtk::Label lbName;
        Gtk::Entry inName;
        Gtk::HBox boxName,boxFrame;
        Gtk::RadioButton rdllevar, rdaqui;
        Gtk::Frame frame;

    private:
        const mps::User* user;



    };





    class TableServicies : public Gtk::TreeView
    {
    public:

    public:
        TableServicies(Mias*);
        void init();
        virtual ~TableServicies();

        void load();
        void reload();
        bool is_reloadable();
        void notify();

        void on_show()override;

        // Dispatcher handler.
        void on_notification_from_worker_thread();
        bool on_key_press_event(GdkEventKey* key_event) override;


        // Signal handlers.
        void on_start_services();
        void on_stop_services();
        void on_quit_services();

        void update_start_stop_buttons();

        void step_data(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);

        bool on_button_press_event(GdkEventButton* button_event) override;
        bool on_enter_notify_event (GdkEventCrossing* crossing_event)override;
        bool on_leave_notify_event (GdkEventCrossing* crossing_event)override;
        void on_menu_cooked_popup();
        void on_menu_waiting_popup();
        void on_menu_deliver_popup();
        void on_menu_cancel_popup();

    protected:

    private:
        class Menu : public Gtk::Menu
        {
        public:
            Menu();
            Menu(TableServicies& parent);
            bool on_enter_notify_event (GdkEventCrossing* crossing_event)override;
            //void on_show()override;
            //void on_hide() override;
            void set(TableServicies& parent);

        private:
            TableServicies* parent;
        };
        class ModelColumns : public Gtk::TreeModel::ColumnRecord
        {
        public:
            ModelColumns();
            Gtk::TreeModelColumn<long> service;
            Gtk::TreeModelColumn<Glib::ustring> name;
            Gtk::TreeModelColumn<int> progress;
            Gtk::TreeModelColumn<short> updated;
            Gtk::TreeModelColumn<Glib::ustring> step_str;
            Gtk::TreeModelColumn<ServiceStep> step_number;
        };
        class Updater
        {
        public:
            Updater();
            // Thread function.
            void do_work(TableServicies* caller);

            //void get_data(double* fraction_done, Glib::ustring* message) const;
            void stop_work();
            bool has_stopped() const;
        private:
            mutable std::mutex mutex;
            // Data used by both GUI thread and worker thread.
            bool m_shall_stop;
            bool m_has_stopped;

            //mps::Connector connDB;
            //bool connDB_flag;
        };

        ModelColumns columns;
        Gtk::ScrolledWindow scrolled;
        Glib::RefPtr<Gtk::ListStore> tree_model;
        bool is_runnig;
        bool is_stop;
        Glib::Dispatcher dispatcher;
        Updater updater;
        std::thread* updaterThread;
        Menu menu;
        long serviceSelected;
        Mias* mias;
        long order_view;
    };






    class Saling : public Gtk::Box
    {

    public:
        Saling();
        Saling(long o);
        //Saling(long o,mps::Crud);
        void init();
        virtual ~Saling();

        void set(const mps::User& user);
    protected:

    private:
        //TableSaling table;
        const mps::User* user;
    };

    class PendingServices : public Gtk::Box
    {

    public:
        PendingServices(Mias*);
        void init();
        virtual ~PendingServices();

    private:
        Gtk::Label lbTitle;

        //TableServicies servicies;
        Mias* mias;
    };


    class Sales : public Gtk::Paned
    {
    public:
        Sales(Mias*);
        Sales(Mias*,long);
        //Sales(Mias*,long,mps::Crud);
        //Sales(Mias*,mps::Crud);
        void init();
        virtual ~Sales();

        void set(const mps::User& user);

    protected:

    private:
        Gtk::Label label1;
        Gtk::Label label2;
        Saling saling;
        PendingServices pending;
        const mps::User* user;
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
        //void enables();
        //virtual void notific_session();

    private:
        std::vector<Sales*> sale;
        Gtk::ToolButton btSales;
    };



}

#endif
