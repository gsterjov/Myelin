
#ifndef MYELIN_CLASS_H_
#define MYELIN_CLASS_H_


namespace Myelin
{

	/* forward declaration */
	class Function;
	
	
	
	class Class
	{
	public:
		/**
		 * Get class name.
		 */
		virtual const std::string& getName() const = 0;
		
		
		/**
		 * Register function with class.
		 */
		virtual void registerFunction (Function* function) = 0;
		
		
		/**
		 * Get function.
		 */
		virtual const Function* getFunction (const std::string& name) const = 0;
	};

}


#endif /* MYELIN_CLASS_H_ */
