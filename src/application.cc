



#include "application.hh"


namespace mias
{


BodyApplication::BodyApplication()
{
}
void BodyApplication::options(std::ostream& out)const
{		
	out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\"></a></div>\n";	
}
void BodyApplication::print(std::ostream& out)const
{		
	out << "\t<div id=\"menu\">\n";		
	
		out << "\t\t<div id=\"panel\">\n";				
			out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\"></a></div>\n";
	
			out << "\t\t\t<div class=\"space\"></div>\n";

			if(user_mang) out << "\t\t\t<div id=\"user\"><a href=\"/user-mang.html\"></a></div>\n";
			out << "\t\t\t<div id=\"system\"><a href=\"/system.html\"></a></div>\n";			
		out << "\t\t</div>\n";	

		out << "\t\t<div class=\"space\"></div>\n";

	
		out << "\t\t<div id=\"options\">\n";
			this->options(out);
		out << "\t\t</div>\n";
	
	out << "\t</div>\n";
}


Application::Application(BodyApplication& b) : muposys::Application(b)
{
}
Application::Application(BodyApplication& b,const std::string& t) : muposys::Application(b,t)
{
}
Application::~Application()
{
}
	
void Application::print(std::ostream& out) const
{
	muposys::HTML::print(out);
}
int Application::main(std::ostream& out)
{
	muposys::contenttype(out,"text","html");
	
	if(not session.load(conn))
	{
		head.redirect(0,"/login.html?failure");
		head.print(out);
		return EXIT_SUCCESS;
	}
	
	print(std::cout);

	return EXIT_SUCCESS;
}

}