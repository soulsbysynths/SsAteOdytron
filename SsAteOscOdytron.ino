#include <AteOdy.h>
#include <AteOdyEngineBase.h>
#include <AteOscHardwareBase.h>
#include <OdyAudio.h>
#include <OdyOscillator.h>
#include <OdyNoise.h>
#include <OdyPatch.h>
#include <SsHelpers.h>
#include <OdyFilter.h>
#include <QuantizePitch.h>
#include <AteOscPitch.h>
#include <OdyPitch.h>
#include <LedRgb.h>
#include <LedCircular.h>
#include <Led.h>
#include <CvInput.h>
#include <Switch.h>
#include <RotaryEncoder.h>

AteOdy odytron;

void setup()
{
  odytron.initialize();
}

void loop()
{
  odytron.poll();
}

