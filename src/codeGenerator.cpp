#include "codeGenerator.h"


namespace MasterMind
{


void allCodeGenerator(
      Config &config,
      CodePtrList &codePtrList
      ) noexcept
{
   assert( codePtrList.size() == 0 );
   Itertools itertools;
   auto colors = itertools.range<ColorType>(0, config.nColors);
   if( config.duplicate )
   {
      itertools.product(colors, config.nPins, codePtrList);
   }
   else
   {
      itertools.permutations(colors, config.nPins, codePtrList);
   }
}


void setGuessCandidates(
      CodePtrList &codePtrList,
      CodePtrList &guessHist,
      Config &config,
      CodePtrList &guessCandidates
      ) noexcept
{
   assert ( guessCandidates.size() == 0 );

   // get colors used in guesses
   std::set<ColorType> histColors;
   for ( auto &guess : guessHist )
   {
      for ( auto &color : *guess )
      {
         histColors.insert(color);
      }
   }

   if ( static_cast<int>(histColors.size()) >= config.nColors - 1 )
   {
      guessCandidates = codePtrList;
      return;
   }

   Itertools itertools;
   auto colors = itertools.range<ColorType>(0, config.nColors);
   ColorType minColorNotInHist = -1;
   for ( auto &color : colors )
   {
      if ( histColors.find(color) == histColors.end() )
      {
         minColorNotInHist = color;
         break;
      }
   }
   assert( minColorNotInHist != -1 );

   // extract guess code
   for ( auto &code : codePtrList )
   {
      int tmp = -1;
      bool insert = true;
      for ( auto &color : *code )
      {
         if ( histColors.find(color) == histColors.end() )
         {
            if ( ( tmp == -1 && color != minColorNotInHist )
                  || ( color < tmp ) )
            {
               insert = false;
               break;
            }
            tmp = color;
         }
      }
      if ( insert )
      {
         guessCandidates.push_back(code);
      }
   }
}

}; // MasterMind
