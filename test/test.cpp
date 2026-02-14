#include <catch2/catch_test_macros.hpp>
#include <iostream>
 #include "AVLTree.h"

using namespace std;

// the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.
TEST_CASE("Unsuccessful Test", "[flag]"){
	AVLTree t;
	REQUIRE(t.insert(123456789, "Sunny Chetal") == false);
	REQUIRE(t.insert(12345678 ,"Sunny Chetal2") == false);
	REQUIRE(t.remove(87654321) == false);
	REQUIRE(t.search(87654321) == false);
	REQUIRE(t.search("Katara") == false);
}

TEST_CASE("Balanced Insert", "[flag]"){
	AVLTree LL;
	LL.insert(90000000, "Sunny Chetal");
	LL.insert(80000000, "Sunny C");
	LL.insert(70000000, "Sunny");
	vector<int> UFIDs = LL.printInOrder();
	REQUIRE((UFIDs[0] == 70000000 && UFIDs[1] == 80000000 && UFIDs[2] == 90000000));

	AVLTree RR;
	RR.insert(10000000, "Evil Sunny");
	RR.insert(20000000, "Tired Sunny");
	RR.insert(30000000, "Happy Sunny");
	vector<int> UFIDs2 = RR.printInOrder();
	REQUIRE((UFIDs2[0] == 10000000 && UFIDs2[1] == 20000000 && UFIDs2[2] == 30000000));

	AVLTree LR;
	LR.insert(16000000, "Not Sunny");
	LR.insert(14000000, "Or Sunny");
	LR.insert(15000000, "And Sunny");
	vector<int> UFIDs3 = LR.printInOrder();
	REQUIRE((UFIDs3[0] == 14000000 && UFIDs3[1] == 15000000 && UFIDs3[2] == 16000000));

	AVLTree RL;
	RL.insert(21000000, "One Sunny");
	RL.insert(23000000, "Last Sunny");
	RL.insert(22000000, "Time Sunny");
	vector<int> UFIDs4 = RL.printInOrder();
	REQUIRE((UFIDs4[0] == 21000000 && UFIDs4[1] == 22000000 && UFIDs4[2] == 23000000));
}


TEST_CASE("100 Inserts", "[flag]"){
	AVLTree random100;
	vector<int> expectedOutput, actualOutput;
	for (int i = 0; i < 100; i++) {
		int randomNumber = rand() % 90000000 + 10000000; //Searched for how to force rand() to produce between 10000000-99999999
		if (count(expectedOutput.begin(), expectedOutput.end(), randomNumber) == 0) {
			expectedOutput.push_back(randomNumber);
			random100.insert(randomNumber, "Random Number");
		}
	}
	actualOutput = random100.printInOrder();
	REQUIRE(actualOutput.size() == expectedOutput.size());
	REQUIRE_FALSE(actualOutput == expectedOutput);
	sort(expectedOutput.begin(), expectedOutput.end());
	REQUIRE(expectedOutput == actualOutput);

	for (int i = 0; i < 10; i++) {
		int randomNumber = rand() % 100; //Searched for how to force rand() to produce between 0-99
		expectedOutput.erase(expectedOutput.begin() + randomNumber);
		random100.remove(expectedOutput[randomNumber]);
	}
	actualOutput = random100.printInOrder();
	REQUIRE(actualOutput.size() == expectedOutput.size());
	REQUIRE_FALSE(actualOutput == expectedOutput);
	sort(expectedOutput.begin(), expectedOutput.end());
	REQUIRE(expectedOutput == actualOutput);
}
