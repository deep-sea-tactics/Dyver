#ifndef H_THRUSTER
#define H_THRUSTER

#include <memory>
#include <vector>

#include <Eigen/Dense>

/**
 * @brief Abstract thruster; purely a mathematical object
 *
 */
class thruster_t
{
public:
	thruster_t(const Eigen::Vector3d pos, const Eigen::Vector3d look)
	{
		m_pos = pos;
		m_look = look;
	}

	auto get_pos() -> Eigen::Vector3d & { return m_pos; }
	auto get_look() -> Eigen::Vector3d & { return m_look; }
	auto get_force() -> double & { return m_force; }

private:
	/**
	 * @brief Linearly scaled "maximum" force output of the thruster.
	 *
	 */
	double m_force;

	Eigen::Vector3d m_pos{Eigen::Vector3d(0, 0, 0)};
	Eigen::Vector3d m_look{Eigen::Vector3d(0, 0, 0)}; // Tada! Thrusters are very simple...
};

typedef std::vector<std::shared_ptr<thruster_t>> thrusters_t;

#endif