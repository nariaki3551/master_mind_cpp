#include <iostream>
#include <argparse/argparse.hpp>

#include "def.h"
#include "utils.h"
#include "policy.h"
#include "trial.h"
#include "codeGenerator.h"


int main(
      int argc,
      char *argv[]
      )
{
   argparse::ArgumentParser program("master mind");

   program.add_argument("num_colors")
      .help("number of colors")
      .action([](const std::string& value) { return std::stoi(value); });

   program.add_argument("num_pins")
      .help("number of pins")
      .action([](const std::string& value) { return std::stoi(value); });

   program.add_argument("--no_duplicate")
      .help("secret codes donot have color duplication")
      .default_value(false)
      .implicit_value(true);
   try
   {
      program.parse_args(argc, argv);
   }
   catch (const std::runtime_error& err)
   {
      std::cout << err.what() << std::endl;
      std::cout << program;
      exit(0);
   }

   int nColors = program.get<int>("num_colors");
   int nPins = program.get<int>("num_pins");
   bool duplicate = !program.get<bool>("--no_duplicate");

   // create config object
   Config config{nColors, nPins, duplicate};

   CodeList S;
   allCodeGenerator(config, S);

   // main
   decltype(policy(S, S)) guess;
   while( S.size() > 1 )
   {
      guess = policy(S, S);      // G <- S
      trial(S, guess, config);   // update S
   }

   // post process
   auto secret = S[0];
   std::cout << "secret is " << strCode(secret) << std::endl;

   return 0;
}
