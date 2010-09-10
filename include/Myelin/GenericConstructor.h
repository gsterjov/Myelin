
#ifndef MYELIN_GENERIC_CONSTRUCTOR_H_
#define MYELIN_GENERIC_CONSTRUCTOR_H_


#include <stdexcept>
#include <sstream>

#include <Myelin/Config.h>
#include <Myelin/Type.h>
#include <Myelin/Constructor.h>
#include <Myelin/Functor.h>


namespace Myelin
{

	/**
	 * Generic constructor.
	 */
	class MYELIN_API GenericConstructor : public Constructor
	{
	public:
		/**
		 * Constructor.
		 */
		GenericConstructor () : mCreator(0) {}
		
		
		
		template <typename ClassType>
		void set ()
		{
			mCreator = new ClassCreator0 <ClassType> ();
		}
		
		
		template <typename ClassType, typename Param1>
		void set ()
		{
			mParamTypes.push_back (TYPE(Param1));
			mCreator = new ClassCreator1 <ClassType, Param1> ();
		}
		
		
		template <typename ClassType, typename Param1, typename Param2>
		void set ()
		{
			mParamTypes.push_back (TYPE(Param1));
			mParamTypes.push_back (TYPE(Param2));
			mCreator = new ClassCreator2 <ClassType, Param1, Param2> ();
		}
		
		
		template <typename ClassType, typename Param1, typename Param2, typename Param3>
		void set ()
		{
			mParamTypes.push_back (TYPE(Param1));
			mParamTypes.push_back (TYPE(Param2));
			mParamTypes.push_back (TYPE(Param3));
			mCreator = new ClassCreator3 <ClassType, Param1, Param2, Param3> ();
		}
		
		
		template <typename ClassType, typename Param1, typename Param2, typename Param3, typename Param4>
		void set ()
		{
			mParamTypes.push_back (TYPE(Param1));
			mParamTypes.push_back (TYPE(Param2));
			mParamTypes.push_back (TYPE(Param3));
			mParamTypes.push_back (TYPE(Param4));
			mCreator = new ClassCreator4 <ClassType, Param1, Param2, Param3, Param4> ();
		}
		
		
		template <typename ClassType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
		void set ()
		{
			mParamTypes.push_back (TYPE(Param1));
			mParamTypes.push_back (TYPE(Param2));
			mParamTypes.push_back (TYPE(Param3));
			mParamTypes.push_back (TYPE(Param4));
			mParamTypes.push_back (TYPE(Param5));
			mCreator = new ClassCreator5 <ClassType, Param1, Param2, Param3, Param4, Param5> ();
		}
		
		
		
		int getParamCount() const { return mParamTypes.size(); }
		
		const Type* getParamType (int index) const { return mParamTypes[index]; }
		
		const TypeList getParamList () const { return mParamTypes; }
		
		
		
		Pointer call (const List& params) const
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
			mCreator->create (params);
		}
		
		
		
	private:
		struct ClassCreator;
		ClassCreator* mCreator;
		
		TypeList mParamTypes;
		
		
		struct ClassCreator
		{
			virtual Pointer create (const List& params) const = 0;
		};
		
		
		
		template <typename ClassType>
		struct ClassCreator0 : ClassCreator
		{
			Pointer create(const List& params) const { return Pointer (
					new ClassType ()); }
		};
		
		
		template <typename ClassType, typename Param1>
		struct ClassCreator1 : ClassCreator
		{
			Pointer create(const List& params) const { return Pointer (
					new ClassType (unpack_param<Param1>(params[0]))); }
		};
		
		
		template <typename ClassType, typename Param1, typename Param2>
		struct ClassCreator2 : ClassCreator
		{
			Pointer create(const List& params) const { return Pointer (
					new ClassType (unpack_param<Param1>(params[0]),
					               unpack_param<Param2>(params[1]))); }
		};
		
		
		template <typename ClassType, typename Param1, typename Param2, typename Param3>
		struct ClassCreator3 : ClassCreator
		{
			Pointer create(const List& params) const { return Pointer (
					new ClassType (unpack_param<Param1>(params[0]),
					               unpack_param<Param2>(params[1]),
					               unpack_param<Param3>(params[2]))); }
		};
		
		
		template <typename ClassType, typename Param1, typename Param2, typename Param3, typename Param4>
		struct ClassCreator4 : ClassCreator
		{
			Pointer create(const List& params) const { return Pointer (
					new ClassType (unpack_param<Param1>(params[0]),
					               unpack_param<Param2>(params[1]),
					               unpack_param<Param3>(params[2]),
					               unpack_param<Param4>(params[3]))); }
		};
		
		
		template <typename ClassType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
		struct ClassCreator5 : ClassCreator
		{
			Pointer create(const List& params) const { return Pointer (
					new ClassType (unpack_param<Param1>(params[0]),
					               unpack_param<Param2>(params[1]),
					               unpack_param<Param3>(params[2]),
					               unpack_param<Param4>(params[3]),
					               unpack_param<Param5>(params[4]))); }
		};
	};

}


#endif /* MYELIN_GENERIC_CONSTRUCTOR_H_ */
