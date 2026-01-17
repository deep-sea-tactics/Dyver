#include "denseutils.h"
#include <iostream>

#include "rov.h"

#include <Eigen/Dense>

void rov_t::optimize_throttle_config(Eigen::Vector3d target_translational, Eigen::Vector3d target_rotational)
{
	for (auto p_thruster : m_thrusters)
	{
		optimize_thruster(p_thruster, target_translational, target_rotational);
	}
}

void rov_t::optimize_thruster(std::shared_ptr<thruster_t> which, Eigen::Vector3d &target_translational, Eigen::Vector3d &target_rotational)
{
	Eigen::Vector3d &look = which->get_look();
	Eigen::Vector3d &pos = which->get_pos();

	// Thruster lookat target
	const Eigen::Vector3d lookat = target_translational.normalized();

	const double dot = lookat.dot(look);

	which->get_throttle() = dot;

	const Eigen::Vector3d calc_torque = pos.cross(look);

	std::cout << "Position of the thruster:\n" << pos << std::endl;
	std::cout << std::endl;
	std::cout << "Look of the thruster:\n" << look << std::endl;
	std::cout << std::endl;
	std::cout << "Calculated torque production:\n" << calc_torque << std::endl;
	std::cout << std::endl;
}