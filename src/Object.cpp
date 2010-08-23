

#include "Object.h"


namespace Myelin
{

	Value Object::call (const std::string& function,
	                           const ValueList& params)
	{
		return callImpl (function, params);
	}
	
	
	Value Object::call (const std::string& function)
	{
		ValueList params;
		return call (function, params);
	}
	
	
	Value Object::call (const std::string& function, const Value& param1)
	{
		ValueList params;
		params.push_back (param1);
		return call (function, params);
	}
	
	
	Value Object::call (const std::string& function, const Value& param1,
	                                                 const Value& param2)
	{
		ValueList params;
		params.push_back (param1);
		params.push_back (param2);
		return call (function, params);
	}
	
	
	Value Object::call (const std::string& function, const Value& param1,
	                                                 const Value& param2,
	                                                 const Value& param3)
	{
		ValueList params;
		params.push_back (param1);
		params.push_back (param2);
		params.push_back (param3);
		return call (function, params);
	}
	
	
	Value Object::call (const std::string& function, const Value& param1,
	                                                 const Value& param2,
	                                                 const Value& param3,
	                                                 const Value& param4)
	{
		ValueList params;
		params.push_back (param1);
		params.push_back (param2);
		params.push_back (param3);
		params.push_back (param4);
		return call (function, params);
	}
	
	
	Value Object::call (const std::string& function, const Value& param1,
	                                                 const Value& param2,
	                                                 const Value& param3,
	                                                 const Value& param4,
	                                                 const Value& param5)
	{
		ValueList params;
		params.push_back (param1);
		params.push_back (param2);
		params.push_back (param3);
		params.push_back (param4);
		params.push_back (param5);
		return call (function, params);
	}

}
