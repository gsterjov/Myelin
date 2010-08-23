

#include "Value.h"


/* C api */
int
myelin_value_list_size (Myelin::ValueList *list)
{
	return list->size();
}



const Myelin::Type *
myelin_value_get_type (Myelin::Value *value)
{
	return &value->getType();
}



void *
myelin_value_get_data (Myelin::Value *value)
{
	return value->getData();
}





/* boolean */
bool
myelin_value_get_bool (const Myelin::Value *value)
{
	return Myelin::value_cast<bool> (*value);
}


void
myelin_value_set_bool (Myelin::Value *value, bool val)
{
	value->setValue (val);
}


/* char */
char
myelin_value_get_char (const Myelin::Value *value)
{
	return Myelin::value_cast<char> (*value);
}


void
myelin_value_set_char (Myelin::Value *value, char val)
{
	value->setValue (val);
}



uchar
myelin_value_get_uchar (const Myelin::Value *value)
{
	return Myelin::value_cast<uchar> (*value);
}


void
myelin_value_set_uchar (Myelin::Value *value, uchar val)
{
	value->setValue (val);
}




/* integer */
int
myelin_value_get_int (const Myelin::Value *value)
{
	return Myelin::value_cast<int> (*value);
}


void
myelin_value_set_int (Myelin::Value *value, int val)
{
	value->setValue (val);
}



uint
myelin_value_get_uint (const Myelin::Value *value)
{
	return Myelin::value_cast<uint> (*value);
}


void
myelin_value_set_uint (Myelin::Value *value, uint val)
{
	value->setValue (val);
}




/* long */
long
myelin_value_get_long (const Myelin::Value *value)
{
	return Myelin::value_cast<long> (*value);
}


void
myelin_value_set_long (Myelin::Value *value, long val)
{
	value->setValue (val);
}



ulong
myelin_value_get_ulong (const Myelin::Value *value)
{
	return Myelin::value_cast<ulong> (*value);
}


void
myelin_value_set_ulong (Myelin::Value *value, ulong val)
{
	value->setValue (val);
}




/* 64bit integer */
int64
myelin_value_get_int64 (const Myelin::Value *value)
{
	return Myelin::value_cast<int64> (*value);
}


void
myelin_value_set_int64 (Myelin::Value *value, int64 val)
{
	value->setValue (val);
}



uint64
myelin_value_get_uint64 (const Myelin::Value *value)
{
	return Myelin::value_cast<uint64> (*value);
}


void
myelin_value_set_uint64 (Myelin::Value *value, uint64 val)
{
	value->setValue (val);
}




/* float */
float
myelin_value_get_float (const Myelin::Value *value)
{
	return Myelin::value_cast<float> (*value);
}


void
myelin_value_set_float (Myelin::Value *value, float val)
{
	value->setValue (val);
}




/* double */
double
myelin_value_get_double (const Myelin::Value *value)
{
	return Myelin::value_cast<double> (*value);
}


void
myelin_value_set_double (Myelin::Value *value, double val)
{
	value->setValue (val);
}




/* string */
const char *
myelin_value_get_string (const Myelin::Value *value)
{
	return Myelin::value_cast<const char*> (*value);
}


void
myelin_value_set_string (Myelin::Value *value, const char *val)
{
	value->setValue (val);
}




/* pointer */
void *
myelin_value_get_pointer (const Myelin::Value *value)
{
	return Myelin::value_cast<void*> (*value);
}


void
myelin_value_set_pointer (Myelin::Value *value, void *val)
{
	value->setValue (val);
}


