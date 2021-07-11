#include <omp.h>
#include <mpi.h>
#include <progresscpp/ProgressBar.hpp>
#include "runMpi.h"


namespace MasterMind
{

void runTestPara(
      Config &config,
      int nProcesses,
      int rank
      ) noexcept
{
   CodePtrList S;
   allCodeGenerator(config, S);

   std::vector<int> countTable(S.size());
   std::vector<double> timeTable(S.size());
   auto startTotal = omp_get_wtime();
   int sendcount = 0;

   // initialize the bar
   progresscpp::ProgressBar progressBar(S.size(), 70);

   for ( int i = 0; i*nProcesses + rank < static_cast<int>(S.size()); ++i )
   {
      if ( rank == 0 )
      {
         // record the tick and display the bar
         for ( int j = 0; j < nProcesses; j++ ) ++progressBar;
         progressBar.display();
      }
      // test code
      auto secret = S[i*nProcesses + rank];
      sendcount++;
      config.setSecret(secret);
      CodePtrList testS = copy(S);
      CodeList guessHist;
      CodePtrList G;

      int count = 0;
      auto start = omp_get_wtime();
      while( testS.size() > 1 )
      {
         count++;
         G.clear();
         setGuessCandidates(S, guessHist, config, G);
         auto guess = policy(testS, G, config);
         trial(testS, guess, config);
         guessHist.push_back(guess);
      }
      auto end = omp_get_wtime();

      assert( *testS[0] == *secret );
      double elapsed = end - start;
      countTable[i] = count;
      timeTable[i] = elapsed;
   }


   if( nProcesses > 0 )
   {
      MPI_Gather(countTable.data(), sendcount, MPI_INT, countTable.data(), sendcount, MPI_INT, 0, MPI_COMM_WORLD);
      MPI_Gather(timeTable.data(), sendcount, MPI_DOUBLE, timeTable.data(), sendcount, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   }

   if( rank == 0 )
   {
      auto endTotal = omp_get_wtime();
      // output statistics
      auto getMax = [&](auto &v){ return *std::max_element(v.cbegin(), v.cend()); };
      auto getSum = [&](auto &v){ return std::accumulate(v.cbegin(), v.cend(), 0.0); };
      auto getAve = [&](auto &v){ return getSum(v) / v.size(); };
      int maxCount         = getMax(countTable);
      double averageCount  = getAve(countTable);
      double totalTime     = endTotal - startTotal;
      double averageTime   = getAve(timeTable);
      std::cout
         << std::endl
         << "Log,num colors,num pins,policy,max count,average count,total time,average time"
         << std::endl;
      std::cout
         << "log"
         << "," << config.nColors   << "," << config.nPins
         << "," << config.policy
         << "," << maxCount         << "," << averageCount
         << "," << totalTime        << "," << averageTime
         << std::endl;
   }
}

}; // MasterMind

