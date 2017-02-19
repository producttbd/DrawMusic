#include "CombBrush.h"

#include "AbstractBrushControls.h"
#include "GridColourScheme.h"

using ControlSpec = AbstractBrushControls::ControlSpec;

CombBrush::CombBrush()
    : numberHarmonics_(8.0f),
      evenIntensity_(0.4),
      oddIntensity_(0.3),
      taper_(0.5),
      spacing_(Configuration::getBinsPerOctave())
{
  ControlSpec spec({"Number", 1.0f, 10.0f, numberHarmonics_});
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

  const auto numberHarmonics = roundDoubleToInt(numberHarmonics_);
  const auto spacing = roundDoubleToInt(spacing_);
  const auto taperBase = taper_ / (numberHarmonics_ - 1.0f);

  float value = clampOutputValue(intensityScalar_);
  g.setColour(GridColourScheme::convertToColour(value));
  g.setPixel(centreX, centreY);

  for (int i = 1; i < numberHarmonics; ++i)
  {
    const auto y = centreY - i * spacing;
    const float taperAmount = 1.0f - (taperBase * i);
    const float intensity = i % 2 == 0 ? evenIntensity_ : oddIntensity_;
    value = clampOutputValue(taperAmount * intensity * intensityScalar_);
    g.setColour(GridColourScheme::convertToColour(value));
    g.setPixel(centreX, y);
  }
}

Array<GridPoint> CombBrush::applyBrushToPoint(StrokePoint p, GridData& gridData) const
{
  Array<GridPoint> affectedPoints;
  const auto width = gridData.getWidth();
  const auto height = gridData.getHeight();

  const auto numberHarmonics = roundDoubleToInt(numberHarmonics_);
  const auto spacing = roundDoubleToInt(spacing_);
  const auto taperBase = taper_ / (numberHarmonics_ - 1.0f);

  float max_value = intensityScalar_ * p.pressure;
  if (p.gridPoint.x >= 0 && p.gridPoint.x < width && p.gridPoint.y >= 0 && p.gridPoint.y < height)
  {
    if (max_value > gridData[p.gridPoint])
    {
      gridData[p.gridPoint] = max_value;
      affectedPoints.add(p.gridPoint);
    }
  }

  for (int i = 1; i < numberHarmonics; ++i)
  {
    const auto y = p.gridPoint.y - i * spacing;
    if (p.gridPoint.x >= 0 && p.gridPoint.x < width && y >= 0 && y < height)
    {
      const float taperAmount = 1.0f - (taperBase * i);
      const float harmonicIntensity = i % 2 == 0 ? evenIntensity_ : oddIntensity_;
      const float value = taperAmount * harmonicIntensity * max_value;
      GridPoint affectedPoint(p.gridPoint.x, y);
      if (value > gridData[affectedPoint])
      {
        gridData[affectedPoint] = value;
        affectedPoints.add(affectedPoint);
      }
    }
  }

  return affectedPoints;
}