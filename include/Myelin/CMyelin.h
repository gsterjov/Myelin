
#ifndef CMYELIN_H_
#define CMYELIN_H_


#include <Myelin/MetaClass.h>
#include <Myelin/MetaObject.h>
#include <Myelin/MetaFunction.h>
#include <Myelin/Value.h>


extern "C"
{

	struct MyelinArray
	{
		int size;
		Myelin::MetaFunction **data;
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
	
	
	
	Myelin::BaseMetaClass **meta_class_get_all ()
	{
		Myelin::BaseMetaClass **array = new Myelin::BaseMetaClass*[Myelin::Classes.size()];
		
		
		std::map<std::string, Myelin::BaseMetaClass*>::iterator iter;
		
		int i = 0;
		for (iter = Myelin::Classes.begin(); iter != Myelin::Classes.end(); iter++)
		{
			array[i] = iter->second;
			++i;
		}
		
		
		return array;
	}
	
	
	
	
	MyelinArray *meta_class_get_function_list (const char *class_name)
	{
		Myelin::BaseMetaClass *meta_class = Myelin::Classes[class_name];
		std::vector<Myelin::MetaFunction*> list = meta_class->getFunctionList();
		
		
		MyelinArray *array = new MyelinArray();
		array->size = list.size();
		array->data = new Myelin::MetaFunction*[array->size];
		
		
		std::vector<Myelin::MetaFunction*>::iterator iter;
		
		int i = 0;
		for (iter = list.begin(); iter != list.end(); iter++)
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
	
	
	
	
	const char *meta_function_get_name (Myelin::MetaFunction *function)
	{
		return function->getName().c_str();
	}
	

}


#endif /* CMYELIN_H_ */
