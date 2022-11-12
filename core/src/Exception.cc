
/*
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 * 
 * octetos-cc is free software: you can redistribute it and/or modify it
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
 
#include "Exception.hh"

namespace mias
{
	
Exception::Exception()
{

}
Exception::Exception(unsigned int c) : mps::Exception(c)
{
}
Exception::Exception(unsigned int c,const char* s) : mps::Exception(c,s)
{
}
Exception::Exception(unsigned int c,const char* f, unsigned int l) : mps::Exception(c,f,l)
{
}
Exception::Exception(unsigned int c,const char* s,const char* f, unsigned int l) : mps::Exception(c,s,f,l)
{
}

const char* Exception::what () const throw ()
{
	switch(code())
	{
	case Errors::NO_ERROR:
		return "No error.";
	case Errors::VISIBLE_MAIN:
		return "La ventana principal no deve estar inicialmente visisble(importante para realizar la llamada al Login).";
	case Errors::DB_CONECTION_FAIL:
		return "Falló en la conexion de Base de Datos";
	case Errors::DB_READ_FAIL:
		return "La lectura en Base de Datos falló";
	case Errors::DB_WRITE_FAIL:
		return "La escritura en Base de Datos falló";
	default:
		return "Error desconocido.";
	}
	return "Error desconocido.";
}
	
}
