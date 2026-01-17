#ifndef H_ROV
#define H_ROV

#include <memory>

#include "denseutils.h"
#include "utils.h"
#include "geometry/rectprism.h"

#include "amp_distribution.h"
#include "thruster/thruster.h"

class rov_t
{
public:
	explicit rov_t() {}
	~rov_t() {}

	/**
	 * @brief Create a thruster object
	 *
	 * @param pos Position of the thruster
	 * @param look Look vector of the thruster (thrusters are really simple!)
	 */
	void create_thruster(const Eigen::Vector3d pos, const Eigen::Vector3d look, const double force)
	{
		ensure_is_unit(look);

		std::shared_ptr<thruster_t> new_thruster = std::make_shared<thruster_t>(pos, look, force);
		m_thrusters.push_back(new_thruster);
	}

	auto calculate_unbalanced_torque() -> Eigen::Vector3d
	{
		if (m_thrusters.size() == 0)
		{
			utils::log("(rov) No thrusters, cannot calculate torque.", utils::MSG_TYPE::WARN);
		}

		Eigen::Vector3d sum = Eigen::Vector3d(0, 0, 0);

		for (auto thruster : m_thrusters)
		{
			Eigen::Vector3d &look = thruster->get_look();
			Eigen::Vector3d &pos = thruster->get_pos();

			const Eigen::Vector3d tau = pos.cross(look);
			sum += tau;
		}

		return sum;
	}

	/**
	 * @brief Throttle each thruster correctly to maximize the "correctness" of the direction
	 * towards a target point. Magnitude is arbitrarily 1 N of force.
	 *
	 * @param target The target point to optimize the configuration towards. Should be within
	 * world space.
	 */
	void optimize_throttle_config(Eigen::Vector3d target, Eigen::Vector3d target_rotational);

private:
	thrusters_t m_thrusters = {};
	std::shared_ptr<amp_distributor_t> m_amp_distributor;

	/**
	 * @brief The geometric shape of the ROV, not the physical shape. Utilities
	 * for geometric properties such as the centroid.
	 *
	 */
	std::shared_ptr<rectprism_t> m_shape;

	/**
	 * @brief World rotation of the ROV
	 *
	 */
	Eigen::Quaterniond m_rot;

	/**
	 * @brief Optimize a specific thruster towards a target.
	 *
	 * @param which
	 * @param target
	 */
	void optimize_thruster(std::shared_ptr<thruster_t> which, Eigen::Vector3d &target, Eigen::Vector3d &target_rotational);
};

#endif