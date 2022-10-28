
#ifndef MUPOSYS_EXCEPTION_HH
#define MUPOSYS_EXCEPTION_HH

/*
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 *
 * MUPOSYS is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * octetos-cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#if EXPORTING_OCTETOS_CC_DLL
#if _MSC_VER
#define OCTETOS_CC_DECLSPCE_DLL __declspec(dllexport)
#elif __GNUG__

#endif
#elif IMPORTING_OCTETOS_CC_DLL
#if _MSC_VER
#define OCTETOS_CC_DECLSPCE_DLL __declspec(dllimport)
#elif __GNUG__

#endif
#else
	#define OCTETOS_CC_DECLSPCE_DLL
#endif

#if defined(__linux__)
    #include <octetos/core/Exception-v3.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <Exception-v3.hh>
#else
	#error "Plataforma desconocida"
#endif

namespace mps
{

class Exception : public oct::core::v3::Exception
{
public:
	enum Errors
	{
		NO_ERROR,
		VISIBLE_MAIN,
		DB_CONECTION_FAIL,
		DB_READ_FAIL,
		DB_WRITE_FAIL,
	};

public:
	Exception();
	Exception(unsigned int code);
	Exception(unsigned int code,const char* subject);
	Exception(unsigned int code,const char* filename, unsigned int line);
	Exception(unsigned int code,const char* subject,const char* filename, unsigned int line);

	virtual const char* what () const throw ();

private:
};

}

#endif
