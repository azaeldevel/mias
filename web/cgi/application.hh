#ifndef MIAS_WEB_APPLICATION_HH
#define MIAS_WEB_APPLICATION_HH


#include <muposys/web/application.hh>
#include <map>

namespace mias
{

void params_get(std::map<std::string, std::string>&);
	
enum class Station
{
	none,
	pizza,
	stove,
	oven,
};

struct GetParams
{
	Station station;
	long order;
	
	GetParams();
};
class BodyApplication : public mps::BodyApplication
{
private:
	GetParams params;
	mps::Connector* connDB;
	
public:
	BodyApplication();
	virtual std::ostream& operator >> (std::ostream& out);
	virtual void programs(std::ostream& out);
	void programs_pizza(std::ostream& out);
	virtual void panel(std::ostream& out);
	
	void set(mps::Connector& connDB);
	
protected:
	
};

class Application : public mps::Application
{
public:
	virtual std::ostream& operator >> (std::ostream& out);
	virtual int main(std::ostream& out = std::cout);
	
	void init();
	Application(BodyApplication&);
	Application(BodyApplication&,const std::string& title);
	virtual ~Application();
	
private:	
	GetParams params;
protected:
	
};

}

#endif
