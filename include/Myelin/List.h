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

#ifndef MYELIN_LIST_H_
#define MYELIN_LIST_H_


#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>
#include <Myelin/Value.h>


namespace Myelin
{

	/**
	 * A generic list.
	 */
	class MYELIN_API List : public RefCounter
	{
	public:
		/**
		 * Iterator type.
		 */
		typedef std::vector<Value>::iterator iterator;
		typedef std::vector<Value>::const_iterator const_iterator;
		
		typedef std::vector<Value>::reverse_iterator reverse_iterator;
		typedef std::vector<Value>::const_reverse_iterator const_reverse_iterator;
		
		
		
		/**
		 * Iterator at the start of the list.
		 */
		iterator begin() { return mList.begin(); }
		const_iterator begin() const { return mList.begin(); }
		
		/**
		 * Iterator at the end of the list.
		 */
		iterator end() { return mList.end(); }
		const_iterator end() const { return mList.end(); }
		
		/**
		 * Iterator at the end of the list.
		 */
		reverse_iterator rbegin() { return mList.rbegin(); }
		const_reverse_iterator rbegin() const { return mList.rbegin(); }
		
		/**
		 * Iterator at the end of the list.
		 */
		reverse_iterator rend() { return mList.rend(); }
		const_reverse_iterator rend() const { return mList.rend(); }
		
		
		
		/**
		 * Append value.
		 */
		void push_back (const Value& value) { mList.push_back (value); }
		
		/**
		 * Append generic value.
		 */
		template <typename T>
		void push_back (T value)
		{
			/* explicitly set value so we can store reference values */
			Value val;
			val.set <T> (value);
			mList.push_back (val);
		}
		
		
		/**
		 * Remove last element.
		 */
		void pop_back() { mList.pop_back(); }
		
		
		
		/**
		 * Insert value at the specified position.
		 */
		iterator insert (iterator position, const Value& value)
		{ return mList.insert (position, value); }
		
		
		/**
		 * Insert value at the specified position 'n' times.
		 */
		void insert (iterator position, uint n, const Value& value)
		{ return mList.insert (position, n, value); }
		
		
		/**
		 * Insert values between the two iterators.
		 */
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last)
		{ return mList.insert (position, first, last); }
		
		
		/**
		 * Insert generic value at the specified position.
		 */
		template <typename T>
		iterator insert (iterator position, const T& value)
		{ return mList.insert (position, value); }
		
		
		/**
		 * Insert generic value at the specified position 'n' times.
		 */
		template <typename T>
		void insert (iterator position, uint n, const T& value)
		{ return mList.insert (position, n, value); }
		
		
		
		/**
		 * Remove element from a list.
		 */
		iterator erase (iterator position) { return mList.erase (position); }
		
		/**
		 * Remove element range from a list.
		 */
		iterator erase (iterator first, iterator last)
		{ return mList.erase (first, last); }
		
		
		
		/**
		 * Clear list.
		 */
		void clear () { mList.clear (); }
		
		
		
		/**
		 * List size.
		 */
		uint size() const { return mList.size(); }
		
		
		/**
		 * Is list empty?
		 */
		bool empty() const { return mList.empty(); }
		
		
		/**
		 * Value at the front of the list.
		 */
		Value& front() { return mList.front(); }
		const Value& front() const { return mList.front(); }
		
		/**
		 * Generic value at the front of the list.
		 */
		template <typename T>
		T& front() { return mList.front().get<T>(); }
		
		template <typename T>
		const T& front() const { return mList.front().get<T>(); }
		
		
		
		/**
		 * Value at the back of the list.
		 */
		Value& back() { return mList.back(); }
		const Value& back() const { return mList.back(); }
		
		/**
		 * Generic value at the back of the list.
		 */
		template <typename T>
		T& back() { return mList.back().get<T>(); }
		
		template <typename T>
		const T& back() const { return mList.back().get<T>(); }
		
		
		
		/**
		 * Value at the specified index.
		 */
		Value& at (uint n) { return mList.at (n); }
		const Value& at (uint n) const { return mList.at (n); }
		
		/**
		 * Generic value at the specified index.
		 */
		template <typename T>
		T& at (uint n) { return mList.at(n).get<T>(); }
		
		template <typename T>
		const T& at (uint n) const { return mList.at(n).get<T>(); }
		
		
		
		/**
		 * Index access operator.
		 */
		Value& operator[] (uint n) { return mList[n]; }
		const Value& operator[] (uint n) const { return mList[n]; }
		
		
		/**
		 * Generic index access operator.
		 */
		template <typename T>
		T& operator[] (uint n) { return mList[n].get<T>(); }
		
		template <typename T>
		const T& operator[] (uint n) const { return mList[n].get<T>(); }
		
		
		
	private:
		std::vector<Value> mList;
		
	};

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
extern "C"
{

	/**
	 * Create a new generic list.
	 */
	MYELIN_API Myelin::List *myelin_list_new ();
	
	/**
	 * Increase the reference count.
	 */
	MYELIN_API Myelin::List *myelin_list_ref (Myelin::List *list);
	
	/**
	 * Decrease the reference count.
	 */
	MYELIN_API void myelin_list_unref (Myelin::List *list);
	
	/**
	 * Gets the amount of elements in the list.
	 */
	MYELIN_API uint myelin_list_size (const Myelin::List *list);
	
	/**
	 * Get the value in the list at the given index.
	 */
	MYELIN_API Myelin::Value *myelin_list_index (const Myelin::List *list, uint index);
	
	/**
	 * Append the value at the end of the list.
	 */
	MYELIN_API void myelin_list_append (Myelin::List *list, Myelin::Value *value);

}



#endif /* MYELIN_LIST_H_ */
