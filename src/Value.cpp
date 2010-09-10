

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
myelin_value_get_type (const Myelin::Value *value) { return value->getType(); }


MYELIN_API bool myelin_value_is_empty (const Myelin::Value *value) { return value->isEmpty(); }
MYELIN_API void myelin_value_clear (Myelin::Value *value) { value->clear(); }




/* boolean */
MYELIN_API bool
myelin_value_get_bool (const Myelin::Value *value)
{
	return value->get<bool>();
}

MYELIN_API const bool
myelin_value_get_const_bool (const Myelin::Value *value)
{
	return value->get<const bool>();
}


MYELIN_API void
myelin_value_set_bool (Myelin::Value *value, bool val)
{
	value->set (val);
}

MYELIN_API void
myelin_value_set_const_bool (Myelin::Value *value, const bool val)
{
	value->set (val);
}


/* char */
MYELIN_API char
myelin_value_get_char (const Myelin::Value *value)
{
	return value->get<char>();
}

MYELIN_API const char
myelin_value_get_const_char (const Myelin::Value *value)
{
	return value->get<const char>();
}


MYELIN_API void
myelin_value_set_char (Myelin::Value *value, char val)
{
	value->set (val);
}

MYELIN_API void
myelin_value_set_const_char (Myelin::Value *value, const char val)
{
	value->set (val);
}



MYELIN_API uchar
myelin_value_get_uchar (const Myelin::Value *value)
{
	return value->get<uchar>();
}

MYELIN_API const uchar
myelin_value_get_const_uchar (const Myelin::Value *value)
{
	return value->get<const uchar>();
}


MYELIN_API void
myelin_value_set_uchar (Myelin::Value *value, uchar val)
{
	value->set (val);
}

MYELIN_API void
myelin_value_set_const_uchar (Myelin::Value *value, const uchar val)
{
	value->set (val);
}




/* integer */
MYELIN_API int
myelin_value_get_int (const Myelin::Value *value)
{
	return value->get<int>();
}

MYELIN_API const int
myelin_value_get_const_int (const Myelin::Value *value)
{
	return value->get<const int>();
}


MYELIN_API void
myelin_value_set_int (Myelin::Value *value, int val)
{
	value->set (val);
}

MYELIN_API void
myelin_value_set_const_int (Myelin::Value *value, const int val)
{
	value->set (val);
}



MYELIN_API uint
myelin_value_get_uint (const Myelin::Value *value)
{
	return value->get<uint>();
}

MYELIN_API const uint
myelin_value_get_const_uint (const Myelin::Value *value)
{
	return value->get<const uint>();
}


MYELIN_API void
myelin_value_set_uint (Myelin::Value *value, uint val)
{
	value->set (val);
}

MYELIN_API void
myelin_value_set_const_uint (Myelin::Value *value, const uint val)
{
	value->set (val);
}




/* long */
MYELIN_API long
myelin_value_get_long (const Myelin::Value *value)
{
	return value->get<long>();
}

MYELIN_API const long
myelin_value_get_const_long (const Myelin::Value *value)
{
	return value->get<const long>();
}


MYELIN_API void
myelin_value_set_long (Myelin::Value *value, long val)
{
	value->set (val);
}

MYELIN_API void
myelin_value_set_const_long (Myelin::Value *value, const long val)
{
	value->set (val);
}



MYELIN_API ulong
myelin_value_get_ulong (const Myelin::Value *value)
{
	return value->get<ulong>();
}

MYELIN_API const ulong
myelin_value_get_const_ulong (const Myelin::Value *value)
{
	return value->get<const ulong>();
}


MYELIN_API void
myelin_value_set_ulong (Myelin::Value *value, ulong val)
{
	value->set (val);
}

MYELIN_API void
myelin_value_set_const_ulong (Myelin::Value *value, const ulong val)
{
	value->set (val);
}




/* 64bit integer */
MYELIN_API int64
myelin_value_get_int64 (const Myelin::Value *value)
{
	return value->get<int64>();
}

MYELIN_API const int64
myelin_value_get_const_int64 (const Myelin::Value *value)
{
	return value->get<const int64>();
}


MYELIN_API void
myelin_value_set_int64 (Myelin::Value *value, int64 val)
{
	value->set (val);
}

MYELIN_API void
myelin_value_set_const_int64 (Myelin::Value *value, const int64 val)
{
	value->set (val);
}



MYELIN_API uint64
myelin_value_get_uint64 (const Myelin::Value *value)
{
	return value->get<uint64>();
}

MYELIN_API const uint64
myelin_value_get_const_uint64 (const Myelin::Value *value)
{
	return value->get<const uint64>();
}


MYELIN_API void
myelin_value_set_uint64 (Myelin::Value *value, uint64 val)
{
	value->set (val);
}

MYELIN_API void
myelin_value_set_const_uint64 (Myelin::Value *value, const uint64 val)
{
	value->set (val);
}




/* float */
MYELIN_API float
myelin_value_get_float (const Myelin::Value *value)
{
	return value->get<float>();
}

MYELIN_API const float
myelin_value_get_const_float (const Myelin::Value *value)
{
	return value->get<const float>();
}


MYELIN_API void
myelin_value_set_float (Myelin::Value *value, float val)
{
	value->set (val);
}

MYELIN_API void
myelin_value_set_const_float (Myelin::Value *value, const float val)
{
	value->set (val);
}




/* double */
MYELIN_API double
myelin_value_get_double (const Myelin::Value *value)
{
	return value->get<double>();
}

MYELIN_API const double
myelin_value_get_const_double (const Myelin::Value *value)
{
	return value->get<const double>();
}


MYELIN_API void
myelin_value_set_double (Myelin::Value *value, double val)
{
	value->set (val);
}

MYELIN_API void
myelin_value_set_const_double (Myelin::Value *value, const double val)
{
	value->set (val);
}




/* string */
MYELIN_API const char *
myelin_value_get_string (const Myelin::Value *value)
{
	return value->get<const char*>();
}


MYELIN_API void
myelin_value_set_string (Myelin::Value *value, const char *val)
{
	value->set (val);
}




/* pointer */
MYELIN_API Myelin::Pointer *
myelin_value_get_pointer (const Myelin::Value *value)
{
	return value->getPointer();
}


MYELIN_API const Myelin::Pointer *
myelin_value_get_const_pointer (const Myelin::Value *value)
{
	return value->getPointer();
}


MYELIN_API void
myelin_value_set_pointer (Myelin::Value *value,
                          Myelin::Pointer *val)
{
	value->set (val);
}

MYELIN_API void
myelin_value_set_const_pointer (Myelin::Value *value,
                                const Myelin::Pointer* val)
{
	value->set (val);
}


