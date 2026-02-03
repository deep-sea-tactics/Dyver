#ifndef H_TEST
#define H_TEST

#include <cstdint>
#include <string>
#include <iostream>
#include <exception>

/**
 * @brief Whether or not `lhs` is within `tolerance` of `rhs`
 *
 * @param lhs The value to compare against `rhs`
 * @param rhs The value being compared against
 * @param tolerance The range that determines whether or not the values are "approximately" equal.
 */
inline bool approx_eq(double lhs, double rhs, double tolerance)
{
	double diff = (rhs - lhs);

	if (std::abs(diff) > tolerance)
	{
		return false;
	}

	return true;
}

/**
 * @brief Which test passed, and where.
 *
 * @param id The identifier of the test.
 * @param line The traceback line.
 *
 * @see test_t
 */
inline void notification_test_passed(std::string id) // Yes, it's inline IO.
{
	std::cout << "\033[32mTest [" << id << "] passed without error." << std::endl;
}

/**
 * @brief Which test failed, and where.
 *
 * @param id The identifier of the test.
 * @param line The traceback line.
 * @param is_err Whether or not to display that the test errored.
 *
 * @see test_t
 */
inline void notification_test_failed(std::string id, bool is_err) // Yes, it's inline IO.
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

/**
 * @brief A test object which contains various utilities for unit testing
 */
struct test_t
{
	bool (*m_fn)(){nullptr};
	std::string m_id{""};
	uint64_t m_line{0};

	/**
	 * @brief Construct a new test object
	 */
	test_t(std::string id, uint64_t line, bool (*fn)())
	{
		m_fn = fn;
		m_id = id;
		m_line = line;
	}

	/**
	 * Run the test and report failure/success in the standard output
	 */
	bool run(int *passed_tests_counter = nullptr, int *failed_tests_counter = nullptr) const
	{
		bool res = false;
		try
		{
			res = m_fn();

			if (res == true)
			{
				notification_test_passed(m_id);

				if (passed_tests_counter != nullptr)
				{
					++*passed_tests_counter;
				}
			}
			else if (res == false)
			{
				notification_test_failed(m_id, false);

				if (failed_tests_counter != nullptr)
				{
					++*failed_tests_counter;
				}
			}
		}
		catch (const std::exception &e)
		{
			notification_test_failed(m_id, true);
			std::cout << e.what() << std::endl;

			if (failed_tests_counter != nullptr)
			{
				++*failed_tests_counter;
			}
		}
		catch (const int &code)
		{
			notification_test_failed(m_id, true);
			std::cout << "Error code: " << code << std::endl;

			if (failed_tests_counter != nullptr)
			{
				++*failed_tests_counter;
			}
		}

		std::cout << "      Traceback to line " << int(m_line) << std::endl << std::endl;

		std::cout << "\033[39m";

		return res;
	}
};

#endif