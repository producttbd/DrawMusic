#ifndef BININFORMATIONCALCULATOR_H_INCLUDED
#define BININFORMATIONCALCULATOR_H_INCLUDED

#include "JuceHeader.h"

#include "../GridData/GridData.h"
#include "AudioSystemConfiguration.h"

class BinInformationCalculator
{
 public:
  struct BinInformation
  {
    Array<float> Waveform;
    int CycleLength;
  };

  static Array<BinInformation> getBinInformation(AudioSystemConfiguration config,
                                                 const GridData& gridData);
};

#endif  // BININFORMATIONCALCULATOR_H_INCLUDED
