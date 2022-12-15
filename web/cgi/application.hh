#ifndef MIAS_WEB_APPLICATION_HH
#define MIAS_WEB_APPLICATION_HH


#ifdef __linux__
    #include <muposys/web/application.hh>
    #include <mias/core/core.hh>
    #include <mias/core/Exception.hh>
#elif defined MSYS2
    #include <muposys/web/cgi/application.hh>
    #include <muposys/web/cgi/html.hh>
    #include <mias/core/src/core.hh>
#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida"
#endif

#include <map>


namespace mias
{
class Application;

//void params_get(std::map<std::string, std::string>&);

struct GetParams : public mps::Params
{
	Station station;
	long order;
	Eating step;
	long item;
	bool restoring;

	GetParams();
	operator std::string()const;
};


class BodyApplication : public mps::BodyApplication
{
private:
	const GetParams& params;
	const char* to_text(Eating);
	
	bool is_combined(long);

public:
	BodyApplication(const GetParams& params);
	virtual std::ostream& print (std::ostream& out);
	virtual std::ostream& print_common(std::ostream& out);
	virtual std::ostream& print_common_commands(std::ostream& out);
	virtual std::ostream& print_oven(std::ostream& out);
	virtual void programs(std::ostream& out);
	void select_order(std::ostream& out);
	void select_item(std::ostream& out);
	void accepted_item(std::ostream& out);
	void restoring_order(std::ostream& out);
	void select_item_oven(std::ostream& out);

	virtual void panel(std::ostream& out);
	void select_order_restore(std::ostream& out);
	void select_step_restore(std::ostream& out);
	void select_item_restore(std::ostream& out);
	
protected:
	
};

class Application : public mps::Application
{
public:
	virtual int main(std::ostream& out = std::cout);

	void init();
	Application(BodyApplication&,const GetParams& params);
	Application(BodyApplication&,const std::string& title,const GetParams& params);
	virtual ~Application();

private:
	const GetParams& params;

	long accepting();
	void preparing();
	void steping(Eating);

protected:

};

}

#endif
