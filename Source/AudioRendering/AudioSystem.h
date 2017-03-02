#ifndef AUDIOSYSTEM_H_INCLUDED
#define AUDIOSYSTEM_H_INCLUDED

#include "JuceHeader.h"

#include "../GridData/GridData.h"
#include "../UI/AudioSettingsWindow.h"
#include "AudioDataChangedNotifier.h"
#include "GridAudioRendererAudioSource.h"

class AudioSystem : public GridDataChangedNotifier::GridDataResizedListener,
                    public GridDataChangedNotifier::GridDataUpdatedListener
{
 public:
  AudioSystem(const GridData& gridData, AudioDataChangedNotifier& audioDataChangedNotifier);
  ~AudioSystem();

  // GridDataChangedNotifier methods
  // Called when new gridData is available and needs rerendering
  void entireGridDataUpdatedCallback() override;
  void partialBrushStrokeCallback(const Array<GridPoint>& affectedPoints) override;
  void completeBrushStrokeCallback(const Array<GridPoint>& affectedPoints) override;
  void gridDataResizedCallback() override;

  bool isPlaying() const;
  void startPlayback();
  void stopPlayback();

  void setNewPlaybackPosition(float fraction);

  void openSettingsWindow();
  void saveAudioToFile() const;

 private:
  AudioDataChangedNotifier& audioDataChangedNotifier_;
  AudioDeviceManager deviceManager_;
  AudioSourcePlayer audioSourcePlayer_;
  AudioTransportSource transportSource_;
  GridAudioRendererAudioSource gridAudioSource_;
  Component::SafePointer<Component> audioSettingsWindow_;
};

#endif  // AUDIOSYSTEM_H_INCLUDED
