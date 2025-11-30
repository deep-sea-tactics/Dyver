#ifndef H_BODY
#define H_BODY

#include <Eigen/Dense>
#include "shape.h"

template <typename S>
class body_t
{
public:
    /**
     * @brief Construct a new body object
     * 
     * @param pos The position of the body
     * @param rot The rotation of the body
     */
    body_t(Eigen::Vector3d pos, Eigen::Quaterniond rot)
    {
        m_pos = pos;
        rot = rot;
    }

    auto get_shape() -> S
    {
        return m_shape;
    }
    
private:
    Eigen::Vector3d m_pos{Eigen::Vector3d(0, 0, 0)};
    Eigen::Quaterniond m_rot{Eigen::Quaternion(0, 0, 0, 0)};

    Eigen::Vector3d m_lin_vel{Eigen::Vector3d(0, 0, 0)};
    Eigen::Vector3d m_lin_accel{Eigen::Vector3d(0, 0, 0)};

    Eigen::Vector3d m_ang_vel{Eigen::Vector3d(0, 0,0)};
    Eigen::Vector3d m_ang_accel{Eigen::Vector3d(0, 0, 0)};

    S m_shape;
};

#endif