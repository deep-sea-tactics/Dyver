#include "rov.h"

void rov_t::optimize_throttle_config(Eigen::Vector3d target)
{
	for (auto p_thruster : m_thrusters)
	{
		optimize_thruster(p_thruster, target);
	}
}

void rov_t::optimize_thruster(std::shared_ptr<thruster_t> which, Eigen::Vector3d &target)
{
	Eigen::Vector3d &look = which->get_look();
	Eigen::Vector3d &pos = which->get_pos();
}