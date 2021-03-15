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
  };

}

#endif /* Scale_hpp */
