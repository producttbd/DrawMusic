#include "BinInformationCalculator.h"

#include "EqualLoudnessCurve.h"

Array<BinInformationCalculator::BinInformation> BinInformationCalculator::getBinInformation(
    AudioSystemConfiguration config, const GridData& gridData)
{
  Array<BinInformation> output;
  const int numberFrequencies = gridData.getHeight();
  output.resize(numberFrequencies);
  for (int i = 0; i < numberFrequencies; ++i)
  {
    BinInformation& binInformation = output.getReference(i);

    auto freq = config.MinimumFrequency * powf(2.0, i / config.BinsPerOctave);
    jassert(freq < config.SampleRate / 2);

    const float repeatLength = (float)(config.SampleRate / freq);
    const int minRequiredTableLength = roundToInt(repeatLength);
    binInformation.CycleLength = minRequiredTableLength;

    const int newWaveTableLength =
        jmax(minRequiredTableLength,
             roundToInt(repeatLength * ceil(config.MinWaveTableLength / repeatLength)));
    binInformation.Waveform.resize(newWaveTableLength);

    float scaleFactor = 2.0f * float_Pi * freq / config.SampleRate;
    auto freqScaleFactor = config.GlobalScalar * EqualLoudnessCurve::getScalarForFrequency(freq);
    for (int j = 0; j < newWaveTableLength; ++j)
    {
      binInformation.Waveform.set(j, freqScaleFactor * sinf(static_cast<float>(j) * scaleFactor));
    }

    // std::cout << freq << "\t" << minRequiredTableLength << "\t" << newWaveTableLength
    //           << "\t" << scaleFactor << "\t" << freqScaleFactor << std::endl;
  }
  return output;
}