#ifndef AUDIODATACHANGEDNOTIFIER_H_INCLUDED
#define AUDIODATACHANGEDNOTIFIER_H_INCLUDED

#include "JuceHeader.h"

class AudioDataChangedNotifier
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

  void addNewAudioListener(NewAudioListener* listener);
  void removeNewAudioListener(NewAudioListener* listener);
  void callNewAudioListeners(const AudioSampleBuffer& buffer);

  void addNewPositionListener(NewPositionListener* listener);
  void removeNewPositionListener(NewPositionListener* listener);
  void callNewPositionListeners(float fraction);

 private:
  ListenerList<NewAudioListener> newAudioListeners_;
  ListenerList<NewPositionListener> newPositionListeners_;
};

#endif  // AUDIODATACHANGEDNOTIFIER_H_INCLUDED
