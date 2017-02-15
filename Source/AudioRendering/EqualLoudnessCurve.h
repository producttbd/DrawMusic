#ifndef EQUALLOUDNESSCURVE_H_INCLUDED
#define EQUALLOUDNESSCURVE_H_INCLUDED

#include "JuceHeader.h"

class EqualLoudnessCurve
{
 private:
  struct EqualLoudnessPoint
  {
    float Frequency;
    float Value;
  };

 public:
  static float getScalarForFrequency(float freq)
  {
    static const int numPoints = 31;
    static const EqualLoudnessPoint curveData[numPoints] = {{20.0f, 1.0f},
                                                            {25.0f, 0.9517852251f},
                                                            {31.5f, 0.9047575564f},
                                                            {40.0f, 0.8600127842f},
                                                            {50.0f, 0.8214774906f},
                                                            {63.0f, 0.7847685143f},
                                                            {80.0f, 0.7492466441f},
                                                            {100.0f, 0.7181992512f},
                                                            {125.0f, 0.68998265f},
                                                            {160.0f, 0.6617660488f},
                                                            {200.0f, 0.6379326089f},
                                                            {250.0f, 0.6166560131f},
                                                            {315.0f, 0.5971144188f},
                                                            {400.0f, 0.5793991416f},
                                                            {500.0f, 0.566614921f},
                                                            {630.0f, 0.5552917542f},
                                                            {800.0f, 0.5468906949f},
                                                            {1000.0f, 0.5479864853f},
                                                            {1250.0f, 0.5675280796f},
                                                            {1600.0f, 0.5770249292f},
                                                            {2000.0f, 0.5475299059f},
                                                            {2500.0f, 0.5228746233f},
                                                            {3150.0f, 0.515204091f},
                                                            {4000.0f, 0.525705415f},
                                                            {5000.0f, 0.5560222811f},
                                                            {6300.0f, 0.6059720573f},
                                                            {8000.0f, 0.654369464f},
                                                            {10000.0f, 0.6680668432f},
                                                            {12500.0f, 0.6267007579f},
                                                            {16000.0f, 0.6248744407f},
                                                            {20000.0f, 0.9580860195f}};

    if (freq <= curveData[0].Frequency)
    {
      return curveData[0].Value;
    }

    for (int i = 1; i < numPoints; ++i)
    {
      if (freq > curveData[i].Frequency)
      {
        continue;
      }
      float f = (freq - curveData[i - 1].Frequency) /
                (curveData[i].Frequency - curveData[i - 1].Frequency);
      return (1.0f - f) * curveData[i - 1].Value + f * curveData[i].Value;
    }
    return curveData[numPoints - 1].Value;
  }
};

#endif  // EQUALLOUDNESSCURVE_H_INCLUDED