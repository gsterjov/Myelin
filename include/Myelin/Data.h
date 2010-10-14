
#ifndef MYELIN_DATA_H_
#define MYELIN_DATA_H_


#include <Myelin/Type.h>


namespace Myelin
{

	/**
	 * Data storage interface.
	 */
	struct Data : RefCounter
	{
		virtual const Type* getType() const = 0;
		virtual const Type* getPointerType() const = 0;
		virtual void* getPointer() = 0;
	};
	
	
	
	/**
	 * Generic data storage.
	 */
	template <typename T>
	struct GenericData : Data
	{
		/**
		 * Value constructor.
		 */
		GenericData (T value) : mData (value) {}
		
		
		/**
		 * Get the held data.
		 */
		T& getData() { return mData; }
		
		/**
		 * Get the data type.
		 */
		const Type* getType() const { return TYPE(T); }
		
		/**
		 * Get the data type as a pointer.
		 */
		const Type* getPointerType() const { return TYPE(T*); }
		
		/**
		 * Get the data as a pointer.
		 */
		void* getPointer() { return &mData; }
		
		
	private:
		T mData;
	};

}


#endif /* MYELIN_DATA_H_ */
