#include "AudioBufferThumbnail.h"

AudioBufferThumbnail::AudioBufferThumbnail() { zeroOut(); }

void AudioBufferThumbnail::zeroOut()
{
  data.resize(1);
  data.getReference(0).setFloat(0.0, 0.0);
}

void AudioBufferThumbnail::refresh(const juce::AudioSampleBuffer& source, int samplesPerSample)
{
  const auto numSamples = source.getNumSamples();
  const auto numWindows = numSamples / samplesPerSample;

  auto input = source.getReadPointer(0);

  data.resize(numWindows);
  auto output = data.getRawDataPointer();

  for (int w = 0; w < numWindows; ++w)
  {
    float minimum = 0.0f;
    float maximum = 0.0f;
    for (int i = 0; i < samplesPerSample; ++i)
    {
      minimum = jmin(input[w * samplesPerSample + i], minimum);
      maximum = jmax(input[w * samplesPerSample + i], maximum);
    }
    output[w].setFloat(minimum, maximum);
  }
}

void AudioBufferThumbnail::drawChannel(Graphics& g, const Rectangle<int>& area)
{
  const float sliceWidth = static_cast<float>(area.getWidth()) / static_cast<float>(data.size());
  const float middle = static_cast<float>(area.getCentreY());
  const float scale = static_cast<float>(area.getHeight()) / 2.0f;
  const float leftEdge = static_cast<float>(area.getX());
  const float minHeight = 2.0f;

  for (int i = 0; i < data.size(); ++i)
  {
    const float x = leftEdge + sliceWidth * i;
    const float y = middle - jmax(data[i].getMaxValue() * scale, minHeight / 2.0f);
    const float height = jmax(data[i].getSpread() * scale, minHeight);
    g.fillRect(x, y, sliceWidth, height);
  }
}