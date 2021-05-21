#ifndef Scale_hpp
#define Scale_hpp

#include <vector>
#include "MusicTheory.hpp"

namespace MusicTheory
{

  class Scale
  {
  public:
    Scale(Interval *intervals, int length);
    int length;
    std::vector<Interval> intervals;
    std::vector<Note> getNotes(NoteType key, int octave);
    Note getNote(NoteType key, int noteInx, int octave = 2);

    const static Scale major;
    const static Scale minor;
    const static Scale majorPentatonic;
    const static Scale minorPentatonic;
    const static Scale custom1;
    const static Scale custom2;
  };

}

#endif /* Scale_hpp */
