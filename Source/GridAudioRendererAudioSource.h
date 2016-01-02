#ifndef GRIDAUDIORENDERERAUDIOSOURCE_H_INCLUDED
#define GRIDAUDIORENDERERAUDIOSOURCE_H_INCLUDED

#include "JuceHeader.h"

#include "Configuration.h"
#include "GridData.h"

class GridAudioRendererAudioSource : public PositionableAudioSource,
                                     public Slider::Listener,
                                     public ChangeListener
{
public:
    class NewAudioListener
    {
    public:
        virtual void newAudioCallback(const AudioSampleBuffer& updatedAudio) =0;
        virtual ~NewAudioListener() {}
    };
    
    class NewPositionListener
    {
    public:
        virtual void newPositionCallback(float fraction) =0;
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
    
    // ChangeListener method
    // Called when new gridData is available and needs rerendering
    void changeListenerCallback(ChangeBroadcaster *source) override;

    // AudioSource methods
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock (const AudioSourceChannelInfo &bufferToFill) override;
    
    // PositionableAudioSource methods
    void setNextReadPosition (int64 newPosition) override;
    int64 getNextReadPosition () const override;
    int64 getTotalLength() const override;
    bool isLooping() const override;
    void setLooping(bool shouldLoop) override;

    // Slider::Listener methods
    void sliderValueChanged(Slider* slider) override;
    void sliderDragStarted(Slider* slider) override;
    void sliderDragEnded(Slider* slider) override;

private:
    void callDeviceChangeListeners();

    static inline int freqIndexToColumnIndex(int i)
    {
        return Configuration::getFftLength() - i;
    }


    const GridData& gridData_;
    bool readyToPlay_;
    FFT fft_;
    AudioSampleBuffer fullPieceAudioBuffer_;
    int currentOutputOffset_;

    int lgIterations_;

    ListenerList<NewAudioListener> newAudioListeners_;
    ListenerList<NewPositionListener> newPositionListeners_;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GridAudioRendererAudioSource);
};


#endif // GRIDAUDIORENDERERAUDIOSOURCE_H_INCLUDED
