
#ifndef CMYELIN_H_
#define CMYELIN_H_


#include <Myelin/MetaClass.h>
#include <Myelin/MetaObject.h>
#include <Myelin/MetaFunction.h>
#include <Myelin/Value.h>
#include <iostream>


extern "C"
{

	struct MyelinArray
	{
		int size;
		void **data;
	};
	
	
	MyelinArray *myelin_array_new ()
	{
		return new MyelinArray();
	}
	
	
	void myelin_array_free (MyelinArray *array)
	{
		delete array->data;
		delete array;
	}
	
	
	int myelin_array_size (MyelinArray *array)
	{
		return array->size;
	}
	
	
	void *myelin_array_index (MyelinArray *array, int index)
	{
		return array->data[index];
	}
	
	
	
	
	
	Myelin::BaseMetaClass *meta_class_get (const char *class_name)
	{
		return Myelin::Classes[class_name];
	}
	
	
	
	MyelinArray *meta_class_get_class_list (const char *name_space)
	{
		MyelinArray *array = new MyelinArray();
		array->size = Myelin::Classes.size();
		array->data = new void*[array->size];
		
		
		std::map<std::string, Myelin::BaseMetaClass*>::iterator iter;
		
		int i = 0;
		for (iter = Myelin::Classes.begin(); iter != Myelin::Classes.end(); ++iter)
		{
			array->data[i] = iter->second;
			++i;
		}
		
		return array;
	}
	
	
	
	const char *meta_class_get_name (Myelin::BaseMetaClass *meta_class)
	{
		return meta_class->getName().c_str();
	}
	
	
	
	
	
	
	
	
	MyelinArray *meta_class_get_function_list (const char *class_name)
	{
		Myelin::BaseMetaClass *meta_class = Myelin::Classes[class_name];
		std::vector<Myelin::MetaFunction*> list = meta_class->getFunctionList();
		
		
		MyelinArray *array = new MyelinArray();
		array->size = list.size();
		array->data = new void*[array->size];
		
		
		std::vector<Myelin::MetaFunction*>::iterator iter;
		
		int i = 0;
		for (iter = list.begin(); iter != list.end(); ++iter)
		{
			array->data[i] = *iter;
			++i;
		}
		
		return array;
	}
	
	
	
	
	Myelin::MetaObject *meta_object_new (const char *class_name)
	{
		return new Myelin::MetaObject (class_name);
	}
	
	
	
	void meta_object_call (Myelin::MetaObject *object, const char *function_name)
	{
		object->call (function_name, 2);
	}
	
	
//	Myelin::Value meta_object_call2 (Myelin::MetaObject *object,
//			const char *function_name,
//			Myelin::ValueList list)
//	{
//		
//	}
	
	
	
	
	const char *meta_function_get_name (Myelin::MetaFunction *function)
	{
		return function->getName().c_str();
	}
	

}


#endif /* CMYELIN_H_ */
