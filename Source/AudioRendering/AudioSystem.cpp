#include "AudioSystem.h"

#include "AudioFileWriter.h"

AudioSystem::AudioSystem(const GridData& gridData,
                         AudioDataChangedNotifier& audioDataChangedNotifier)
    : audioDataChangedNotifier_(audioDataChangedNotifier),
      deviceManager_(),
      audioSourcePlayer_(),
      transportSource_(),
      gridAudioSource_(gridData, audioDataChangedNotifier_),
      audioSettingsWindow_(nullptr)
{
  // TODO channels?
  deviceManager_.initialiseWithDefaultDevices(0, 2);
  deviceManager_.addAudioCallback(&audioSourcePlayer_);
  audioSourcePlayer_.setSource(&transportSource_);
  transportSource_.setSource(&gridAudioSource_);
}

AudioSystem::~AudioSystem()
{
  transportSource_.setSource(nullptr);
  audioSourcePlayer_.setSource(nullptr);
  deviceManager_.closeAudioDevice();
  if (audioSettingsWindow_ != nullptr)
  {
    audioSettingsWindow_.deleteAndZero();
  }
}

void AudioSystem::entireGridDataUpdatedCallback()
{
  gridAudioSource_.rerenderAll();
}

void AudioSystem::partialBrushStrokeCallback(const Array<GridPoint>& affectedPoints)
{
  // We don't need to render audio of an brush stroke in progress, it would be rendering and
  // re-rendering too frequently to be useful.
}

void AudioSystem::completeBrushStrokeCallback(const Array<GridPoint>& affectedPoints)
{
  gridAudioSource_.rerenderAsNeeded(affectedPoints);
}

void AudioSystem::gridDataResizedCallback()
{
  gridAudioSource_.reinitialize();
}

bool AudioSystem::isPlaying() const
{
  return transportSource_.isPlaying();
}

void AudioSystem::startPlayback()
{
  transportSource_.start();
}

void AudioSystem::stopPlayback()
{
  transportSource_.stop();
}

void AudioSystem::setNewPlaybackPosition(float fraction)
{
  gridAudioSource_.setNewPlaybackPosition(fraction);
}

void AudioSystem::openSettingsWindow()
{
  if (audioSettingsWindow_ != nullptr)
  {
    return;
  }
  audioSettingsWindow_ = new AudioSettingsWindow(TRANS("audio settings window"), deviceManager_);
}

void AudioSystem::saveAudioToFile() const
{
  AudioFileWriter::saveToFileWithDialogBox(gridAudioSource_.getOutputBuffer());
}