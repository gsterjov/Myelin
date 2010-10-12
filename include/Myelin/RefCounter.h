
#ifndef MYELIN_REF_COUNTER_H_
#define MYELIN_REF_COUNTER_H_


#include <Myelin/Config.h>


namespace Myelin
{

	/**
	 * Reference counting implementation.
	 */
	class MYELIN_API RefCounter
	{
	public:
		/**
		 * Constructor.
		 */
		RefCounter() : mCounter(0) {}
		
		/**
		 * Destructor.
		 */
		virtual ~RefCounter() {}
		
		
		/**
		 * Reference counter.
		 */
		int count() { return mCounter; }
		
		/**
		 * Increment reference counter.
		 */
		void ref() { ++mCounter; }
		
		/**
		 * Decrement reference counter.
		 */
		void unref() { --mCounter; }
		
		
	private:
		int mCounter;
	};

}


#endif /* MYELIN_REF_COUNTER_H_ */
