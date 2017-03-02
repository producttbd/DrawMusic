#ifndef WAVELETRECONSTRUCTOR_H_INCLUDED
#define WAVELETRECONSTRUCTOR_H_INCLUDED

#include "JuceHeader.h"

#include "../GridData/GridData.h"
#include "AudioDataChangedNotifier.h"
#include "AudioSystemConfiguration.h"
#include "BinInformationCalculator.h"

class WaveletReconstructor : private Thread
{
 public:
  WaveletReconstructor(AudioSampleBuffer& output, const GridData& gridData,
                       AudioDataChangedNotifier& notifier);
  ~WaveletReconstructor() {}

  void perform();
  void perform(const Array<GridPoint>& affectedPoints);

  // TODO make the dependencies on Configuration explicit
  void reinitialize();

 private:
  // Used to interrupt rendering early. Returns true if interrupted.
  bool requestThreadExitAndWait();
  void run();
  Range<int> range_ = Range<int>(0, 0);

  AudioDataChangedNotifier& notifier_;
  AudioSampleBuffer& buffer_;
  const GridData& gridData_;

  AudioSystemConfiguration config_;
  // Contains the wave table and how many cycles the wave table contains for each row (frequency)
  // of the GridData.
  Array<BinInformationCalculator::BinInformation> waveTables_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveletReconstructor);
};

#endif  // WAVELETRECONSTRUCTOR_H_INCLUDED