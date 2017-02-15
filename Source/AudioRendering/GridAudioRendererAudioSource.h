#ifndef GRIDAUDIORENDERERAUDIOSOURCE_H_INCLUDED
#define GRIDAUDIORENDERERAUDIOSOURCE_H_INCLUDED

#include "JuceHeader.h"

#include "Configuration.h"
#include "GridActionManager.h"
#include "GridData.h"
#include "WaveletReconstructor.h"

class GridAudioRendererAudioSource : public PositionableAudioSource,
                                     public GridActionManager::GridDataResizedListener,
                                     public GridActionManager::GridDataUpdatedListener
{
 public:
  class NewAudioListener
  {
   public:
    virtual void newAudioCallback(const AudioSampleBuffer& updatedAudio) = 0;
    virtual ~NewAudioListener() {}
  };

  class NewPositionListener
  {
   public:
    virtual void newPositionCallback(float fraction) = 0;
    virtual ~NewPositionListener() {}
  };

  explicit GridAudioRendererAudioSource(const GridData& gridData) noexcept;
  ~GridAudioRendererAudioSource();

  const AudioSampleBuffer& getOutputBuffer();

  void rerender();
  void addNewAudioListener(NewAudioListener* listener);
  void removeNewAudioListener(NewAudioListener* listener);
  void addNewPositionListener(NewPositionListener* listener);
  void removeNewPositionListener(NewPositionListener* listener);

  // GridActionManagerListener methods
  // Called when new gridData is available and needs rerendering
  void newGridDataCallback() override;
  void gridDataResizedCallback() override;

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
  // TODO make dependencies on Configuration explicit
  void reinitialize();

  void callDeviceChangeListeners();

  const GridData& gridData_;
  bool readyToPlay_;
  AudioSampleBuffer fullPieceAudioBuffer_;
  int currentOutputOffset_;

  WaveletReconstructor reconstructor_;

  ListenerList<NewAudioListener> newAudioListeners_;
  ListenerList<NewPositionListener> newPositionListeners_;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GridAudioRendererAudioSource);
};

#endif  // GRIDAUDIORENDERERAUDIOSOURCE_H_INCLUDED
