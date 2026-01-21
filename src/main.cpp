#include "dss/runtime.h"
#include "dss/DSS.h"

#include <thread>

#include "app.h"

const std::string MAIN_CLI_NAME = "dyver-dss";
void command_line(std::shared_ptr<DSS::executor_t> p_exec)
{
	DSS::cli_t cli = DSS::cli_t(p_exec, MAIN_CLI_NAME);
	cli.init();
}

auto main(int argv, char **argc) -> int
{
	(void)argv;
	(void)argc;

	DSS::environment_t env = DSS::environment_t();

	env.init();
	std::shared_ptr<DSS::executor_t> main_executor = env.main_executor();

	if (main_executor == nullptr)
	{
		return 1;
	}

	app_t app = app_t(main_executor);

	std::thread cli_handle(command_line, main_executor);

	app.run();

	cli_handle.join();

	return 0;
}