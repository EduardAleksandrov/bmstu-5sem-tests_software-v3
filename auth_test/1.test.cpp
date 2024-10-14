/*

*/


#define BOOST_TEST_MODULE MyTestModule
#include <iostream>
#include <gmock/gmock.h>
#include "boost/test/included/unit_test.hpp"

#include "./include/5.five.cpp"

BOOST_AUTO_TEST_SUITE(TestSuite_auth)


BOOST_AUTO_TEST_CASE(test_case_1_1_exception)
{
    // Arrange
    std::string login_player, pass_player;

    // Act 
    login_player = "";
    pass_player = "232";
     
    // Assert
    BOOST_CHECK_THROW(authorization(login_player, pass_player, 1), Except_log);
    BOOST_CHECK_THROW(authorization(login_player, pass_player, 2), Except_log);

    // BOOST_CHECK_NO_THROW(authorization("11", "222", 1));

    std::cout << "test1" << std::endl;
}

BOOST_AUTO_TEST_CASE(test_case_1_2_exception)
{
    // Arrange
    std::string login_player, pass_player;

    // Act 
    login_player = "111";
    pass_player = "";
     
    // Assert
    BOOST_CHECK_THROW(authorization(login_player, pass_player, 1), Except_pass);
    BOOST_CHECK_THROW(authorization(login_player, pass_player, 2), Except_pass);

    std::cout << "test2" << std::endl;
}

BOOST_AUTO_TEST_CASE(test_case_1_3_exception)
{
    // Arrange
    std::string login_player, pass_player;

    // Act 
    login_player = "";
    pass_player = "";
     
    // Assert
    BOOST_CHECK_THROW(authorization(login_player, pass_player, 1), Except_log_pass_empty);
    BOOST_CHECK_THROW(authorization(login_player, pass_player, 2), Except_log_pass_empty);

    std::cout << "test3" << std::endl;
}

BOOST_AUTO_TEST_CASE(test_case_1_4_exception)
{
    // Arrange
    std::string login_player, pass_player;

    // Act 
    login_player = "";
    pass_player = "";
     
    // Assert
    BOOST_CHECK_THROW(authorization(login_player, pass_player, 3), Except_not_correct_player);

    std::cout << "test4" << std::endl;
}

BOOST_AUTO_TEST_CASE(test_case_1_5_exception)
{
    // Arrange
    std::string login_player, pass_player;

    // Act 
    login_player = "1";
    pass_player = "2";
     
    // Assert
    BOOST_CHECK_THROW(authorization(login_player, pass_player, 1), Except_log_pass);
    BOOST_CHECK_THROW(authorization(login_player, pass_player, 2), Except_log_pass);

    std::cout << "test5" << std::endl;
}

BOOST_AUTO_TEST_CASE(test_case_1_6_exception)
{
    // Arrange
    std::string login_player_1, pass_player_1;
    std::string login_player_2, pass_player_2;

    // Act 
    login_player_1 = "111";
    pass_player_1 = "222";
    login_player_2 = "333";
    pass_player_2 = "444";
     
    // Assert
    BOOST_CHECK_NO_THROW(authorization(login_player_1, pass_player_1, 1));
    BOOST_CHECK_NO_THROW(authorization(login_player_2, pass_player_2, 2));

    std::cout << "test6" << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()