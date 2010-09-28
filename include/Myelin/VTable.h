
#ifndef MYELIN_VTABLE_H_
#define MYELIN_VTABLE_H_


#include <string>
#include <map>

#include <Myelin/Config.h>
#include <iostream>

namespace Myelin
{

	/* forward declaration */
	class Function;
	
	
	
	/**
	 * VTable to store functions overriding virtual functions.
	 */
	class MYELIN_API VTable
	{
	public:
		/**
		 * Get a function from the virtual function table.
		 */
		const Function* get (const std::string& name) const;
		
		/**
		 * Set a function in the virtual function table.
		 */
		void set (const Function* function);
		
		
	private:
		/* virtual function storage */
		typedef std::map<std::string, const Function*> FunctionTable;
		FunctionTable mTable;
	};
	
	
	
	
	/**
	 * Allows access to call overriden virtual functions.
	 */
	template <typename ClassType>
	class MYELIN_API Overridable
	{
	public:
		/**
		 * Get the virtual function table.
		 */
		static VTable* getVTable () { return mTable; }
		
		
	protected:
		/**
		 * Get a virtual function from the virtual function table.
		 */
		const Function* get (const std::string& name) const
		{
			return mTable->get (name);
		}
		
		
	private:
		static VTable* mTable;
	};
	
	
	/* static table declaration */
	template <typename ClassType>
	VTable* Overridable<ClassType>::mTable = new VTable();

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/


extern "C"
{

	/**
	 * Get a function from the virtual function table with the matching name.
	 */
	MYELIN_API const Myelin::Function *myelin_vtable_get (const Myelin::VTable *vtable,
	                                                      const char *name);
	
	/**
	 * Set a function in the virtual function table.
	 */
	MYELIN_API void myelin_vtable_set (Myelin::VTable *vtable,
	                                   const Myelin::Function *function);

}



#endif /* MYELIN_VTABLE_H_ */
