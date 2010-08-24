
#ifndef MYELIN_TYPE_H_
#define MYELIN_TYPE_H_


#include <typeinfo>
#include <vector>
#include <stdint.h>



namespace Myelin
{

	typedef std::type_info Type;
	typedef std::vector<const Type*> TypeList;

}


/* integer types */
typedef int64_t   int64;
typedef int32_t   int32;
typedef int16_t   int16;
typedef int8_t    int8;

typedef uint64_t  uint64;
typedef uint32_t  uint32;
typedef uint16_t  uint16;
typedef uint8_t   uint8;



/* unsigned numbers */
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;



#endif /* MYELIN_TYPE_H_ */
