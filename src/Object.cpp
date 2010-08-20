

#include "Object.h"


namespace Myelin
{

	Value Object::call (const std::string& method)
	{
		ValueList args;
		call (method, args);
	}
	
	
	Value Object::call (const std::string& method, const Value& arg1)
	{
		ValueList args;
		args.push_back (arg1);
		call (method, args);
	}
	
	
	Value Object::call (const std::string& method, const Value& arg1,
	                                               const Value& arg2)
	{
		ValueList args;
		args.push_back (arg1);
		args.push_back (arg2);
		call (method, args);
	}
	
	
	Value Object::call (const std::string& method, const Value& arg1,
	                                               const Value& arg2,
	                                               const Value& arg3)
	{
		ValueList args;
		args.push_back (arg1);
		args.push_back (arg2);
		args.push_back (arg3);
		call (method, args);
	}
	
	
	Value Object::call (const std::string& method, const Value& arg1,
	                                               const Value& arg2,
	                                               const Value& arg3,
	                                               const Value& arg4)
	{
		ValueList args;
		args.push_back (arg1);
		args.push_back (arg2);
		args.push_back (arg3);
		args.push_back (arg4);
		call (method, args);
	}
	
	
	Value Object::call (const std::string& method, const Value& arg1,
	                                               const Value& arg2,
	                                               const Value& arg3,
	                                               const Value& arg4,
	                                               const Value& arg5)
	{
		ValueList args;
		args.push_back (arg1);
		args.push_back (arg2);
		args.push_back (arg3);
		args.push_back (arg4);
		args.push_back (arg5);
		call (method, args);
	}

}
