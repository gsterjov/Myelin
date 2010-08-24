
#ifndef MYELIN_LIST_H_
#define MYELIN_LIST_H_


#include <Myelin/Value.h>


namespace Myelin
{

	class List
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
		void push_back (const T& value) { mList.push_back (value); }
		
		
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
		T& front() { return value_cast<T> (mList.front()); }
		
		template <typename T>
		const T& front() const { return value_cast<T> (mList.front()); }
		
		
		
		/**
		 * Value at the back of the list.
		 */
		Value& back() { return mList.back(); }
		const Value& back() const { return mList.back(); }
		
		/**
		 * Generic value at the back of the list.
		 */
		template <typename T>
		T& back() { return value_cast<T> (mList.back()); }
		
		template <typename T>
		const T& back() const { return value_cast<T> (mList.back()); }
		
		
		
		/**
		 * Value at the specified index.
		 */
		Value& at (uint n) { return mList.at (n); }
		const Value& at (uint n) const { return mList.at (n); }
		
		/**
		 * Generic value at the specified index.
		 */
		template <typename T>
		T& at (uint n) { return value_cast<T> (mList.at (n)); }
		
		template <typename T>
		const T& at (uint n) const { return value_cast<T> (mList.at (n)); }
		
		
		
		/**
		 * Index access operator.
		 */
		Value& operator[] (uint n) { return mList[n]; }
		const Value& operator[] (uint n) const { return mList[n]; }
		
		
		/**
		 * Generic index access operator.
		 */
		template <typename T>
		T& operator[] (uint n) { return value_cast<T> (mList[n]); }
		
		template <typename T>
		const T& operator[] (uint n) const { return value_cast<T> (mList[n]); }
		
		
		
	private:
		std::vector<Value> mList;
		
	};

}




/* C api */
extern "C"
{

	Myelin::List *myelin_list_new ();
	
	void myelin_list_free (Myelin::List *list);
	
	
	uint myelin_list_size (const Myelin::List *list);
	
	Myelin::Value *myelin_list_index (const Myelin::List *list, uint index);

}



#endif /* MYELIN_LIST_H_ */
