#include "denseutils.h"
#include "utils.h"

#include "rov.h"
#include "Eigen/src/Core/Matrix.h"

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

	// Target relative to thruster (which is, itself, relative to the ROV centroid)
	const Eigen::Vector3d in_local = (target_translational - pos);

	// Thruster lookat target
	const Eigen::Vector3d lookat = in_local.normalized();

	const double dot = lookat.dot(look);
	which->get_throttle() = dot;
}