
#include <gtkmm/application.h>

#include "desk.hh"

namespace mias
{

Mias::Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& b) : mps::Restaurant(cobject,b)
{
	init();	
}
Mias::Mias(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& b,bool d) : mps::Restaurant(cobject,b,d)
{
	init();	
}
void Mias::init()
{	
	set_title("Mia's Pizza & Pasta");
	
	boxClients = 0;
	builder->get_widget("boxClients", boxClients);
			
	nbPages = 0;
	builder->get_widget("nbPages", nbPages);
	nbPages->append_page(sales);
	nbPages->show();
	sales.show();
	//notebook.set_child_visible(true);
	//sales->set_parent(notebook);
	//sales->set_parent(*notebook.get_children()[0]);
	//notebook.add_child(*sales);
	

	/*neworder = 0;
	builder->get_widget_derived("NewOrder", neworder);
	neworder->set_transient_for(*this);
	
	int res = Gtk::RESPONSE_NONE;
	res = neworder->run();
	switch(res)
	{
	case Gtk::RESPONSE_OK:
		neworder->close();
		break;	
	case Gtk::RESPONSE_CANCEL:
		neworder->close();
		return;	
	case Gtk::RESPONSE_NONE:
		break;			
	}
	*/
	
}
Mias::~Mias()
{
}



NewOrder::NewOrder(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) : Gtk::Dialog(cobject), builder(refGlade)
{
	set_modal(true);
	
	btOK = 0;
	builder->get_widget("btOK", btOK);
	btOK->signal_clicked().connect(sigc::mem_fun(*this,&NewOrder::on_bt_ok_clicked));
	
	btCancel = 0;
	builder->get_widget("btCancel", btCancel);
	btCancel->signal_clicked().connect(sigc::mem_fun(*this,&NewOrder::on_bt_cancel_clicked));
		
}

int NewOrder::run()
{
	show();
	Gtk::Dialog::run();
	return retcode;
}
void NewOrder::on_bt_cancel_clicked()
{
	retcode = Gtk::RESPONSE_CANCEL;
	close();
}
void NewOrder::on_bt_ok_clicked()
{
	retcode = Gtk::RESPONSE_OK;
	close();	
}




Sales::Sales()
{
	init();	
}
void Sales::init()
{	
	set_valign(Gtk::ALIGN_START);
	
	label1.set_text("etiqueta 1");
	pack_start(label1);
	label1.show();
	
	label2.set_text("etiqueta 2");
	pack_start(label2);
	label2.show();
}
Sales::~Sales()
{
}






}

