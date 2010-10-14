

#include "Value.h"


namespace Myelin
{

	/* default constructor */
	Value::Value () : mData(0)
	{
		
	}
	
	
	/* copy constructor */
	Value::Value (const Value& ref) : mData(ref.mData)
	{
		if (mData) mData->ref();
	}
	
	
	/* destructor */
	Value::~Value ()
	{
		clear ();
	}
	
	
	
	/* assignment */
	const Value& Value::operator= (const Value& ref)
	{
		mData = ref.mData;
		if (mData) mData->ref();
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
		if (mData)
		{
			mData->unref();
			
			if (mData->count() == 0)
				delete mData;
			
			mData = 0;
		}
	}
	
	
	
	/* get pointer value */
	Pointer* Value::getPointer () const
	{
		/* empty value */
		if (isEmpty())
			throw std::invalid_argument ("Cannot cast value type to "
					"a generic pointer type because the value is empty");
		
		
		const Type* val_t = mData->getType();
		
		/* we have a generic pointer */
		if (val_t->getAtom() == TYPE(Pointer)->getAtom())
		{
			if      (val_t->isPointer())   return get<Pointer*>();
			else if (val_t->isReference()) return &get<Pointer&>();
			else return &get<Pointer>();
		}
		
		/* not a generic pointer */
		else if (val_t->isPointer())
		{
			/* wrap pointer in a generic pointer */
			Pointer* ptr = new Pointer (mData);
			
			/* we dont want ownership of the created pointer */
			ptr->unref();
			return ptr;
		}
		
		
		/* create a pointer */
		else
		{
			Pointer* ptr = new Pointer (mData->getPointer(),
					mData->getPointerType());
			
			ptr->unref();
			return ptr;
		}
		
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
Myelin::Pointer *
myelin_value_get_pointer (const Myelin::Value *value)
{
	return value->getPointer();
}


const Myelin::Pointer *
myelin_value_get_const_pointer (const Myelin::Value *value)
{
	return value->getPointer();
}


void
myelin_value_set_pointer (Myelin::Value *value,
                          Myelin::Pointer *val)
{
	val->ref();
	value->set (val);
}

void
myelin_value_set_const_pointer (Myelin::Value *value,
                                const Myelin::Pointer *val)
{
	value->set (val);
}


