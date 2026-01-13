#include <cmath>

#include "amp_distribution.h"
#include "networking/client/nwclient.h"
#include "networking/server/nwserver.h"
#include "denseutils.h"

#include "rov.h"

#include "utils.h"

#include "servo.h"

#include "test.h"

static const test_t TEST_TEST = test_t("test_test", __LINE__,
	[]()
	{
		if (1 + 1 == 2)
		{
			return true;
		}
		else
		{
			return false;
		}
	});

static const test_t TEST_AMP_DISTRIBUTOR = test_t("test_amp_distributor", __LINE__,
	[]()
	{
		amp_distributor_t distributor = amp_distributor_t(10.0);
		std::shared_ptr<dynamic_amp_request_t> req_a = distributor.invoke_request(5.0, AMP_REQUEST_PRIORITY::ALWAYS_FULFILL);
		std::shared_ptr<dynamic_amp_request_t> req_b = distributor.invoke_request(3.0, AMP_REQUEST_PRIORITY::DISTRIBUTE);
		std::shared_ptr<dynamic_amp_request_t> req_c = distributor.invoke_request(2.0, AMP_REQUEST_PRIORITY::DISTRIBUTE);

		distributor.compute();

		/*
		// Debug purposes
		std::cout << req_a->get_allowance() << std::endl;
		std::cout << req_b->get_allowance() << std::endl;
		std::cout << req_c->get_allowance() << std::endl;
		*/

		if (req_a->get_allowance() != 5.0)
			return false;
		if (req_b->get_allowance() != 3.0)
			return false;
		if (req_c->get_allowance() != 2.0)
			return false;

		std::shared_ptr<dynamic_amp_request_t> req_d = distributor.invoke_request(6.0, AMP_REQUEST_PRIORITY::DISTRIBUTE);

		/*
		std::cout << req_d->get_allowance() << std::endl;
		std::cout << req_a->get_allowance() << std::endl;
		std::cout << req_b->get_allowance() << std::endl;
		std::cout << req_c->get_allowance() << std::endl;
		*/

		if (req_a->get_allowance() != 5.0)
			return false;
		if (approx_eq(req_b->get_allowance(), 1.6667, 0.1) == false)
			return false;
		if (approx_eq(req_c->get_allowance(), 1.6667, 0.1) == false)
			return false;
		if (approx_eq(req_d->get_allowance(), 1.6667, 0.1) == false)
			return false;

		return true;
	});

static const test_t TEST_SERVO = test_t("test_servo", __LINE__,
	[]()
	{
		servo_t servo = servo_t(9);

		// Do some testing... try to fail the test

		return true;
	});

static const test_t TEST_PWM_THROTTLE = test_t("test_pwm_throttle", __LINE__,
	[]()
	{
		utils::linear_percentage_t throttle = utils::linear_percentage_t(1000.0, 1100.0);
		double p = throttle.to_percentage(1050.0);

		if (p != 0.5)
			return false;

		p = throttle.to_percentage(1075.0);

		if (p != 0.75)
			return false;

		double v = throttle.to_value(p);

		if (v != 1075.0)
			return false;

		return true;
	});

static const test_t TEST_ABSTRACT_ROV = test_t("test_abstract_rov", __LINE__,
	[]()
	{
		rov_t rov = rov_t();
		const double FORCE = 28.63542; // Roughly approximation of a BlueRobotics T200 Thruster maximmum output

		const double sqrt22 = sqrt(2) / 2;

		// A terribly impractical ROV... but mathematically simple and easy to test
		rov.create_thruster({1.0, 0, 0}, {0.0, 1.0, 0.0}, FORCE);
		rov.create_thruster({-1.0, 0, 0}, {0, 1, 0}, FORCE);
		rov.create_thruster({0, 0, 1.0}, {0, 0, 1}, FORCE);
		rov.create_thruster({0, 0, -1.0}, {0, 0, 1}, FORCE);

		rov.optimize_throttle_config({0, 3, 0}, {0, 0, 0});

		return true;
	});

/*
static const test_t TEST_DENSE_UTILS = test_t("", __LINE__, [](){
	quat_from_euler(Eigen::Vector3d());
});
*/
auto main() -> int
{
	TEST_TEST.run();
	TEST_AMP_DISTRIBUTOR.run();
	TEST_SERVO.run();
	TEST_PWM_THROTTLE.run();
	TEST_ABSTRACT_ROV.run();

	return 0;
}