
#ifndef MIAS_MAIN_HH
#define MIAS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>

#include "config.h"

#include <muposys/desk/desk.hh>



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

class TableSaling : public Gtk::TreeView
{
	
public:
	TableSaling();	
	void init();
	virtual ~TableSaling();
	
protected:
	
	void row_changed(const Gtk::TreeModel::Path& path, const Gtk::TreeModel::iterator& iter);
	
	/*
	void treeviewcolumn_validated_on_cell_data(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
	void cellrenderer_validated_on_editing_started(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void cellrenderer_validated_on_edited(const Glib::ustring& path_string, const Glib::ustring& new_text);
	*/
	
	void treeviewcolumn_validated_on_cell_data_number(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
	void cellrenderer_validated_on_editing_started_number(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void cellrenderer_validated_on_edited_number(const Glib::ustring& path_string, const Glib::ustring& new_text);
	
	void treeviewcolumn_validated_on_cell_data_quantity(Gtk::CellRenderer* renderer, const Gtk::TreeModel::iterator& iter);
	void cellrenderer_validated_on_editing_started_quantity(Gtk::CellEditable* cell_editable, const Glib::ustring& path);
	void cellrenderer_validated_on_edited_quantity(const Glib::ustring& path_string, const Glib::ustring& new_text);
	
	void newrow();
	
private:
	
	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		ModelColumns();
		Gtk::TreeModelColumn<unsigned int> id;		
		Gtk::TreeModelColumn<unsigned int> item;
		Gtk::TreeModelColumn<unsigned int> quantity;
		Gtk::TreeModelColumn<bool> quantity_valid;
		Gtk::TreeModelColumn<Glib::ustring> presentation;
		Gtk::TreeModelColumn<Glib::ustring> number;
		Gtk::TreeModelColumn<bool> number_validated;
		Gtk::TreeModelColumn<Glib::ustring> name;
		Gtk::TreeModelColumn<float> cost;
		Gtk::TreeModelColumn<bool> cost_valid;
		//Gtk::TreeModelColumn<const muposysdb::Catalog_Items*> db;
	};
	
	ModelColumns columns;
	Glib::RefPtr<Gtk::ListStore> tree_model;
	
	/*
	Gtk::CellRendererText cell_render;
	Gtk::TreeView::Column column_validated;
	bool validate_retry,valid_number;
	Glib::ustring invalid_text_for_retry;
	*/
	
	
	//Gtk::CellRendererText* cell_number;
	//Gtk::TreeViewColumn* col_number;
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
		Gtk::TreeModelColumn<const muposysdb::Catalog_Items*> db;
	};
	
	ModelColumnsItem columns;
	Glib::RefPtr<Gtk::ListStore> refModel;
	Gtk::CellRendererText cell;
	std::vector<muposysdb::Catalog_Items*>* lstCatItems;
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
	/**
	*
	**/
	Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade,bool);
	void init();
	virtual ~Mias();
	
protected:
	
private:
	Gtk::Box* boxSlices;
	Gtk::Box boxWork;
	//NewOrder* neworder;
	Gtk::Notebook activities;
	Sales sales;
};



}

#endif
