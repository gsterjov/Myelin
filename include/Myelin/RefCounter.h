/*
    Copyright 2009-2010 Goran Sterjov
    This file is part of Myelin.

    Myelin is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Myelin is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Myelin.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MYELIN_REF_COUNTER_H_
#define MYELIN_REF_COUNTER_H_


#include <Myelin/Config.h>


namespace Myelin
{

	/**
	 * Reference counting implementation.
	 */
	class MYELIN_API RefCounter
	{
	public:
		/**
		 * Constructor.
		 */
		RefCounter() : mCounter(1) {}
		
		/**
		 * Copy constructor.
		 */
		RefCounter (const RefCounter& ref) : mCounter (1) {}
		
		/**
		 * Destructor.
		 */
		virtual ~RefCounter() {}
		
		
		/**
		 * Assignment operator.
		 */
		const RefCounter& operator= (const RefCounter& ref)
		{
			mCounter = 1;
			return *this;
		}
		
		
		/**
		 * Reference counter.
		 */
		int count() { return mCounter; }
		
		/**
		 * Increment reference counter.
		 */
		void ref() { ++mCounter; }
		
		/**
		 * Decrement reference counter.
		 */
		void unref() { --mCounter; }
		
		
	private:
		int mCounter;
	};

}


#endif /* MYELIN_REF_COUNTER_H_ */
