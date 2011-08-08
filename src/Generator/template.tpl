
#include <Myelin/Myelin.h>
{{#HEADERS}}
#include <{{HEADER}}>{{/HEADERS}}


{{#NAMESPACES}}
namespace {{NAMESPACE}} {
namespace {{NAMESPACE}}Introspection {

void declare_namespace (Myelin::Repository* repo)
{
	Myelin::Namespace* nspace = 0;
	Myelin::Class* klass = 0;
	
	
	/* get namespace */
	nspace = repo->getNamespace ("{{NAMESPACE}}");
	
{{#CLASSES}}
	/* register class type */
	klass = new Myelin::Class ("{{CLASS}}");
	nspace->addClass (klass);
	
	Myelin::REGISTER_CLASS ({{CLASS}}, klass);
	klass->setType (Myelin::TYPE({{CLASS}}));
	
	/* register class function types */
	{{#FUNCTIONS}}klass->addFunction (new Myelin::Function ("{{NAME}}", new Myelin::{{#CONSTANT}}Const{{/CONSTANT}}MemberFunctionType{{PARAM_COUNT}} <{{CLASS}}, {{RETURN}}{{#PARAMS}}, {{TYPE}}{{/PARAMS}}> (&{{CLASS}}::{{NAME}}){{#CONSTANT}}, Myelin::Function::CONSTANT{{/CONSTANT}}));
	{{/FUNCTIONS}}
{{/CLASSES}}
}

}}
{{/NAMESPACES}}


#if defined _WIN32 || defined __CYGWIN__ 
	#define MYELIN_ENTRY_EXPORT __declspec(dllexport)
#else
	#if __GNUC__ >= 4
		#define MYELIN_ENTRY_EXPORT __attribute__ ((visibility("default")))
	#else
		#define MYELIN_ENTRY_EXPORT
	#endif
#endif

extern "C" MYELIN_ENTRY_EXPORT Myelin::Repository* myelin_create_repository ()
{
	Myelin::Repository* repo = new Myelin::Repository ("{{REPO}}");
	
	{{#NAMESPACES}}
	/* declare namespaces */
	{{NAMESPACE}}::{{NAMESPACE}}Introspection::declare_namespace (repo);
	{{/NAMESPACES}}
	
	return repo;
}

