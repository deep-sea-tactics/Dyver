#include "test.h"

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

int main(int argc, char **argv)
{
    TEST_TEST.run();

    return 0;
}