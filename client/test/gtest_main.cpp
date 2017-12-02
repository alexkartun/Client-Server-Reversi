/*
 * gtest_main.cpp
 */
#include "gtest/gtest.h"

GTEST_API_ int main3(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}




