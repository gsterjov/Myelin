

#include "Value.h"


/* C api */
MYELIN_API Myelin::Value *
myelin_value_new ()
{
	return new Myelin::Value ();
}


MYELIN_API void
myelin_value_free (Myelin::Value *value)
{
	delete value;
}




MYELIN_API const Myelin::Type *
myelin_value_get_type (Myelin::Value *value) { return value->getType(); }


MYELIN_API bool myelin_value_is_empty (Myelin::Value *value) { return value->isEmpty(); }
MYELIN_API void myelin_value_clear (Myelin::Value *value) { value->clear(); }




/* boolean */
MYELIN_API bool
myelin_value_get_bool (const Myelin::Value *value)
{
	return Myelin::value_cast<bool> (*value);
}


MYELIN_API void
myelin_value_set_bool (Myelin::Value *value, bool val)
{
	value->setValue (val);
}


/* char */
MYELIN_API char
myelin_value_get_char (const Myelin::Value *value)
{
	return Myelin::value_cast<char> (*value);
}


MYELIN_API void
myelin_value_set_char (Myelin::Value *value, char val)
{
	value->setValue (val);
}



MYELIN_API uchar
myelin_value_get_uchar (const Myelin::Value *value)
{
	return Myelin::value_cast<uchar> (*value);
}


MYELIN_API void
myelin_value_set_uchar (Myelin::Value *value, uchar val)
{
	value->setValue (val);
}




/* integer */
MYELIN_API int
myelin_value_get_int (const Myelin::Value *value)
{
	return Myelin::value_cast<int> (*value);
}


MYELIN_API void
myelin_value_set_int (Myelin::Value *value, int val)
{
	value->setValue (val);
}



MYELIN_API uint
myelin_value_get_uint (const Myelin::Value *value)
{
	return Myelin::value_cast<uint> (*value);
}


MYELIN_API void
myelin_value_set_uint (Myelin::Value *value, uint val)
{
	value->setValue (val);
}




/* long */
MYELIN_API long
myelin_value_get_long (const Myelin::Value *value)
{
	return Myelin::value_cast<long> (*value);
}


MYELIN_API void
myelin_value_set_long (Myelin::Value *value, long val)
{
	value->setValue (val);
}



MYELIN_API ulong
myelin_value_get_ulong (const Myelin::Value *value)
{
	return Myelin::value_cast<ulong> (*value);
}


MYELIN_API void
myelin_value_set_ulong (Myelin::Value *value, ulong val)
{
	value->setValue (val);
}




/* 64bit integer */
MYELIN_API int64
myelin_value_get_int64 (const Myelin::Value *value)
{
	return Myelin::value_cast<int64> (*value);
}


MYELIN_API void
myelin_value_set_int64 (Myelin::Value *value, int64 val)
{
	value->setValue (val);
}



MYELIN_API uint64
myelin_value_get_uint64 (const Myelin::Value *value)
{
	return Myelin::value_cast<uint64> (*value);
}


MYELIN_API void
myelin_value_set_uint64 (Myelin::Value *value, uint64 val)
{
	value->setValue (val);
}




/* float */
MYELIN_API float
myelin_value_get_float (const Myelin::Value *value)
{
	return Myelin::value_cast<float> (*value);
}


MYELIN_API void
myelin_value_set_float (Myelin::Value *value, float val)
{
	value->setValue (val);
}




/* double */
MYELIN_API double
myelin_value_get_double (const Myelin::Value *value)
{
	return Myelin::value_cast<double> (*value);
}


MYELIN_API void
myelin_value_set_double (Myelin::Value *value, double val)
{
	value->setValue (val);
}




/* string */
MYELIN_API const char *
myelin_value_get_string (const Myelin::Value *value)
{
	return Myelin::value_cast<const char*> (*value);
}


MYELIN_API void
myelin_value_set_string (Myelin::Value *value, const char *val)
{
	value->setValue (val);
}




/* pointer */
MYELIN_API void *
myelin_value_get_pointer (const Myelin::Value *value)
{
	return Myelin::value_cast<void*> (*value);
}


MYELIN_API void
myelin_value_set_pointer (Myelin::Value *value, void *val)
{
	value->setValue (val);
}


