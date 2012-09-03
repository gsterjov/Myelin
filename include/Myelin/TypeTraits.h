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

#ifndef MYELIN_TYPE_TRAITS_H_
#define MYELIN_TYPE_TRAITS_H_


namespace Myelin
{

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

}


#endif /* MYELIN_TYPE_TRAITS_H_ */
