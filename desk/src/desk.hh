
#ifndef MIAS_MAIN_HH
#define MIAS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>


#if __linux__
    #include <muposys/desk/desk.hh>
    #include <mias/core/core.hh>
    #include <mias/core/Exception.hh>
#elif MSYS2
    #include <mias/core/src/core.hh>
    #include <mias/core/src/Exception.hh>
    #include <muposys/desk/src/desk.hh>
#else
    #error "Plataforma desconocida."
#endif

#include <thread>
#include <mutex>





namespace mps
{

class SearchItem : public Gtk::Dialog
{
public:
	SearchItem(Glib::ustring&);
	void init();

protected:
	void on_bt_ok_clicked();
	void on_bt_cancel_clicked();
	void on_response(int);
	void on_search_text_changed();
	void on_visible_child_changed();

	muposysdb::CatalogItem* searching(const Glib::ustring& s);

private:
	mps::Connector connDB;
	bool connDB_flag;
	Glib::ustring& number;

	Gtk::Button btOK;
	Gtk::Button btCancel;
	Gtk::SearchBar bar;
	Gtk::SearchEntry entry;
	Gtk::ButtonBox boxButtons;
	Gtk::VBox panel;

	std::vector<muposysdb::CatalogItem*>* lstCatalog;
};

}




namespace mias
{

class TableSaling : public mps::TableSaling
{
public:
	TableSaling();
	void init();
	virtual ~TableSaling();

	void clear();
	void set(const muposysdb::User& user);

protected:
	virtual void save();
	void on_save_clicked();
	bool on_key_press_event(GdkEventKey* key_event) override;


	Gtk::Label lbName;
	Gtk::Entry inName;
	Gtk::HBox boxName;

private:
	const muposysdb::User* user;
};

class TableServicies : public Gtk::TreeView
{
public:

public:
	TableServicies();
	void init();
	virtual ~TableServicies();

	void load();
	void reload();
	bool is_reloadable();
	void notify();

	void on_show()override;

	// Dispatcher handler.
	void on_notification_from_worker_thread();

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
		Gtk::TreeModelColumn<Glib::ustring> step;
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

		mps::Connector connDB;
		bool connDB_flag;
	};
	/*struct Row
	{

	};
	struct Data
	{
		std::vector<muposysdb::MiasService*>* lstOprs;
		std::vector<muposysdb::Progress*>* lstProgress;
		bool reload;

	};*/

	ModelColumns columns;
	Gtk::ScrolledWindow scrolled;
	Glib::RefPtr<Gtk::ListStore> tree_model;
	mps::Connector connDB;
	bool connDB_flag;
	bool is_runnig;
	bool is_stop;
	Glib::Dispatcher dispatcher;
	Updater updater;
	std::thread* updaterThread;
	Menu menu;
	long serviceSelected;
	std::vector<muposysdb::MiasService*>* lstOprs;
	std::vector<muposysdb::Progress*>* lstProgress;
};


class Saling : public Gtk::Box
{

public:
	Saling();
	void init();
	virtual ~Saling();

	void set(const muposysdb::User& user);
protected:

private:
	TableSaling table;
	const muposysdb::User* user;
};

class PendingServices : public Gtk::Box
{

public:
	PendingServices();
	void init();
	virtual ~PendingServices();

private:
	Gtk::Label lbTitle;

	TableServicies servicies;
};


class Sales : public Gtk::Paned
{
public:
	Sales();
	void init();
	virtual ~Sales();

	void set(const muposysdb::User& user);

protected:

private:
	Gtk::Label label1;
	Gtk::Label label2;
	Saling saling;
	PendingServices pending;
	const muposysdb::User* user;

};


class Mias : public mps::Restaurant
{
public:
	Mias();
	Mias(bool devel);
	/**
	*
	**/
	//Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	//Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade,bool);
	void init();
	virtual ~Mias();


protected:

private:
	Sales sale;
};



}

#endif
