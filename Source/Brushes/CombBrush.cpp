#include "CombBrush.h"

#include "AbstractBrushControls.h"
#include "GridColourScheme.h"

using ControlSpec = AbstractBrushControls::ControlSpec;

CombBrush::CombBrush()
    : numberHarmonics_(8.0f),
      evenIntensity_(1.0),
      oddIntensity_(0.7),
      taper_(0.3),
      spacing_(Configuration::getBinsPerOctave())
{
  ControlSpec spec({"Number", 1.0f, 30.0f, numberHarmonics_});
  supportedControls_.add(spec);
  controlWirings_.set(spec.name, &numberHarmonics_);

  spec = ControlSpec({"Even intensity", 0.0f, 1.0f, evenIntensity_});
  supportedControls_.add(spec);
  controlWirings_.set(spec.name, &evenIntensity_);

  spec = ControlSpec({"Odd intensity", 0.0f, 1.0f, oddIntensity_});
  supportedControls_.add(spec);
  controlWirings_.set(spec.name, &oddIntensity_);

  spec = ControlSpec({"Taper", 0.0f, 1.0f, taper_});
  supportedControls_.add(spec);
  controlWirings_.set(spec.name, &taper_);

  spec = ControlSpec({"Spacing", 2.0f, 200.0f, spacing_});
  supportedControls_.add(spec);
  controlWirings_.set(spec.name, &spacing_);
}

void CombBrush::drawPreviewInto(juce::Graphics& g, const Rectangle<int>& bounds) const
{
  const Colour zeroColour = GridColourScheme::convertToColour(0.0f);
  g.fillAll(zeroColour);

  const auto centreX = bounds.getCentreX();
  const auto centreY = bounds.getCentreY();

  auto harmonics = getHarmonics(Configuration::getDefaultPressure());
  for (auto& harmonic : harmonics)
  {
    auto y = centreY + harmonic.Spacing;
    g.setColour(GridColourScheme::convertToColour(harmonic.Intensity));
    g.setPixel(centreX, y);
  }
}

Array<GridPoint> CombBrush::applyBrushToPoint(StrokePoint p, GridData& gridData) const
{
  Array<GridPoint> affectedPoints;
  const auto gridWidth = gridData.getWidth();
  const auto gridHeight = gridData.getHeight();
  if (p.gridPoint.x < 0 || p.gridPoint.x >= gridWidth || p.gridPoint.y < 0 ||
      p.gridPoint.y >= gridHeight)
  {
    return {};
  }

  auto harmonics = getHarmonics(p.pressure);

  for (auto& harmonic : harmonics)
  {
    auto y = p.gridPoint.y + harmonic.Spacing;
    if (y < 0 || y >= gridHeight)
    {
      break;
    }
    GridPoint affectedPoint(p.gridPoint.x, y);
    if (harmonic.Intensity > gridData[affectedPoint])  // Don't decrease the intensity of the point.
    {
      gridData[affectedPoint] = harmonic.Intensity;
      affectedPoints.add(affectedPoint);
    }
  }

  return affectedPoints;
}

int CombBrush::getSpacing(int i) const
{
  return -roundDoubleToInt(spacing_ * log2(i + 1));
}

Array<CombBrush::Harmonic> CombBrush::getHarmonics(float pressure) const
{
  const auto numberHarmonics = roundDoubleToInt(numberHarmonics_);
  const auto taperBase = taper_ / (numberHarmonics_ - 1.0f);
  float max_value = intensityScalar_ * pressure;

  Array<Harmonic> output;
  output.add({0, max_value});
  for (int i = 1; i < numberHarmonics; ++i)
  {
    const float taperAmount = 1.0f - (taperBase * i);
    const float harmonicIntensity = i % 2 == 0 ? evenIntensity_ : oddIntensity_;
    const float value = taperAmount * harmonicIntensity * max_value;
    const int y = getSpacing(i);
    output.add({y, value});
  }
  return output;
}

int OctaveBrush::getSpacing(int i) const
{
  return -roundDoubleToInt(spacing_ * i);
}