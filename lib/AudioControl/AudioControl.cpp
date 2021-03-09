#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioInputI2S i2s1;            //xy=356,458
AudioOutputI2S i2s2;           //xy=867,361
AudioAnalyzeFFT1024 fft1024_1; //xy=746,538
AudioConnection patchCord1(i2s1, 0, fft1024_1, 0);
AudioConnection patchCord2(i2s1, 0, i2s2, 0);
AudioConnection patchCord3(i2s1, 1, i2s2, 1);
AudioControlSGTL5000 sgtl5000_1; //xy=736,779

#include "AudioControl.h"

#include <AudioMessages.h>

namespace HLAudioControl
{

  void AudioControl::begin()
  {
    AudioMemory(160);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.7);

    sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
    // sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);

    sgtl5000_1.micGain(10); // from 0db to 63db
    sgtl5000_1.lineInLevel(0);
  }

  void AudioControl::update()
  {
    if (!delegate)
    {
      return;
    }
    if (fft1024_1.available())
    {
      AudioSignalsMsg msg;
      msg.lowBand = fft1024_1.read(4, 10);
      msg.midBand = fft1024_1.read(11, 80);
      msg.hiBand = fft1024_1.read(81, 500);
      delegate->audioControlReceiveMsg(&msg);
    }
  }

} // namespace HLAudioControl
