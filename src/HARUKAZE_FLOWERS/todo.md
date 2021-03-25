* flower 

three states:
  0 sleeping
  1 calling
  2 active
  3 explosion

LED animation:

state animation:
  0: sleeping
    ***
  1: calling: 
    visualize midi notes in a specific color doing fade in - fade out(increasing brightness)
  2: active
    visualize activation with brightness
    visualize solenoid notes
    visualize midi notes
    visualize touch activation with ring section (?)
  3: explosion
    ***





Functionallity

1. the tree is waiting (flower on state 0)
2. the tree sends a call message to the flower (flower state 1)
  the call can be send physically (by pressing a button)
  the midi instrument is assigned randomly to the call 

3. the flower starts playing a midi track, and visualizing a call (flower state 1)
3.1 if nobody touches the flower, the midi track stops after a time has passed
3.2 if someone touches the flower
  1. the flower goes into active state 2 (flower state 2)
  2. the branch starts playing a solenoid track that shadows the midi track, with amount of notes depending on the activation level
  3. if the IMU is used, there are retrig effects and modulation
  4. the complexity of the midi melody changes everytime someone touches the flower following a sine wave
  5. when nobody touches the flower, the midi complexity remains constant
  6. when nobody touches the flower, the activation level goes back to zero gradually, and thus, the solenoid also stop
  7. when nobody touches the flower, the counter for the midi melody to stop starts
  8. when touching the flower, if an activation threshold is surpassed, the flower goes to sleep and the tracks stop 

4 There is a rock to change the bpm
  the bpom changes with an encoder
  there is an animation that represetns the BPM with a ring

5 Tree
  the tree creates midi tracks and assign them to the flower, picking an instrument from a pool
  there are maximum 5 instruments at the same time (one per flower)
  instrument types are not repeated
  there is no percussion instruments

6 refactoring the track
  one track is a sum of sequences and one instrument channel
  one sequence has different states composed by (n steps, n events, offset, retrig, etc) 
  each sequence has a range of possible values for each paremeter
  there is a function to assign random values from the range
  the ranges are hardcoded per type of instruments

7 branch
  a branch is a gorup of three solenoids
  the branch plays an euclidean sequence shadowing a midi sequence
  the amount of notes being played depends on the activation
  each note is sent to a different solenoid in the branch
    either random
    or rotating