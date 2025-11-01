#ifndef H_UTILS
#define H_UTILS

#include <iostream>

namespace utils
{
    enum MSG_TYPE
    {
        INFO,
        WARN
    };

    
    static void log(MSG_TYPE type, std::string s)
    {
        switch (type)
        {
            case(MSG_TYPE::WARN):
            {
                std::cout << "\033[93m[warning] ";
                break;
            }

            case (MSG_TYPE::INFO):
            {
                std::cout << "\033[0m[info] ";
                break;
            }
        }

        std::cout << s;

        std::cout << "\033[0m\n" << std::flush;
    }

}

#endif