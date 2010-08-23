
#ifndef MYELIN_LIST_H_
#define MYELIN_LIST_H_


#include <vector>


namespace Myelin
{

	class List
	{
	public:
		/**
		 * Constructor.
		 */
		template <typename T>
		List (std::vector<T> list) : mData(new List<T>()) {}
		
		
		
	private:
		struct ListData;
		
		ListData* mData;
		
		
		template <typename T>
		struct ListData
		{
			ListData (std::vector<T> list) : mList(list) {}
			
			std::vector<T> mList;
		};
	};

}



/* C api */
extern "C"
{

	void myelin_list_size (Myelin::List *list);

}



#endif /* MYELIN_LIST_H_ */
