#include <boost/test/included/unit_test_framework.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost::unit_test_framework;

test_suite *init_unit_test_suite(int argc, char *argv[]){
	return BOOST_TEST_SUITE("LibSanuki test");
}


