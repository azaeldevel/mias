
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
	
private:	
	struct Item
	{
	};
	
	class ModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		ModelColumns();
		Gtk::TreeModelColumn<unsigned int> amount;
		Gtk::TreeModelColumn<Glib::ustring> presentation;
		Gtk::TreeModelColumn<Glib::ustring> item;		
		Gtk::TreeModelColumn<float> cost;
	};
	
	ModelColumns columns;
	Gtk::ScrolledWindow scrolled;
	Glib::RefPtr<Gtk::ListStore> tree_model;
	
};


class Saling : public Gtk::Box
{
	
public:
	Saling();	
	void init();
	virtual ~Saling();
	
protected:
	
private:	
	class ModelColumnsItem : public Gtk::TreeModel::ColumnRecord
	{
	public:
		ModelColumnsItem();
		
		Gtk::TreeModelColumn<unsigned int> id;
		Gtk::TreeModelColumn<Glib::ustring> number;
		Gtk::TreeModelColumn<Glib::ustring> name;
	};
	
	Gtk::Frame capture;
	
	Gtk::Box boxCapture;
	
	Gtk::SpinButton inAmount;
	Gtk::Entry item;
	ModelColumnsItem columns;
	Gtk::Entry inCost;
	
	TableSaling table;
	
	bool on_completion_match(const Glib::ustring& key, const Gtk::TreeModel::const_iterator& iter);
	
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
