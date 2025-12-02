/**
 * @brief Mass distribution objects
 */

#ifndef H_SHAPE
#define H_SHAPE

#include <cmath>

#include <Eigen/Dense>

#include "utils.h"

class shape_t
{
public:
    shape_t(double mass, double I_x, double I_y, double I_z)
    {
        m_mass = mass;
        m_I_x = I_x;
        m_I_y = I_y;
        m_I_z = I_z;
    }

    shape_t() = default;
protected:
    double m_I_x{0.0};
    double m_I_y{0.0};
    double m_I_z{0.0};

    double m_mass{0.0};
};

constexpr double ONE_TWELTH = (1.0/12.0);

inline auto I_rectprism(const double &mass, const double x, const double y) -> double
{
    //I_center,L = 1/12 * M * (W^2+H^2)
    return ONE_TWELTH * mass * (utils::square(x) + utils::square(y));
}
/*
    auto I_x() -> double override
    {
        return I(m_w, m_h);
    }

    auto I_y() -> double override
    {
        return I(m_l, m_w);
    }

    auto I_z() -> double override
    {
        return I(m_l, m_h);
    }
*/
inline auto rectprism_factory(const double mass, const double w, const double h, const double l) -> shape_t
{
    return shape_t(
        mass,
        I_rectprism(mass, w ,h),
        I_rectprism(mass, l, w),
        I_rectprism(mass, l, h)
    );
};

#endif