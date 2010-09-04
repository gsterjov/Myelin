

#include "Class.h"
#include "List.h"
#include "Constructor.h"
#include "Function.h"


/* C api */
MYELIN_API const char *
myelin_class_get_name (Myelin::Class *klass)
{
	return klass->getName().c_str();
}



MYELIN_API Myelin::List *
myelin_class_get_namespace (Myelin::Class *klass)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get a list of all functions */
	const std::vector<std::string>& name_space = klass->getNamespace();
	std::vector<std::string>::const_iterator iter;
	
	/* add all functions into the list */
	for (iter = name_space.begin(); iter != name_space.end(); ++iter)
		list->push_back (iter->c_str());
	
	return list;
}




MYELIN_API void
myelin_class_register_constructor (Myelin::Class *klass,
                                   Myelin::Constructor *constructor)
{
	klass->registerConstructor (constructor);
}


MYELIN_API Myelin::List *
myelin_class_get_constructor_list (Myelin::Class *klass)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get a list of all functions */
	const Myelin::ConstructorList& funcs = klass->getConstructorList();
	Myelin::ConstructorList::const_iterator iter;
	
	/* add all functions into the list */
	for (iter = funcs.begin(); iter != funcs.end(); ++iter)
		list->push_back (*iter);
	
	return list;
}




MYELIN_API void
myelin_class_register_function (Myelin::Class *klass,
                                Myelin::Function *function)
{
	klass->registerFunction (function);
}


MYELIN_API Myelin::Function *
myelin_class_get_function (Myelin::Class *klass, const char *name)
{
	return klass->getFunction (name);
}


MYELIN_API Myelin::List *
myelin_class_get_function_list (Myelin::Class *klass)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get a list of all functions */
	Myelin::FunctionList funcs = klass->getFunctionList();
	Myelin::FunctionList::iterator iter;
	
	/* add all functions into the list */
	for (iter = funcs.begin(); iter != funcs.end(); ++iter)
		list->push_back (*iter);
	
	return list;
}



MYELIN_API void *
myelin_class_create_instance (const Myelin::Class *klass,
                              const Myelin::List *params)
{
	return klass->createInstance (*params);
}



MYELIN_API Myelin::Object *
myelin_class_create_object (const Myelin::Class *klass,
                            const Myelin::List *params)
{
	return klass->createObject (*params);
}



MYELIN_API Myelin::Object *
myelin_class_create_object_instance (const Myelin::Class *klass,
                                     void* instance)
{
	return klass->createObject (instance);
}

