#include "AudioDataChangedNotifier.h"

void AudioDataChangedNotifier::addNewAudioListener(
    AudioDataChangedNotifier::NewAudioListener* listener)
{
  newAudioListeners_.add(listener);
}

void AudioDataChangedNotifier::removeNewAudioListener(
    AudioDataChangedNotifier::NewAudioListener* listener)
{
  newAudioListeners_.remove(listener);
}

void AudioDataChangedNotifier::callNewAudioListeners(const AudioSampleBuffer& buffer)
{
  newAudioListeners_.call(&NewAudioListener::newAudioCallback, buffer);
}

void AudioDataChangedNotifier::addNewPositionListener(
    AudioDataChangedNotifier::NewPositionListener* listener)
{
  newPositionListeners_.add(listener);
}

void AudioDataChangedNotifier::removeNewPositionListener(
    AudioDataChangedNotifier::NewPositionListener* listener)
{
  newPositionListeners_.remove(listener);
}

void AudioDataChangedNotifier::callNewPositionListeners(float fraction)
{
  newPositionListeners_.call(&NewPositionListener::newPositionCallback, fraction);
}