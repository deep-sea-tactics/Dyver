#include <iostream>
#include "test.h"
#include <exception>
#include <vector>
#include <map>
using namespace std;


test_t TEST_TEST = test_t("test_test", __LINE__, []()
{
    if (1 + 1 == 2)
    {
        return true;
    }
    else
    {
        return false;
    }
});

vector<string> CONTINENTS_AND_COUNTRIES(string continent) {
    map<string, vector<string>> continents_and_countries =
    {
        {"North America", {"United States of America", "Canada", "Mexico"}},
        {"South America", {"Brazil", "Chile", "Peru"}},
        {"Europe", {"United Kingdom", "France", "Germany"}},
    };
    return continents_and_countries[continent];
}

int main(int argc, char **argv)
{
    TEST_TEST.run();

    vector<string> countries = CONTINENTS_AND_COUNTRIES("Europe");
    for (string country : countries) {
        cout << country << ", ";
    }

    return 0;
}