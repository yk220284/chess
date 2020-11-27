#include <iostream>
#include "board.hpp"
#include "util.hpp"
using namespace std;

int main()
{

    Board bd(filenames::DEFALT_CONFIG);
    Board bd1(filenames::ONLY_KING);
    cout << bd;
    cout << bd1;
    // cout << bd1;
}
