#ifndef AUDIOFILEWRITER_H_INCLUDED
#define AUDIOFILEWRITER_H_INCLUDED

#include "JuceHeader.h"

class AudioFileWriter
{
public:
    static void saveToFileWithDialogBox(const AudioSampleBuffer& buffer)
    {
        AudioFormatManager afManager;
        afManager.registerBasicFormats();
        AudioFormat* format = afManager.getDefaultFormat();

        FileChooser fileChooser(TRANS("Select output file"),
                                File::nonexistent,
                                format->getFileExtensions().joinIntoString(";"));
        if (fileChooser.browseForFileToSave(true))
        {
            File file(fileChooser.getResult());
            ScopedPointer<AudioFormatWriter> writer =
            format->createWriterFor(file.createOutputStream(), 44100, buffer.getNumChannels(), 16, NULL, 0);
            writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
        }
    }
};




#endif  // AUDIOFILEWRITER_H_INCLUDED
