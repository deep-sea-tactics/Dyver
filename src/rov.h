#ifndef H_ROV
#define H_ROV

#include <vector>
#include <memory>

#include "utils.h"

#include "amp_distribution.h"
#include "thruster/thruster.h"

class rov_t
{
public:
	/**
	 * @brief Create a thruster object
	 *
	 * @param pos Position of the thruster
	 * @param look Look vector of the thruster (thrusters are really simple!)
	 */
	void create_thruster(const Eigen::Vector3d pos, const Eigen::Vector3d look)
	{
		std::shared_ptr<thruster_t> new_thruster = std::make_shared<thruster_t>(pos, look);
		m_thrusters.push_back(new_thruster);
	}

	/**
	 * @brief Throttle each thruster correctly to maximize the "correctness" of the direction
	 * towards a target point. Magnitude is arbitrarily 1 N of force.
	 *
	 * @param target The target point to optimize the configuration towards. Should be within
	 * world space.
	 */
	void optimize_throttle_config(Eigen::Vector3d target);

private:
	thrusters_t m_thrusters = {};
	std::shared_ptr<amp_distributor_t> m_amp_distributor;

	void optimize_thruster(std::shared_ptr<thruster_t> which, Eigen::Vector3d &target);
};

#endif