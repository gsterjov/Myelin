/*
    Copyright 2009-2010 Goran Sterjov
    This file is part of Myelin.

    Myelin is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Myelin is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Myelin.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Value.h"


namespace Myelin
{

	/* default constructor */
	Value::Value () : mData(0)
	{
		
	}
	
	
	/* copy constructor */
	Value::Value (const Value& ref) : mData(ref.mData->clone())
	{
		
	}
	
	
	/* destructor */
	Value::~Value ()
	{
		clear ();
	}
	
	
	
	/* assignment */
	const Value& Value::operator= (const Value& ref)
	{
		mData = ref.mData->clone();
		return *this;
	}
	
	
	/* value type */
	const Type* Value::getType() const
	{
		return mData ? mData->getType() : TYPE(void);
	}
	
	
	
	/* clear value */
	void Value::clear ()
	{
		if (mData) delete mData;
		mData = 0;
	}
	
	
	
	/* get pointer value */
	void* Value::asPointer () const
	{
		/* empty value */
		if (isEmpty())
			throw std::invalid_argument ("Cannot cast value type to "
					"a generic pointer type because the value is empty");
		
		
		/* value is already a pointer */
		if (mData->getType()->isPointer())
			return static_cast<GenericData<void*>*> (mData)->getData();
		
		/* create a pointer */
		else return mData->asPointer();
		
	}

}


/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
Myelin::Value *
myelin_value_new ()
{
	return new Myelin::Value ();
}


Myelin::Value *
myelin_value_ref (Myelin::Value *value)
{
	value->ref();
	return value;
}


void
myelin_value_unref (Myelin::Value *value)
{
	value->unref();
	if (value->count() == 0) delete value;
}




const Myelin::Type *
myelin_value_get_type (const Myelin::Value *value) { return value->getType(); }


bool myelin_value_is_empty (const Myelin::Value *value) { return value->isEmpty(); }
void myelin_value_clear (Myelin::Value *value) { value->clear(); }




/* boolean */
bool
myelin_value_get_bool (const Myelin::Value *value)
{
	return value->get<bool>();
}


void
myelin_value_set_bool (Myelin::Value *value, bool val)
{
	value->set (val);
}

void
myelin_value_set_const_bool (Myelin::Value *value, const bool val)
{
	value->set (val);
}


/* char */
char
myelin_value_get_char (const Myelin::Value *value)
{
	return value->get<char>();
}


void
myelin_value_set_char (Myelin::Value *value, char val)
{
	value->set (val);
}

void
myelin_value_set_const_char (Myelin::Value *value, const char val)
{
	value->set (val);
}



uchar
myelin_value_get_uchar (const Myelin::Value *value)
{
	return value->get<uchar>();
}


void
myelin_value_set_uchar (Myelin::Value *value, uchar val)
{
	value->set (val);
}

void
myelin_value_set_const_uchar (Myelin::Value *value, const uchar val)
{
	value->set (val);
}




/* integer */
int
myelin_value_get_int (const Myelin::Value *value)
{
	return value->get<int>();
}


void
myelin_value_set_int (Myelin::Value *value, int val)
{
	value->set (val);
}

void
myelin_value_set_const_int (Myelin::Value *value, const int val)
{
	value->set (val);
}



uint
myelin_value_get_uint (const Myelin::Value *value)
{
	return value->get<uint>();
}


void
myelin_value_set_uint (Myelin::Value *value, uint val)
{
	value->set (val);
}

void
myelin_value_set_const_uint (Myelin::Value *value, const uint val)
{
	value->set (val);
}




/* long */
long
myelin_value_get_long (const Myelin::Value *value)
{
	return value->get<long>();
}


void
myelin_value_set_long (Myelin::Value *value, long val)
{
	value->set (val);
}

void
myelin_value_set_const_long (Myelin::Value *value, const long val)
{
	value->set (val);
}



ulong
myelin_value_get_ulong (const Myelin::Value *value)
{
	return value->get<ulong>();
}


void
myelin_value_set_ulong (Myelin::Value *value, ulong val)
{
	value->set (val);
}

void
myelin_value_set_const_ulong (Myelin::Value *value, const ulong val)
{
	value->set (val);
}




/* 64bit integer */
int64
myelin_value_get_int64 (const Myelin::Value *value)
{
	return value->get<int64>();
}


void
myelin_value_set_int64 (Myelin::Value *value, int64 val)
{
	value->set (val);
}

void
myelin_value_set_const_int64 (Myelin::Value *value, const int64 val)
{
	value->set (val);
}



uint64
myelin_value_get_uint64 (const Myelin::Value *value)
{
	return value->get<uint64>();
}


void
myelin_value_set_uint64 (Myelin::Value *value, uint64 val)
{
	value->set (val);
}

void
myelin_value_set_const_uint64 (Myelin::Value *value, const uint64 val)
{
	value->set (val);
}




/* float */
float
myelin_value_get_float (const Myelin::Value *value)
{
	return value->get<float>();
}


void
myelin_value_set_float (Myelin::Value *value, float val)
{
	value->set (val);
}

void
myelin_value_set_const_float (Myelin::Value *value, const float val)
{
	value->set (val);
}




/* double */
double
myelin_value_get_double (const Myelin::Value *value)
{
	return value->get<double>();
}


void
myelin_value_set_double (Myelin::Value *value, double val)
{
	value->set (val);
}

void
myelin_value_set_const_double (Myelin::Value *value, const double val)
{
	value->set (val);
}




/* string */
const char *
myelin_value_get_string (const Myelin::Value *value)
{
	const Myelin::Type* val_t = value->getType();
	
	/* convert std::string type to C string type */
	if (val_t->getAtom() == Myelin::TYPE (std::string)->getAtom())
	{
		/* pointer type */
		if (val_t->isPointer())
			return value->get<const std::string*>()->c_str();
		
		/* reference type */
		else if (val_t->isReference())
			return value->get<const std::string&>().c_str();
		
		/* value type */
		else return value->get<std::string>().c_str();
	}
	
	/* normal C string type */
	else return value->get<const char*>();
}


void
myelin_value_set_string (Myelin::Value *value, const char *val)
{
	value->set<std::string> (val);
//	value->set (val);
}




/* pointer */
void *
myelin_value_as_pointer (const Myelin::Value *value)
{
	return value->asPointer();
}


const void *
myelin_value_as_const_pointer (const Myelin::Value *value)
{
	return value->asPointer();
}


void
myelin_value_set_pointer (Myelin::Value *value,
                          const Myelin::Type *type,
                          void *ptr)
{
	value->set (type, ptr);
}

void
myelin_value_set_const_pointer (Myelin::Value *value,
                                const Myelin::Type *type,
                                const void *ptr)
{
	value->set (type, ptr);
}


