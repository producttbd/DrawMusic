#ifndef AUDIOSYSTEMCONFIGURATION_H_INCLUDED
#define AUDIOSYSTEMCONFIGURATION_H_INCLUDED

#include "../Configuration.h"

struct AudioSystemConfiguration
{
  AudioSystemConfiguration()
      : MinimumFrequency(Configuration::getMinimumFrequency()),
        BinsPerOctave(Configuration::getBinsPerOctave()),
        WindowLength(Configuration::getReconstructionWindowLength()),
        SampleRate(44100.0)  // TODO fix this
  {
  }

  AudioSystemConfiguration& operator=(const AudioSystemConfiguration&) = default;

  float MinimumFrequency;
  float BinsPerOctave;
  int WindowLength;
  double SampleRate;
  float MinThreshold = 0.00001f;
  float GlobalScalar = 0.1f;
  float RampTransitionCycles = 5.0f;
  int MinWaveTableLength = 512;
};

#endif  // AUDIOSYSTEMCONFIGURATION_H_INCLUDED
