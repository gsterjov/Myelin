

#include "TypeInfo.h"


/* C api */
MYELIN_API const Myelin::Type *
type_info_get_type (const Myelin::TypeInfo* info)
{
	return info->getType();
}


MYELIN_API const char *
type_info_get_name (const Myelin::TypeInfo* info)
{
	return info->getName().c_str();
}



MYELIN_API bool
type_info_is_constant (const Myelin::TypeInfo* info)
{
	return info->isConstant();
}



MYELIN_API bool
type_info_is_reference (const Myelin::TypeInfo* info)
{
	return info->isReference();
}



MYELIN_API bool
type_info_is_pointer (const Myelin::TypeInfo* info)
{
	return info->isPointer();
}
