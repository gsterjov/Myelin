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

#include "List.h"






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
Myelin::List *
myelin_list_new ()
{
	return new Myelin::List ();
}


Myelin::List *
myelin_list_ref (Myelin::List *list)
{
	list->ref();
	return list;
}


void
myelin_list_unref (Myelin::List *list)
{
	list->unref();
	if (list->count() == 0) delete list;
}




uint
myelin_list_size (const Myelin::List *list)
{
	return list->size();
}


Myelin::Value *
myelin_list_index (const Myelin::List *list, uint index)
{
	Myelin::Value* ret = new Myelin::Value (list->at (index));
	
	/* throw away ownership */
	ret->unref();
	return ret;
}



void
myelin_list_append (Myelin::List *list, Myelin::Value *value)
{
	list->push_back (*value);
}

