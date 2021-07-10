#include <iostream>

#include "run.h"
#ifdef USE_MPI
#include "mpi.h"
#include "runMpi.h"
#endif


int main(
      int argc,
      char *argv[]
      )
{
   namespace mm = MasterMind;
   mm::Config config = mm::getConfig(argc, argv);

#ifdef USE_MPI
   int size, rank;
   MPI_Init( &argc, &argv );
   MPI_Comm_size( MPI_COMM_WORLD, &size );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   if ( rank == 0 )
   {
      std::cout << config.str() << std::endl;
      std::cout << "MPI size = " << size << std::endl;
   }
#else
   std::cout << config.str() << std::endl;
#endif


   if ( config.interactive )
   {
      mm::runInteractive(config);
   }
#ifdef USE_MPI
   else if ( size > 0 )
   {
      mm::runTestPara(config, size, rank);
   }
#endif
   else
   {
      mm::runTest(config);
   }

#ifdef USE_MPI
   MPI_Finalize();
#endif
   return 0;
}
