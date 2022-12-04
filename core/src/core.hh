
#ifndef MIAS_CORE_CORE_HH
#define MIAS_CORE_CORE_HH

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
 * */


namespace mias
{
	enum class ServiceStep
	{
		none,
		created,
		working,
		retarded,
		cooked,
		waiting,
		delivered,
		cancel,
	};

	enum class Station
	{
		none,
		pizza,
		stove,
		oven,
		salad,
	};

	namespace steping
	{
		enum class Eat
		{
			none,
			created,
			accept,
			accepted,
			prepare,
			preparing,
			prepared,
			cook,
			cooking,//en el horno
			cooked,
			finalized,
			cancel,
		};

		enum class Pizza
		{
			none,
			created,
			accept,
			accepted,
			prepare,
			preparing,
			prepared,
			bake,
			baking,//en el horno
			baked,
			finalized,
			cancel,
		};

		enum class Stove
		{
			none,
			created,
			accept,
			accepted,
			prepare,
			preparing,
			prepared,
			fry,
			fring,//en el horno
			fryed,
			finalized,
			cancel,
		};


	}


const char* to_string(steping::Eat);
const char* to_text(steping::Eat);
steping::Eat to_step(const char*);
const char* to_string(steping::Pizza);
const char* to_text(steping::Pizza);
const char* to_string(Station s);
const char* to_text(Station s);
Station to_station(const char*);
const char* to_string(ServiceStep s);
const char* to_text(ServiceStep s);
void to_step(const char* str, steping::Pizza& step);

}

#endif
