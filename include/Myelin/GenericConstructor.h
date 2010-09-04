
#ifndef MYELIN_GENERIC_CONSTRUCTOR_H_
#define MYELIN_GENERIC_CONSTRUCTOR_H_


#include <stdexcept>
#include <sstream>

#include <Myelin/Config.h>
#include <Myelin/Type.h>
#include <Myelin/Constructor.h>


namespace Myelin
{

	template <typename ClassType>
	class MYELIN_API GenericConstructor : public Constructor
	{
	public:
		/**
		 * Constructor.
		 */
		GenericConstructor () {}
		
		
		GenericConstructor (const Type* param1)
		{
			mParamTypes.push_back (param1);
		}
		
		
		GenericConstructor (const Type* param1,
		                    const Type* param2)
		{
			mParamTypes.push_back (param1);
			mParamTypes.push_back (param2);
		}
		
		
		GenericConstructor (const Type* param1,
		                    const Type* param2,
		                    const Type* param3)
		{
			mParamTypes.push_back (param1);
			mParamTypes.push_back (param2);
			mParamTypes.push_back (param3);
		}
		
		
		template <typename Param1, typename Param2, typename Param3, typename Param4>
		GenericConstructor (const Type* param1,
		                    const Type* param2,
		                    const Type* param3,
		                    const Type* param4)
		{
			mParamTypes.push_back (param1);
			mParamTypes.push_back (param2);
			mParamTypes.push_back (param3);
			mParamTypes.push_back (param4);
		}
		
		
		template <typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
		GenericConstructor (const Type* param1,
		                    const Type* param2,
		                    const Type* param3,
		                    const Type* param4,
		                    const Type* param5)
		{
			mParamTypes.push_back (param1);
			mParamTypes.push_back (param2);
			mParamTypes.push_back (param3);
			mParamTypes.push_back (param4);
			mParamTypes.push_back (param5);
		}
		
		
		
		
		int getParamCount() const { return mParamTypes.size(); }
		
		const Type* getParamType (int index) const { return mParamTypes[index]; }
		
		const TypeList getParamList () const { return mParamTypes; }
		
		
		
		Value call (const List& params) const
		{
			/* wrong number of parameters */
			if (params.size() < mParamTypes.size())
			{
				std::stringstream stream;
				stream << "The constructor takes exactly "
						<< mParamTypes.size() << " parameter(s) instead of "
						<< params.size() << ".";
				
				throw std::runtime_error (stream.str());
			}
			
			
			/* call constructor */
			if (params.size() == 0)
				return new ClassType ();
		}
		
		
		
	protected:
		TypeList mParamTypes;
	};

}


#endif /* MYELIN_GENERIC_CONSTRUCTOR_H_ */
