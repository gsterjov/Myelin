
#ifndef MYELIN_META_FACTORY_H_
#define MYELIN_META_FACTORY_H_


#include <string>
#include <map>

#include <Myelin/MetaClass.h>


namespace Myelin
{

	class MetaFactory
	{
	public:
		
		template <typename Class>
		static MetaClass* createMetaClass (std::string& name)
		{
			mClasses[name] = new MetaClass (name);
		}
		
		
		
	private:
		std::map<std::string, MetaClass*> mClasses;
	};

}


#endif /* MYELIN_META_FACTORY_H_ */
