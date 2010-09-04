
#ifndef MYELIN_TYPE_INFO_H_
#define MYELIN_TYPE_INFO_H_


#include <Myelin/Type.h>


namespace Myelin
{
	/**
	 * Convenience macro to get type info.
	 */
	#define TYPE_INFO(type) Types::get_type_info<type>()
	
	
	/**
	 * A list of type infos.
	 */
	class TypeInfo; typedef std::vector<const TypeInfo*> TypeInfoList;
	
	
	
	/**
	 * Information on a specific type.
	 */
	struct MYELIN_API TypeInfo
	{
		virtual const Type* getType() const = 0;
		virtual const std::string getName() const = 0;
		
		virtual bool isConstant()  const = 0;
		virtual bool isReference() const = 0;
		virtual bool isPointer()   const = 0;
	};
	
	
	
	
	namespace Types
	{
		/**
		 * Generic no qualifier type.
		 */
		template <typename T>
		struct GenericTypeInfo : TypeInfo
		{
			GenericTypeInfo () { if (!get_type<T>()) register_type<T>(); }
			
			const Type* getType() const { return get_type<T>(); }
			const std::string getName() const { return get_type<T>()->getName(); }
			
			bool isConstant()  const { return false; }
			bool isReference() const { return false; }
			bool isPointer()   const { return false; }
		};
		
		
		/**
		 * Generic pointer type.
		 */
		template <typename T>
		struct GenericTypeInfo<T*> : TypeInfo
		{
			GenericTypeInfo () { if (!get_type<T>()) register_type<T>(); }
			
			const Type* getType() const { return get_type<T>(); }
			const std::string getName() const { return get_type<T>()->getName() + "*"; }
			
			bool isConstant()  const { return false; }
			bool isReference() const { return false; }
			bool isPointer()   const { return true; }
		};
		
		
		
		/**
		 * Get type information.
		 */
		template <typename T>
		const TypeInfo* get_type_info()
		{
			/* store into a static variable since all instance are the same */
			static TypeInfo* info = new GenericTypeInfo<T>();
			return info;
		}
	
	}
}





/* C api */
extern "C"
{

	MYELIN_API const Myelin::Type *type_info_get_type (const Myelin::TypeInfo *info);
	MYELIN_API const char *type_info_get_name (const Myelin::TypeInfo *info);
	
	MYELIN_API bool type_info_is_constant  (const Myelin::TypeInfo *info);
	MYELIN_API bool type_info_is_reference (const Myelin::TypeInfo *info);
	MYELIN_API bool type_info_is_pointer   (const Myelin::TypeInfo *info);

}



#endif /* MYELIN_TYPE_INFO_H_ */