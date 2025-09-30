#ifndef H_TEST
#define H_TEST

#include <string>
#include <iostream>
#include <exception>

inline void notification_test_passed(std::string id, uint64_t line)
{
    std::cout << "\033[32m Test [" << id << "] passed without error." << std::endl;
}

inline void notification_test_failed(std::string id, uint64_t line, bool is_err)
{
    if (is_err == true)
    {
        std::cout << "\033[31m";
    }
    else if (is_err == false)
    {
        std::cout << "\033[33m";
    }

    std::cout << "Test [" << id << "] failed";

    if (is_err == false)
    {
        std::cout << " without error." << std::endl;
    }
    else if (is_err == true)
    {
        std::cout << " and errored." << std::endl;
    }
}

struct test_t
{
    bool (*m_fn)();
    std::string m_id;
    uint64_t m_line;

    test_t(std::string id, uint64_t line, bool (*fn)())
    {
        m_fn = fn;
        m_id = id;
        m_line = line;
    }

    bool run()
    {
        bool res = false;
        try
        {
            res = m_fn();

            if (res == true)
            {
                notification_test_passed(m_id, m_line);
            }
            else if (res == false)
            {
                notification_test_failed(m_id, m_line, false);
            }
        }
        catch(const std::exception &e)
        {
            notification_test_failed(m_id, m_line, true);
            std::cout << e.what();
        }
        catch(const int &code)
        {
            notification_test_failed(m_id, m_line, true);
            std::cout << "Error code: " << code;
        }

        std::cout << "      Traceback to line " << int(m_line) << std::endl << std::endl;

        std::cout << "\033[39m";

        return res;
    }
};

#endif