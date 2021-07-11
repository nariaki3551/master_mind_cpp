#include <omp.h>
#include <argparse/argparse.hpp>
#include <progresscpp/ProgressBar.hpp>

#include "run.h"


namespace MasterMind
{

void runInteractive(
      Config &config
      ) noexcept
{
   CodePtrList S;
   allCodeGenerator(config, S);

   // main
   int count = 0;
   CodePtrList G;
   CodePtrList guessHist;
   while( S.size() > 1 )
   {
      count++;
      std::cout
         << std::endl
         << "count:  " << count
         << ", #S: " << S.size()
         << std::endl;
      G.clear();
      setGuessCandidates(S, guessHist, config, G);
      auto guess = policy(S, G, config);
      trial(S, guess, config);
      guessHist.push_back(guess);
   }

   // post process
   auto secret = S[0];
   std::cout << "secret is " << strCode(secret) << std::endl;
}


void runTest(
      Config &config
      ) noexcept
{
   CodePtrList S;
   allCodeGenerator(config, S);

   std::vector<int> countTable(S.size());
   std::vector<double> timeTable(S.size());
   auto startTotal = omp_get_wtime();

   // initialize the bar
   progresscpp::ProgressBar progressBar(S.size(), 70);


#pragma omp parallel for firstprivate(config)
   for ( int i = 0; i < static_cast<int>(S.size()); ++i )
   {
#if OMP_VERBOSE
      if ( i == 0 )
         std::cout << "parallel test using " << omp_get_num_threads() << " threads " << std::endl;
#endif

#pragma omp critical
      {
         // record the tick and display the bar
         ++progressBar;
         progressBar.display();
      }

      // test code
      auto secret = S[i];
      config.setSecret(secret);
      CodePtrList testS = copy(S);
      CodePtrList guessHist;
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


Config getConfig(
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

   program.add_argument("--policy")
      .help("type of policy: random, minmax, exp_minmax, entropy")
      .default_value(std::string("random"))
      .action([](const std::string& value) { return value; });

   program.add_argument("--no_duplicate")
      .help("secret codes donot have color duplication")
      .default_value(false)
      .implicit_value(true);

   program.add_argument("--test")
      .help("run test mode")
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
   bool interactive = !program.get<bool>("--test");
   std::string policy= program.get<std::string>("--policy");

   // create config object
   Config config{nColors, nPins, duplicate, interactive, policy};
   return config;
}

}; // MasterMind
