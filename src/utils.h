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
inline auto square(const double n) -> double { return n * n; }

/**
 * @brief Log a nicely formatted string in the standard out
 *
 * @param type The type of the message (e.g. MSG_TYPE::WARN)
 * @param s The string message to output
 */
static void log(std::string s, MSG_TYPE type = MSG_TYPE::INFO)
{
	switch (type)
	{
	case (MSG_TYPE::WARN):
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

struct linear_percentage_t
{
	double m_max;
	double m_min;

	linear_percentage_t(const double min, const double max)
	{
		m_max = max;
		m_min = min;
	}

	auto to_percentage(const double v) -> double
	{
		double diff = (m_max - m_min);
		double inbetween = (v - m_min);

		return (inbetween / diff);
	}

	auto to_value(const double p) -> double
	{
		double diff = (m_max - m_min);
		return m_min + (p * diff);
	}
};
} // namespace utils

#endif