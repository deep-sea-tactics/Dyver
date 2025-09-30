#ifndef H_TEST
#define H_TEST

#include <string>
#include <iostream>

inline void notification_test_passed(std::string id, uint64_t line)
{
    std::cout << "Test [" << id << "] passed without error." << std::endl;
}

inline void notification_test_failed(std::string id, uint64_t line, bool is_err)
{
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
        bool res = m_fn();

        if (res == true)
        {
            notification_test_passed(m_id, m_line);
        }
        else if (res == false)
        {
            notification_test_failed(m_id, m_line, false);
        }

        std::cout << "      Traceback to line " << int(m_line) << std::endl << std::endl;

        return res;
    }
};

#endif