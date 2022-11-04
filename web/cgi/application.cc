



#include "application.hh"


namespace mias
{


BodyApplication::BodyApplication()
{
}
void BodyApplication::programs(std::ostream& out)const
{		
	out << "\t\t\t<div id=\"sales\"><a href=\"/mias/sales.html\"></a></div>\n";	
}


Application::Application(BodyApplication& b) : mps::Application(b)
{
}
Application::Application(BodyApplication& b,const std::string& t) : mps::Application(b,t)
{
	head.css("/css/Mkos-Big-Sur/mias/icons/application.css");
}
Application::~Application()
{
}
	
std::ostream& Application::operator >> (std::ostream& out)
{
	Page::operator >>(out);
	
	return out;
}
int Application::main(std::ostream& out)
{
	mps::contenttype(out,"text","html");
	
	if(not has_session())
	{
		head.redirect(0,"/login.html?failure");
		head >> out;
		return EXIT_SUCCESS;
	}
	
	(*this)>> out;

	return EXIT_SUCCESS;
}

}
