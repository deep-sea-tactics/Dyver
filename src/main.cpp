#include "dss/DSS.h"
#include "dss/runtime.h"

#include <iostream>
#include <thread>

#include "app.h"

const std::string MAIN_CLI_NAME = "dyver-dss";
void command_line(DSS::executor_t *p_exec)
{
	DSS::cli_t cli = DSS::cli_t(p_exec, MAIN_CLI_NAME);
	cli.init();
}

auto main() -> int
{
	DSS::environment_t env = DSS::environment_t();

	env.init();
	std::optional<DSS::executor_t> opt_main_executor = env.main_executor();

	if (opt_main_executor.has_value() == false)
	{
		return 1;
	}

	DSS::executor_t main_executor = opt_main_executor.value();

	app_t app = app_t(&main_executor);

	std::thread cli_handle(command_line, &main_executor);

	app.run();

	cli_handle.join();

	return 0;
}