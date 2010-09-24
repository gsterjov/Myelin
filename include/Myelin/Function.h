
#ifndef MYELIN_FUNCTION_H_
#define MYELIN_FUNCTION_H_


#include <string>
#include <Myelin/Config.h>
#include <Myelin/Type.h>


namespace Myelin
{

	/* forward declarations */
	class Value;
	class List;
	class Pointer;
	
	class FunctionType;
	
	
	/**
	 * Free or member function.
	 */
	class MYELIN_API Function
	{
	public:
		/**
		 * Constructor.
		 */
		Function (const std::string& name, FunctionType* type);
		
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
		 * Call the function.
		 */
		Value call (const List& params) const;
		
		
		/**
		 * Bind an instance to the member function.
		 */
		void bind (const Pointer& instance);
		
		
	private:
		std::string mName;
		FunctionType* mType;
	};
	
	
	
	
	/**
	 * The function type interface.
	 */
	class FunctionType
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
		virtual void setInstance (const Pointer& instance) {}
		
		
		/**
		 * Call the function.
		 */
		virtual Value call (const List& params) const = 0;
		
		
	protected:
		TypeList mParamTypes;
		const Type* mReturnType;
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
	 * Get the name of the function.
	 */
	MYELIN_API const char *myelin_function_get_name (Myelin::Function *function);
	
	/**
	 * Get the type of the function.
	 */
	MYELIN_API const Myelin::FunctionType *myelin_function_get_type (Myelin::Function *function);
	
	/**
	 * Call the function.
	 */
	MYELIN_API Myelin::Value *myelin_function_call (Myelin::Function *function,
	                                                const Myelin::List *params);
	
	/**
	 * Bind the function to the given instance.
	 */
	MYELIN_API void myelin_function_bind (Myelin::Function *function,
	                                      const Myelin::Pointer *instance);
	
	
	
	
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
	                                                   const Myelin::Pointer *instance);
	
	/**
	 * Call the function specified by the type.
	 */
	MYELIN_API Myelin::Value *myelin_function_type_call (Myelin::FunctionType *type,
	                                                     const Myelin::List *params);

}



#endif /* MYELIN_FUNCTION_H_ */
