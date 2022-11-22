
#ifndef MIAS_MAIN_HH
#define MIAS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>

#include <muposys/desk/desk.hh>
#include <mias/core/core.hh>
#include <thread>
#include <mutex>

namespace mias
{




	
class TableSaling : public mps::TableSaling
{	
public:
	TableSaling();
	void init();
	virtual ~TableSaling();

protected:
	virtual void save();
	void on_save_clicked();
	
	Gtk::Label lbName;
	Gtk::Entry inName;
	Gtk::HBox boxName;
};

class TableServicies : public Gtk::TreeView
{
public:
	
public:
	TableServicies();	
	void init();
	virtual ~TableServicies();
	
	void load();
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

class SearchItem : public Gtk::ComboBox
{
public:
	SearchItem();	
	void init();
	virtual ~SearchItem();
	
protected:
	void on_cell_data_extra(const Gtk::TreeModel::const_iterator& iter);
	void on_combo_changed();
	bool on_combo_key_presst(GdkEventKey* event);
	
	void on_entry_changed();
	void on_entry_activate();
	bool on_entry_focus_out_event(GdkEventFocus* event);
	bool on_entry_key_presst(GdkEventKey* event);
	
private:	
	class ModelColumnsItem : public Gtk::TreeModel::ColumnRecord
	{
	public:
		ModelColumnsItem();
		
		Gtk::TreeModelColumn<unsigned int> id;
		Gtk::TreeModelColumn<Glib::ustring> number;
		Gtk::TreeModelColumn<Glib::ustring> name;
		Gtk::TreeModelColumn<const muposysdb::CatalogItem*> db;
	};
	
	ModelColumnsItem columns;
	Glib::RefPtr<Gtk::ListStore> refModel;
	Gtk::CellRendererText cell;
	std::vector<muposysdb::CatalogItem*>* lstCatItems;
	Gtk::Entry* item;
	sigc::connection focusOut;
};

class Saling : public Gtk::Box
{
	
public:
	Saling();	
	void init();
	virtual ~Saling();
	
protected:
	
private:
	
		
	TableSaling table;
	
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
	
protected:
	
private:
	Gtk::Label label1;
	Gtk::Label label2;
	Saling saling;
	PendingServices pending;
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
