#ifndef MIAS_APPLICATION_HH
#define MIAS_APPLICATION_HH


#include <muposys/application.hh>

namespace mias
{

class BodyApplication : public mps::BodyApplication
{
private:
	
public:
	BodyApplication();

	virtual void programs(std::ostream& out) const;

protected:
};
class Application : public mps::Application
{	
public:
	virtual std::ostream& operator >> (std::ostream& out);
	virtual int main(std::ostream& out = std::cout);
	
	Application(BodyApplication&);
	Application(BodyApplication&,const std::string& title);
	virtual ~Application();

private:	
	
protected:
};

}

#endif
