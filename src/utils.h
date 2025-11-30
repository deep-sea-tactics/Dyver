#ifndef H_UTILS
#define H_UTILS

#include <iostream>

namespace utils
{
    /**
     * @brief Convert metric "milliU" to U
     * 
     */
    constexpr double MILLIU_T_U = (1.0e-3);

    /**
     * @brief Convert metric centiU to U
     * 
     */
    constexpr double CENTIU_T_U = (1.0e-2);

    /**
     * @brief Convert metric nanoU to U
     * 
     */
    constexpr double NANOU_T_U = (1.0e-9);

    /**
     * @brief Convert metric kiloU to U
     * 
     */
    constexpr double KILOU_T_U = (1.0e3); 

    enum MSG_TYPE
    {
        INFO,
        WARN
    };

    /**
     * @brief Returns the square of n
     * 
     * @param n The number to take the square of
     * @return double Representing the result of the square operation
     */
    inline auto square(const double n) -> double
    {
        return n * n;
    }
    
    /**
     * @brief Log a nicely formatted string in the standard out
     * 
     * @param type The type of the message (e.g. MSG_TYPE::WARN)
     * @param s The string message to output
     */
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