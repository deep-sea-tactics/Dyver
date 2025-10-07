#include "DSS.h"

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

    DSS::CLI cli = DSS::CLI(&main_executor);
    cli.init(); // TODO: Execute "src example.dss" in the console to see DSS in action

    return 0;
}