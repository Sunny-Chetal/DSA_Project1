// #include <catch2/catch_test_macros.hpp>
// #include <iostream>
// #include "AVLTree.h"
//
// using namespace std;
//
// // Sunny Chetal UFID:62677665
// //5 Required Tests
// TEST_CASE("Unsuccessful Test", "[flag]"){
// 	AVLTree t;
// 	REQUIRE_FALSE(t.insert( "123456789", "Sunny Chetal"));
// 	REQUIRE_FALSE(t.insert("12345678" ,"Sunny Chetal2"));
// 	REQUIRE_FALSE(t.remove(87654321));
// 	REQUIRE_FALSE(t.search(87654321));
// 	REQUIRE_FALSE(t.search("Katara"));
// }
//
// TEST_CASE("Balanced Insert", "[flag]"){
// 	AVLTree LL;
// 	LL.insert("90000000", "Sunny Chetal");
// 	LL.insert("80000000", "Sunny C");
// 	LL.insert("70000000", "Sunny");
// 	vector<int> UFIDs = LL.printPreOrder();
// 	REQUIRE((UFIDs[0] == 80000000 && UFIDs[1] == 70000000 && UFIDs[2] == 90000000));
//
// 	AVLTree RR;
// 	RR.insert("10000000", "Evil Sunny");
// 	RR.insert("20000000", "Tired Sunny");
// 	RR.insert("30000000", "Happy Sunny");
// 	vector<int> UFIDs2 = RR.printPreOrder();
// 	REQUIRE((UFIDs2[0] == 20000000 && UFIDs2[1] == 10000000 && UFIDs2[2] == 30000000));
//
// 	AVLTree LR;
// 	LR.insert("16000000", "Not Sunny");
// 	LR.insert("14000000", "Or Sunny");
// 	LR.insert("15000000", "And Sunny");
// 	vector<int> UFIDs3 = LR.printPreOrder();
// 	REQUIRE((UFIDs3[0] == 15000000 && UFIDs3[1] == 14000000 && UFIDs3[2] == 16000000));
//
// 	AVLTree RL;
// 	RL.insert("21000000", "One Sunny");
// 	RL.insert("23000000", "Last Sunny");
// 	RL.insert("22000000", "Time Sunny");
// 	vector<int> UFIDs4 = RL.printPreOrder();
// 	REQUIRE((UFIDs4[0] == 22000000 && UFIDs4[1] == 21000000 && UFIDs4[2] == 23000000));
// }
//
//
// TEST_CASE("100 Inserts", "[flag]"){
// 	AVLTree random100;
// 	vector<int> expectedOutput, actualOutput;
// 	for (int i = 0; i < 100; i++) {
// 		int randomNumber = rand() % 90000000 + 10000000; //Searched for how to force rand() to produce between 10000000-99999999
// 		string ranNumber = to_string(randomNumber);
// 		if (count(expectedOutput.begin(), expectedOutput.end(), randomNumber) == 0) {
// 			expectedOutput.push_back(randomNumber);
// 			random100.insert(ranNumber, "Random Number");
// 		}
// 	}
// 	actualOutput = random100.printInOrder();
// 	REQUIRE(actualOutput.size() == expectedOutput.size());
// 	REQUIRE_FALSE(actualOutput == expectedOutput);
// 	sort(expectedOutput.begin(), expectedOutput.end());
// 	REQUIRE(expectedOutput == actualOutput);
//
// 	for (int i = 0; i < 10; i++) {
// 		int randomNumber = rand() % expectedOutput.size(); //Searched for how to force rand() to produce within size
// 		random100.remove(expectedOutput[randomNumber]);
// 		expectedOutput.erase(expectedOutput.begin() + randomNumber);
// 	}
// 	actualOutput = random100.printInOrder();
// 	REQUIRE(actualOutput.size() == expectedOutput.size());
// 	sort(expectedOutput.begin(), expectedOutput.end());
// 	REQUIRE(expectedOutput == actualOutput);
// }
//
// TEST_CASE("Removal Tests", "[flag]"){
// 	//No Child Test
// 	AVLTree noChild;
// 	noChild.insert("50000000", "One");
// 	noChild.insert("30000000", "Two");
// 	noChild.insert("20000000", "Three");
// 	noChild.insert("40000000", "Four");
// 	noChild.insert("70000000", "Five");
// 	noChild.insert("60000000", "Six");
// 	noChild.insert("80000000", "Seven");;
// 	REQUIRE(noChild.remove(20000000));
// 	vector<int> first = noChild.printInOrder();
// 	vector<int> test = {30000000, 40000000, 50000000, 60000000, 70000000, 80000000};
// 	REQUIRE(first == test);
//
// 	//One Child Test
// 	AVLTree OneChild;
// 	OneChild.insert("50000000", "One");
// 	OneChild.insert("30000000", "Two");
// 	OneChild.insert("20000000", "Three");
// 	OneChild.insert("40000000", "Four");
// 	OneChild.insert("70000000", "Five");
// 	OneChild.insert("60000000", "Six");
// 	REQUIRE(OneChild.remove(70000000));
// 	vector<int> second = OneChild.printInOrder();
// 	vector<int> test2 = {20000000, 30000000, 40000000, 50000000, 60000000,};
// 	REQUIRE(second == test2);
//
// 	//Two Children Test
// 	AVLTree TwoChild;
// 	TwoChild.insert("50000000", "One");
// 	TwoChild.insert("30000000", "Two");
// 	TwoChild.insert("20000000", "Three");
// 	TwoChild.insert("40000000", "Four");
// 	TwoChild.insert("70000000", "Five");
// 	TwoChild.insert("60000000", "Six");
// 	TwoChild.insert("80000000", "Seven");;
// 	REQUIRE(TwoChild.remove(30000000));
// 	vector<int> third = TwoChild.printInOrder();
// 	vector<int> test3 = {20000000, 40000000, 50000000, 60000000, 70000000, 80000000};
// 	REQUIRE(third == test3);
// }
//
// TEST_CASE("Edge Cases", "[flag]") {
// 	//Duplicate IDs
// 	AVLTree t;
// 	t.insert("00000000", "One");
// 	REQUIRE_FALSE(t.insert("00000000", "Two"));
//
// 	//Print on an empty tree
// 	AVLTree t2;
// 	vector<int> first = t2.printInOrder();
// 	REQUIRE(first.size() == 0);
//
// 	//RemoveInOrder with an invalid N
// 	REQUIRE_FALSE(t.removeInOrder(-1));
// }
//
//
// //Extra Personal Tests
// TEST_CASE("Search Test", "[flag]"){
// 	AVLTree searchTest;
// 	searchTest.insert("90000000", "Sunny Chetal");
// 	searchTest.insert("80000000", "Sunny Chetal");
// 	searchTest.insert("70000000", "Sunny Chetal");
// 	REQUIRE(searchTest.search(90000000) == true);
// 	REQUIRE(searchTest.search("Sunny Chetal") == true);
// }
//
// TEST_CASE("PostOrder Test", "[flag]"){
// 	AVLTree postOrderTest;
// 	postOrderTest.insert("90000000", "Sunny Nine");
// 	postOrderTest.insert("80000000", "Sunny Eight");
// 	postOrderTest.insert("70000000", "Sunny Seven");
// 	vector<int> postOrder = postOrderTest.printPostOrder();
// 	REQUIRE((postOrder[0] == 70000000 && postOrder[1] == 90000000 && postOrder[2] == 80000000));
// }