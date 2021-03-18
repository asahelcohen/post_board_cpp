#include "Board.hpp"
#include "doctest.h"
#include <string>
#include <iostream>
using namespace ariel;

Board messageBoard;

TEST_CASE("empty message board")
{
    //horizontal
    CHECK(messageBoard.read(1, 0, Direction::Horizontal, 0) == "");
    CHECK(messageBoard.read(0, 0, Direction::Horizontal, 1) == "_");
    CHECK(messageBoard.read(2, 3, Direction::Horizontal, 2) == "__");
    CHECK(messageBoard.read(10, 11, Direction::Horizontal, 3) == "___");
    CHECK(messageBoard.read(0, 2, Direction::Horizontal, 4) == "____");
    CHECK(messageBoard.read(4, 4, Direction::Horizontal, 5) == "_____");

    //vertical
    CHECK(messageBoard.read(1, 0, Direction::Vertical, 0) == "");
    CHECK(messageBoard.read(0, 0, Direction::Vertical, 1) == "_");
    CHECK(messageBoard.read(2, 3, Direction::Vertical, 2) == "__");
    CHECK(messageBoard.read(10, 11, Direction::Vertical, 3) == "___");
    CHECK(messageBoard.read(0, 2, Direction::Vertical, 4) == "____");
    CHECK(messageBoard.read(4, 4, Direction::Vertical, 5) == "_____");

    //random
    unsigned int x;
    unsigned int y;
    std::string s = "";
    for (int i = 0; i < 10; i++)
    {
        unsigned int length = (unsigned int) i;
        unsigned int x = (unsigned int) std::rand();
        unsigned int y = (unsigned int) std::rand();
        CHECK(messageBoard.read(x, y, Direction::Vertical, length) == s);
        CHECK(messageBoard.read(y, x, Direction::Horizontal, length) == s);
        s += "_";
    }
}

TEST_CASE("post basic")
{
    //horizontal
    CHECK_NOTHROW(messageBoard.post(0, 0, Direction::Horizontal, "message"));
    CHECK_NOTHROW(messageBoard.post(0, 8, Direction::Horizontal, "board"));
    CHECK_NOTHROW(messageBoard.post(3, 0, Direction::Horizontal, "facebook"));
    CHECK_NOTHROW(messageBoard.post(6, 0, Direction::Horizontal, "asahel"));

    //vertical
    CHECK_NOTHROW(messageBoard.post(0, 8, Direction::Vertical, "bitcoin"));
    CHECK_NOTHROW(messageBoard.post(0, 4, Direction::Vertical, "abba"));
    CHECK_NOTHROW(messageBoard.post(2, 10, Direction::Vertical, "project"));
    CHECK_NOTHROW(messageBoard.post(8, 8, Direction::Vertical, "hi"));
}

TEST_CASE("read basic")
{
    CHECK(messageBoard.read(1, 0, Direction::Horizontal, 0) == "");
    CHECK(messageBoard.read(0, 0, Direction::Horizontal, 1) == "m");
    CHECK(messageBoard.read(2, 3, Direction::Horizontal, 2) == "eb");
    CHECK(messageBoard.read(0, 2, Direction::Horizontal, 4) == "ssag");
    CHECK(messageBoard.read(4, 7, Direction::Horizontal, 5) == "_o_o_");
    CHECK(messageBoard.read(0, 0, Direction::Horizontal, 7) == "message");
    CHECK(messageBoard.read(0, 0, Direction::Horizontal, 13) == "message_board");

    //vertical
    CHECK(messageBoard.read(1, 0, Direction::Vertical, 0) == "");
    CHECK(messageBoard.read(0, 0, Direction::Vertical, 1) == "m");
    CHECK(messageBoard.read(2, 3, Direction::Vertical, 2) == "e_");
    CHECK(messageBoard.read(1, 8, Direction::Vertical, 4) == "itco");
    CHECK(messageBoard.read(0, 10, Direction::Vertical, 5) == "a_pro");
    CHECK(messageBoard.read(0, 8, Direction::Vertical, 7) == "bitcoin");
    CHECK(messageBoard.read(0, 8, Direction::Vertical, 10) == "bitcoin_hi");
}

TEST_CASE("post running over older posts")
{
    //horizontal
    CHECK_NOTHROW(messageBoard.post(0, 9, Direction::Horizontal, "read"));
    CHECK_NOTHROW(messageBoard.post(8, 7, Direction::Horizontal, "play"));
    CHECK_NOTHROW(messageBoard.post(6, 1, Direction::Horizontal, "build"));

    //vertical
    CHECK_NOTHROW(messageBoard.post(5, 0, Direction::Vertical, "run"));
    CHECK_NOTHROW(messageBoard.post(0, 3, Direction::Vertical, "find"));
    CHECK_NOTHROW(messageBoard.post(0, 8, Direction::Vertical, "rabbit"));
}

TEST_CASE("read after running over older posts")
{
    //horizontal
    CHECK(messageBoard.read(0, 3, Direction::Horizontal, 1) == "f");
    CHECK(messageBoard.read(2, 3, Direction::Horizontal, 2) == "nb");
    CHECK(messageBoard.read(0, 2, Direction::Horizontal, 4) == "sfag");
    CHECK(messageBoard.read(4, 7, Direction::Horizontal, 5) == "_i_o_");
    CHECK(messageBoard.read(0, 0, Direction::Horizontal, 7) == "masfage");
    CHECK(messageBoard.read(0, 0, Direction::Horizontal, 13) == "mesfage_rread");

    //vertical
    CHECK(messageBoard.read(0, 3, Direction::Vertical, 1) == "f");
    CHECK(messageBoard.read(2, 3, Direction::Vertical, 2) == "nd");
    CHECK(messageBoard.read(1, 8, Direction::Vertical, 4) == "abbi");
    CHECK(messageBoard.read(0, 10, Direction::Vertical, 5) == "e_pro");
    CHECK(messageBoard.read(0, 8, Direction::Vertical, 7) == "rabbitn");
    CHECK(messageBoard.read(0, 8, Direction::Vertical, 10) == "rabbitn_li");
}

TEST_CASE("post BIG letters,other symbols and numbers")
{
    //horizontal
    CHECK_NOTHROW(messageBoard.post(10, 9, Direction::Horizontal, "WHAT"));
    CHECK_NOTHROW(messageBoard.post(13, 7, Direction::Horizontal, "WOrk"));
    CHECK_NOTHROW(messageBoard.post(16, 1, Direction::Horizontal, "#@"));
    CHECK_NOTHROW(messageBoard.post(14, 1, Direction::Horizontal, "Wh$%1"));
    CHECK_NOTHROW(messageBoard.post(12, 0, Direction::Horizontal, "123"));


    //vertical
    CHECK_NOTHROW(messageBoard.post(10, 5, Direction::Vertical, "WHat"));
    CHECK_NOTHROW(messageBoard.post(8, 1, Direction::Vertical, "WORK"));
    CHECK_NOTHROW(messageBoard.post(8, 0, Direction::Vertical, "&*"));
    CHECK_NOTHROW(messageBoard.post(6, 6, Direction::Vertical, "W()1"));
    CHECK_NOTHROW(messageBoard.post(9, 7, Direction::Vertical, "Wh$%1"));
}

TEST_CASE("read BIG letters, other symbols and numbers")
{
    //horizontal
    CHECK(messageBoard.read(13, 5, Direction::Horizontal, 5) == "t_WOrk");
    CHECK(messageBoard.read(14, 1, Direction::Horizontal, 5) == "Wh$%1");
    CHECK(messageBoard.read(8, 0, Direction::Horizontal, 9) == "*W____1Wi");

    //vertical
    CHECK(messageBoard.read(8, 7, Direction::Vertical, 8) == "pWh$%1W_");
    CHECK(messageBoard.read(16, 2, Direction::Vertical, 7) == "@_______");
    CHECK(messageBoard.read(0, 1, Direction::Vertical, 18) == "a_a___b__WORK2_W_#_");
}