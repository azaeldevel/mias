
#ifndef MIAS_MAIN_HH
#define MIAS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>

#include "config.h"

#include <muposys/desk/desk.hh>



namespace mias
{

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
	
	Gtk::Entry inAmount;
	Gtk::Entry inPresentation;
	Gtk::ComboBox cmbItem;
	Gtk::Entry inCost;
	
	
};

class PendingServices : public Gtk::Box
{
	
public:
	PendingServices();	
	void init();
	virtual ~PendingServices();
	
private:
	Gtk::Label lbTitle;
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
