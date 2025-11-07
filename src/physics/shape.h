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
    /**
     * @brief Euler moment of inertia for X
     * 
     */
    virtual auto I_x() -> double;
    
    /**
     * @brief Euler moment of inertia for Y
     * 
     */
    virtual auto I_y() -> double;

    /**
     * @brief Euler moment of inertia for Z
     * 
     */
    virtual auto I_z() -> double;

    auto get_mass() -> double&
    {
        return m_mass;
    }
protected:

    double m_mass;
};

constexpr double ONE_TWELTH = (1.0/12.0);

class rectprism_t : public shape_t
{
public:
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
private:

    auto I(double x, double y) -> double
    {
        //I_center,L = 1/12 * M * (W^2+H^2)
        return ONE_TWELTH * m_mass * (utils::square(x) + utils::square(y));
    }

    double m_w{0.0};
    double m_h{0.0};
    double m_l{0.0};
};

#endif