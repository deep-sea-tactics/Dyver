#include <Eigen>
#include "rov.h"

#include <iostream>
#include "cli.h"
#include "runtime.h"
#include "lang.h"
#include "src/Core/Matrix.h"
#include "utils.h"

int main(int argv, char** argc)
{
    runtime::Environment env = runtime::Environment();
    env.connect_preprocessor_definer(lang::preprocessor_definer);
    env.connect_command_definer(lang::command_definer);
    env.apply_error_key(lang::ERR_KEY);

    env.init();
    std::optional<runtime::Executor> opt_main_executor = env.main_executor();

    if (opt_main_executor.has_value() == false)
    {
        return 1;
    }

    runtime::Executor main_executor = opt_main_executor.value();

    main_executor.exec("out DSS Lovingly says \"Hello, world!\"");
    
    cli::CLI cli = cli::CLI(&main_executor);
    cli.init();

    //TODO: Uncomment and run the example script
    //main_executor.exec("src ../example.dss");

    return 0;
}