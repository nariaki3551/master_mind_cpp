#include <iostream>

#include "run.h"


int main(
      int argc,
      char *argv[]
      )
{
   namespace mm = MasterMind;
   mm::Config config = mm::getConfig(argc, argv);
   std::cout << config.str() << std::endl;

   if ( config.interactive )
   {
      mm::runInteractive(config);
   }
   else
   {
      mm::runTest(config);
   }

   return 0;
}
