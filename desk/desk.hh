
#ifndef MIAS_MAIN_HH
#define MIAS_MAIN_HH

#include <gtkmm.h>
#include <glibmm/i18n.h>

#include "config.h"

#include <muposys/desk/desk.hh>



namespace mias
{

class Sales : public Gtk::Box
{
public:
	Sales();	
	void init();
	virtual ~Sales();
	
protected:
	
private:
	Gtk::Label label1;
	Gtk::Label label2;

};


class NewOrder : public Gtk::Dialog
{

public:
	NewOrder(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	
	int run();
	void on_bt_ok_clicked();
	void on_bt_cancel_clicked();
	
private:
	int retcode;
	Gtk::Button* btOK;
	Gtk::Button* btCancel;
	const Glib::RefPtr<Gtk::Builder>& builder;
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
	Gtk::Box* boxClients;
	NewOrder* neworder;
	Gtk::Notebook* nbPages;
	Sales sales;
};



}

#endif
