
#ifndef MIAS_MAIN_HH
#define MIAS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>

#include <muposys/desk.hh>



namespace mias
{

class TableServicies : public Gtk::TreeView
{
	
public:
	TableServicies();	
	void init();
	virtual ~TableServicies();
	
protected:
	
private:
	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		ModelColumns();
		Gtk::TreeModelColumn<unsigned int> service;
		Gtk::TreeModelColumn<Glib::ustring> name;
		Gtk::TreeModelColumn<unsigned int> progress;
		
	};
	
	ModelColumns columns;
	Gtk::ScrolledWindow scrolled;
	Glib::RefPtr<Gtk::ListStore> tree_model;
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
	
	Gtk::Frame capture;
	
	Gtk::Box boxCapture;
	
	Gtk::SpinButton inAmount;
	//Gtk::Box itemBox;
	SearchItem item;
	Gtk::Entry inCost;
	
	mps::TableSaling table;
	
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
	/**
	*
	**/
	Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade,bool);
	void init();
	virtual ~Mias();
	
protected:
	
private:
	Sales sales;
};



}

#endif
