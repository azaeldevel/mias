#ifndef MIAS_WEB_APPLICATION_HH
#define MIAS_WEB_APPLICATION_HH


#include <muposys/web/application.hh>
#include <map>

#include <mias/core/core.hh>

namespace mps
{
	
class GetParams : public std::map<std::string, std::string>
{
	
public:
	GetParams();
	
	const char* find(const char*)const;
private:
	void build();
	
};
	
}
namespace mias
{

//void params_get(std::map<std::string, std::string>&);

struct GetParams : public mps::GetParams
{
	Station station;
	long order;
	short step;
	long item;
	bool restoring;
	
	GetParams();
};


class BodyApplication : public mps::BodyApplication
{
private:
	const GetParams& params;
	mps::Connector* connDB;
	
public:
	BodyApplication(const GetParams& params);
	virtual std::ostream& print (std::ostream& out);
	virtual void programs(std::ostream& out);
	void programs_pizza(std::ostream& out);
	virtual void panel(std::ostream& out);
	virtual void panel_pizza(std::ostream& out);
	
	void set(mps::Connector& connDB);
	
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
	
	long pizza_accepting();
	void pizza_preparing();
	void pizza_steping(steping::Pizza);
	
protected:
	
};

}

#endif
