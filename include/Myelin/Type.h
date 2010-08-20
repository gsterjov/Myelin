
#ifndef MYELIN_TYPE_H_
#define MYELIN_TYPE_H_


#include <typeinfo>
#include <vector>


namespace Myelin
{

	typedef const std::type_info& Type;
	typedef std::vector<Type> TypeList;

}


#endif /* MYELIN_TYPE_H_ */
