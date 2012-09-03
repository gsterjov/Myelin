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

#ifndef MYELIN_FUNCTION_H_
#define MYELIN_FUNCTION_H_


#include <string>

#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>
#include <Myelin/Type.h>
#include <Myelin/Value.h>
#include <Myelin/List.h>


namespace Myelin
{

	/* forward declarations */
	class FunctionType;
	
	
	/**
	 * Free or member function.
	 */
	class MYELIN_API Function : public RefCounter
	{
	public:
		/**
		 * Function properties.
		 */
		enum Properties
		{
			NONE     = 0,      /** Simple plain function */
			CONSTANT = 1 << 0, /** A constant function */
			VIRTUAL  = 1 << 1, /** A virtual function */
			PURE     = 1 << 2  /** A pure virtual function */
		};
		
		
		
		/**
		 * Constructor.
		 */
		Function (const std::string& name,
		          FunctionType* type,
		          int properties = NONE);
		
		/**
		 * Destructor.
		 */
		virtual ~Function ();
		
		
		/**
		 * Get the function name.
		 */
		const std::string& getName () const { return mName; }
		
		/**
		 * Get the function type.
		 */
		const FunctionType* getType () const { return mType; }
		
		
		/**
		 * Is the function constant?
		 */
		bool isConstant () { return mProperties & CONSTANT; }
		
		/**
		 * Is the function virtual?
		 */
		bool isVirtual () { return mProperties & VIRTUAL; }
		
		/**
		 * Is the function pure virtual?
		 */
		bool isPure () { return mProperties & PURE; }
		
		
		/**
		 * Call the function.
		 */
		Value call (const List& params) const;
		
		
		/**
		 * Bind an instance to the member function.
		 */
		void bind (const Value& instance);
		
		
	private:
		std::string mName;
		int mProperties;
		FunctionType* mType;
	};
	
	
	
	
	/**
	 * The function type interface.
	 */
	class FunctionType : public RefCounter
	{
	public:
		/**
		 * Destructor.
		 */
		virtual ~FunctionType() {}
		
		/**
		 * The return type of the function.
		 */
		const Type* getReturnType() const { return mReturnType; }
		
		/**
		 * Get the parameter type at the given index.
		 */
		const Type* getParamType (int index) const { return mParamTypes[index]; }
		
		/**
		 * The parameter types of the function.
		 */
		const TypeList& getParamTypes() const { return mParamTypes; }
		
		/**
		 * The amount of parameters the function requires.
		 */
		int getParamCount() const { return mParamTypes.size(); }
		
		/**
		 * Check supplied parameters to see if it can be handled by the
		 * function.
		 */
		bool checkParamTypes (const List& params) const;
		
		
		/**
		 * Set the instance to call the function on if it is a member function.
		 */
		virtual void setInstance (const Value& instance) {}
		
		
		/**
		 * Call the function.
		 */
		virtual Value call (const List& params) const = 0;
		
		
	protected:
		TypeList mParamTypes;
		const Type* mReturnType;
	};
	
	
	
	
	/**
	 * A custom function type used to create callbacks in another language.
	 */
	class CustomFunctionType : public FunctionType
	{
	public:
		typedef Value* (*Callback)(const List* params);
		
		CustomFunctionType (Callback callback) : mCallback(callback) {}
		
		void addParamType (const Type* type) { mParamTypes.push_back (type); }
		void setReturnType (const Type* type) { mReturnType = type; }
		
		Value call (const List& params) const;
		
		
	private:
		Callback mCallback;
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
	 * Create a new function.
	 */
	MYELIN_API Myelin::Function *myelin_function_new (const char *name,
	                                                  Myelin::FunctionType *type);
	
	/**
	 * Increase the reference count.
	 */
	MYELIN_API Myelin::Function *myelin_function_ref (Myelin::Function *function);
	
	/**
	 * Decrease the reference count.
	 */
	MYELIN_API void myelin_function_unref (Myelin::Function *function);
	
	
	/**
	 * Get the name of the function.
	 */
	MYELIN_API const char *myelin_function_get_name (Myelin::Function *function);
	
	/**
	 * Get the type of the function.
	 */
	MYELIN_API const Myelin::FunctionType *myelin_function_get_type (Myelin::Function *function);
	
	/**
	 * Is the function constant?
	 */
	MYELIN_API bool myelin_function_is_constant (Myelin::Function *function);
	
	/**
	 * Is the function virtual?
	 */
	MYELIN_API bool myelin_function_is_virtual (Myelin::Function *function);
	
	/**
	 * Is the function pure virtual?
	 */
	MYELIN_API bool myelin_function_is_pure (Myelin::Function *function);
	
	/**
	 * Call the function.
	 */
	MYELIN_API Myelin::Value *myelin_function_call (Myelin::Function *function,
	                                                const Myelin::List *params);
	
	/**
	 * Bind the function to the given instance.
	 */
	MYELIN_API void myelin_function_bind (Myelin::Function *function,
	                                      const Myelin::Value *instance);
	
	
	
	
	/**
	 * Get the function's return type.
	 */
	MYELIN_API const Myelin::Type *myelin_function_type_get_return_type (Myelin::FunctionType *type);
	
	/**
	 * Get the amount of parameters specified by the function.
	 */
	MYELIN_API int myelin_function_type_get_param_count (Myelin::FunctionType *type);
	
	/**
	 * Get the parameter type at the specified index.
	 */
	MYELIN_API const Myelin::Type *myelin_function_type_get_param_type (Myelin::FunctionType *type,
	                                                                    int index);
	
	/**
	 * Get a list of all the parameter types.
	 */
	MYELIN_API Myelin::List *myelin_function_type_get_param_types (Myelin::FunctionType *type);
	
	/**
	 * Can the function handle the given parameter list.
	 */
	MYELIN_API bool myelin_function_type_check_param_types (Myelin::FunctionType *type,
	                                                        const Myelin::List* params);
	
	/**
	 * Set the instance the funciton type should call on.
	 */
	MYELIN_API void myelin_function_type_set_instance (Myelin::FunctionType *type,
	                                                   const Myelin::Value *instance);
	
	/**
	 * Call the function specified by the type.
	 */
	MYELIN_API Myelin::Value *myelin_function_type_call (Myelin::FunctionType *type,
	                                                     const Myelin::List *params);
	
	
	
	
	/**
	 * C callback function type.
	 */
	typedef Myelin::Value* (*Callback)(const Myelin::List* params);
	
	
	/**
	 * Create a custom function type.
	 */
	MYELIN_API Myelin::CustomFunctionType *myelin_custom_function_type_new (Callback callback);
	
	/**
	 * Increase the reference count.
	 */
	MYELIN_API Myelin::CustomFunctionType *myelin_custom_function_type_ref (Myelin::CustomFunctionType *func);
	
	/**
	 * Decrease the reference count.
	 */
	MYELIN_API void myelin_custom_function_type_unref (Myelin::CustomFunctionType *func);
	
	
	/**
	 * Add a parameter type to the custom function type.
	 */
	MYELIN_API void myelin_custom_function_type_add_param_type (Myelin::CustomFunctionType *func,
	                                                            const Myelin::Type *type);
	
	/**
	 * Set the return type of the custom function type.
	 */
	MYELIN_API void myelin_custom_function_type_set_return_type (Myelin::CustomFunctionType *func,
	                                                             const Myelin::Type *type);
	
	/**
	 * Call the custom function type.
	 */
	MYELIN_API Myelin::Value *myelin_custom_function_type_call (Myelin::CustomFunctionType *func,
	                                                            const Myelin::List *params);

}



#endif /* MYELIN_FUNCTION_H_ */
