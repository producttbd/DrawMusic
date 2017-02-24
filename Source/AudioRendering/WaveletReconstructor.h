#ifndef WAVELETRECONSTRUCTOR_H_INCLUDED
#define WAVELETRECONSTRUCTOR_H_INCLUDED

#include "JuceHeader.h"

#include "../GridData/GridData.h"

class WaveletReconstructor
{
 public:
  explicit WaveletReconstructor(const GridData& gridData);

  // TODO make the dependencies on Configuration explicit
  void reinitialize();

  void perform(AudioSampleBuffer& buffer) const;
  void perform(AudioSampleBuffer& buffer, const Array<GridPoint>& affectedPoints) const;

 private:
  void performInternal(AudioSampleBuffer& buffer, int minX, int maxX) const;
  void createBinInformation();

  // Contains the wave table and how many cycles the wave table contains for each row (frequency)
  // of the GridData.
  struct BinInformation
  {
    Array<float> Waveform;
    int CycleLength;
  };
  Array<BinInformation> waveTables_;

  const GridData& gridData_;
  float minimumFrequency_;
  float binsPerOctave_;
  int windowLength_;
  double sampleRate_;
  const float minThreshold = 0.00001f;
  const float impulseThreshold = 0.1f;
  const float globalScalar_ = 0.1f;
  const float rampTransitionCycles_ = 5.0f;
  const int minWaveTableLength_ = 512;
};

#endif  // WAVELETRECONSTRUCTOR_H_INCLUDED