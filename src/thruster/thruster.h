#ifndef H_THRUSTER
#define H_THRUSTER

#include <Eigen/Dense>

class thruster_t
{
public:

private:
    Eigen::Vector3d m_pos{Eigen::Vector3d(0, 0, 0)};
    Eigen::Vector3d m_look{Eigen::Vector3d(0, 0, 0)}; // Tada! Thrusters are very simple...
};

#endif