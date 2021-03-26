#pragma once
class AudioAnalyzerDelegate
{
public:
  virtual void audioAnalyzerOnBandsUpdate(float bandLowVal, float bandMidVal, float bandHighVal);
};

class AudioAnalyzer
{
private:
public:
  float bandLowVal = 0;
  float bandMidVal = 0;
  float bandHighVal = 0;

  AudioAnalyzerDelegate *delegate = nullptr;

  void begin(AudioAnalyzerDelegate *delegate);
  void update();
};

extern AudioAnalyzer *AudioAnalyzerSingleton;
