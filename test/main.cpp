
#include <iostream>
#include <gmock/gmock.h>


int main (int argc, char** argv)
{
	std::cout << "Running Myelin Tests" << std::endl;
	
	/* start tests */
	testing::InitGoogleMock (&argc, argv);
	return RUN_ALL_TESTS ();
}

