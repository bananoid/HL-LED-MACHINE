#pragma once
#include <AudioMessages.h>

using namespace Messages;

namespace HLAudioControl
{

  class AudioControlDelegate
  {
  public:
    virtual void audioControlReceiveMsg(AudioSignalsMsg *message);
  };

  class AudioControl
  {
  private:
  public:
    AudioControlDelegate *delegate;
    void begin();
    void update();
  };

} // namespace HLAudioControl
