#include <iostream>
#include <chrono>
#include <argparse/argparse.hpp>

#include "def.h"
#include "utils.h"
#include "policy.h"
#include "trial.h"
#include "codeGenerator.h"


/**
* @fn Config getConfig(int argc, char *argv[])
* @brief コマンドライン入力を受けとる
* @param[in] argc
* @param[in] argv
* @return Config パラメタ管理クラス
*/
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

   // create config object
   Config config{nColors, nPins, duplicate, interactive};
   return config;
}


/**
 * @fn void runInteractive(Config &config)
 * @brief ユーザの(hit, blow)入力による探索
 * @param[in] config
 */
void runInteractive(
      Config &config
      )
{
   CodePtrList S;
   allCodeGenerator(config, S);

   // main
   int count = 0;
   decltype(policy(S, S)) guess;
   while( S.size() > 1 )
   {
      count++;
      std::cout
         << std::endl
         << "count:  " << count
         << ", #S: " << S.size()
         << std::endl;
      guess = policy(S, S);      // G <- S
      trial(S, guess, config);   // update S
   }

   // post process
   auto secret = S[0];
   std::cout << "secret is " << strCode(secret) << std::endl;
   if ( secret ) delete secret;
}


/**
 * @fn void runInteractive(Config &config)
 * @brief 全てのsecret codeに対する計測
 * @param[in] config
 */
void runTest(
      Config &config
      )
{
   CodePtrList S;
   allCodeGenerator(config, S);

   std::vector<int> countTable(S.size());
   std::vector<double> timeTable(S.size());

   int i = 0;
   for ( auto secret : S )
   {
      // test code
      config.setSecret(*secret);
      CodePtrList testS = copy(S);

      int count = 0;

      auto start = std::chrono::system_clock::now(); // 計測開始時間
      while( testS.size() > 1 )
      {
         count++;
         auto guess = policy(testS, testS);  // G <- S
         trial(testS, guess, config);        // update S
      }
      auto end = std::chrono::system_clock::now();  // 計測終了時間

      assert( *testS[0] == *secret );
      if ( testS[0] ) delete testS[0];
      double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            end-start).count();  //処理に要した時間をミリ秒に変換
      countTable[i] = count;
      timeTable[i] = elapsed;
      i++;
   }

   // output statistics
   int maxCount = *std::max_element(countTable.begin(), countTable.end());
   double averageCount = std::accumulate(countTable.begin(), countTable.end(), 0.0) / countTable.size();
   double totalTime = std::accumulate(timeTable.begin(), timeTable.end(), 0.0);
   double averageTime = totalTime / timeTable.size();
   std::cout
      << "Log,num colors,num pins,max count,average count,total time,average time"
      << std::endl;
   std::cout
      << "log"
      << "," << config.nColors   << "," << config.nPins
      << "," << maxCount         << "," << averageCount
      << "," << totalTime        << "," << averageTime
      << std::endl;

   for ( auto code : S )
   {
      if ( code ) delete code;
   }
}


int main(
      int argc,
      char *argv[]
      )
{
   Config config = getConfig(argc, argv);
   std::cout << config.str() << std::endl;

   if ( config.interactive )
   {
      runInteractive(config);
   }
   else
   {
      runTest(config);
   }

   return 0;
}
