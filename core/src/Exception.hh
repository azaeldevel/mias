
#ifndef MIAS_CORE_EXCEPTION_HH
#define MIAS_CORE_EXCEPTION_HH

/**
 *  This file is part of mias.
 *  mias is a muposys's implementation.
 *  Copyright (C) 2022  Azael Reyes
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#ifdef __linux__
    #include <muposys/core/src/Exception.hh>
#elif defined MSYS2
    #include <muposys/core/src/Exception.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <Exception.hh>
#else
	#error "Plataforma desconocida"
#endif

namespace mias
{

class Exception : public mps::Exception
{
public:
	enum Errors
	{
		NO_ERROR,
		VISIBLE_MAIN,
		DB_CONECTION_FAIL,
		DB_READ_FAIL,
		DB_WRITE_FAIL,
		INTERNAL_ERROR,
	};

public:
	Exception();
	Exception(const Exception&);
	Exception(Exception&&);

	Exception(unsigned int code);
	Exception(unsigned int code,const char* filename, unsigned int line);

	Exception(unsigned int code,const char* message);
	Exception(unsigned int code,const char* message,const char* filename, unsigned int line);

	Exception(const std::string& message);
	Exception(const std::string& message,const char* filename, unsigned int line);

	Exception(unsigned int code,const std::string& message);
	Exception(unsigned int code,const std::string& message,const char* filename, unsigned int line);
	virtual ~Exception();

	virtual const char* what () const throw ();

private:

};

}

#endif
