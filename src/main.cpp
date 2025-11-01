#include "DSS.h"
#include "runtime.h"

#include <iostream>
#include <thread>

#include "app.h"

const std::string MAIN_CLI_NAME = "dyver-dss";
void command_line(DSS::Executor *p_exec)
{
    DSS::CLI cli = DSS::CLI(p_exec, MAIN_CLI_NAME);
    cli.init();
}

int main(int argv, char** argc)
{
    DSS::Environment env = DSS::Environment();

    env.init();
    std::optional<DSS::Executor> opt_main_executor = env.main_executor();

    if (opt_main_executor.has_value() == false)
    {
        return 1;
    }

    DSS::Executor main_executor = opt_main_executor.value();

    app_t app = app_t(&main_executor);

    std::thread cli_handle (command_line, &main_executor);
    
    app.run();

    cli_handle.join();
    
    return 0;
}