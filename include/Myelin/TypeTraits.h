
#ifndef MYELIN_TYPE_TRAITS_H_
#define MYELIN_TYPE_TRAITS_H_


namespace Myelin {
namespace Types {

	
	template <typename T> struct remove_constant  { typedef T type; };
	template <typename T> struct remove_reference { typedef T type; };
	template <typename T> struct remove_pointer   { typedef T type; };
	template <typename T> struct remove_volatile  { typedef T type; };
	
	
	template <typename T> struct remove_constant  <const T>    { typedef T type; };
	template <typename T> struct remove_constant  <const T*>   { typedef T* type; };
	template <typename T> struct remove_constant  <const T&>   { typedef T& type; };
	template <typename T> struct remove_reference <T&>         { typedef T type; };
	template <typename T> struct remove_pointer   <T*>         { typedef T type; };
	template <typename T> struct remove_volatile  <volatile T> { typedef T type; };
	
	
	template <typename T> struct remove_qualifiers
	{
		typedef typename remove_constant<
		        typename remove_reference<
		        typename remove_pointer<
		        typename remove_volatile<T>::type>::type>::type>::type type;
	};
	
	
	
	template <typename T> struct add_constant  { typedef const T type; };
	template <typename T> struct add_reference { typedef T& type; };
	template <typename T> struct add_pointer   { typedef T* type; };
	template <typename T> struct add_volatile  { typedef volatile T type; };
	
	
	
	template <typename T> struct is_constant  { enum { value = false }; };
	template <typename T> struct is_reference { enum { value = false }; };
	template <typename T> struct is_pointer   { enum { value = false }; };
	template <typename T> struct is_volatile  { enum { value = false }; };
	
	
	template <typename T> struct is_constant <const T>           { enum { value = true }; };
	template <typename T> struct is_constant <const T*>          { enum { value = true }; };
	template <typename T> struct is_constant <const T&>          { enum { value = true }; };
	template <typename T> struct is_constant <const volatile T>  { enum { value = true }; };
	template <typename T> struct is_constant <const volatile T*> { enum { value = true }; };
	template <typename T> struct is_constant <const volatile T&> { enum { value = true }; };
	
	
	template <typename T> struct is_volatile <volatile T>        { enum { value = true }; };
	template <typename T> struct is_volatile <volatile T*>       { enum { value = true }; };
	template <typename T> struct is_volatile <volatile T&>       { enum { value = true }; };
	template <typename T> struct is_volatile <const volatile T>  { enum { value = true }; };
	template <typename T> struct is_volatile <const volatile T*> { enum { value = true }; };
	template <typename T> struct is_volatile <const volatile T&> { enum { value = true }; };
	
	
	template <typename T> struct is_reference <T&>                { enum { value = true }; };
	template <typename T> struct is_reference <const T&>          { enum { value = true }; };
	template <typename T> struct is_reference <volatile T&>       { enum { value = true }; };
	template <typename T> struct is_reference <const volatile T&> { enum { value = true }; };
	
	
	template <typename T> struct is_pointer <T*>                { enum { value = true }; };
	template <typename T> struct is_pointer <const T*>          { enum { value = true }; };
	template <typename T> struct is_pointer <volatile T*>       { enum { value = true }; };
	template <typename T> struct is_pointer <const volatile T*> { enum { value = true }; };
	
	
	
	template <typename T> struct is_void { enum { value = false }; };
	template <> struct is_void <void> { enum { value = true }; };

}}


#endif /* MYELIN_TYPE_TRAITS_H_ */
