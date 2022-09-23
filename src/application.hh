#ifndef MIAS_APPLICATION_HH
#define MIAS_APPLICATION_HH


#include <muposys/html.hh>

namespace muposys
{

class BodyApplication : public muposys::Body
{
private:
	
public:
	BodyApplication();

	virtual void print(std::ostream& out) const;
	virtual void options(std::ostream& out) const;

protected:
	bool user_mang;	
};
class Application : public muposys::HTML
{	
public:
	virtual void print(std::ostream& out) const;
	virtual int main(std::ostream& out = std::cout);
	
	Application(BodyApplication&);
	Application(const BodyApplication&);
	~Application();

private:	
	
protected:
};

}

#endif