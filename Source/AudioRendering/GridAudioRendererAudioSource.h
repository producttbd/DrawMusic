#ifndef GRIDAUDIORENDERERAUDIOSOURCE_H_INCLUDED
#define GRIDAUDIORENDERERAUDIOSOURCE_H_INCLUDED

#include "JuceHeader.h"

#include "../Configuration.h"
#include "../GridData/GridData.h"
#include "../GridData/GridDataChangedNotifier.h"
#include "AudioDataChangedNotifier.h"
#include "WaveletReconstructor.h"

class GridAudioRendererAudioSource : public PositionableAudioSource
{
 public:
  GridAudioRendererAudioSource(const GridData& gridData,
                               AudioDataChangedNotifier& audioDataChangedNotifier) noexcept;
  ~GridAudioRendererAudioSource();

  const AudioSampleBuffer& getOutputBuffer() const;
  void reinitialize();
  void rerenderAll();
  void rerenderAsNeeded(const Array<GridPoint>& affectedPoints);
  void setNewPlaybackPosition(float fraction);

  // AudioSource methods
  void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
  void releaseResources() override;
  void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;

  // PositionableAudioSource methods
  void setNextReadPosition(int64 newPosition) override;
  int64 getNextReadPosition() const override;
  int64 getTotalLength() const override;
  bool isLooping() const override;
  void setLooping(bool shouldLoop) override;

 private:
  void callDeviceChangeListeners();

  const GridData& gridData_;
  bool readyToPlay_;
  AudioSampleBuffer fullPieceAudioBuffer_;
  int currentOutputOffset_;

  AudioDataChangedNotifier& audioDataChangedNotifier_;
  WaveletReconstructor reconstructor_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GridAudioRendererAudioSource);
};

#endif  // GRIDAUDIORENDERERAUDIOSOURCE_H_INCLUDED
