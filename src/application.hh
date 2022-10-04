#ifndef MIAS_APPLICATION_HH
#define MIAS_APPLICATION_HH


#include <muposys/application.hh>

namespace mias
{

class BodyApplication : public muposys::BodyApplication
{
private:
	
public:
	BodyApplication();

	virtual void programs(std::ostream& out) const;

protected:
};
class Application : public muposys::Application
{	
public:
	virtual void print(std::ostream& out) const;
	virtual int main(std::ostream& out = std::cout);
	
	Application(BodyApplication&);
	Application(BodyApplication&,const std::string& title);
	virtual ~Application();

private:	
	
protected:
};

}

#endif