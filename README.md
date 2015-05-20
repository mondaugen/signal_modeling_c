signal_modeling_c

signal modeling routines in C

rlspykas
--------

An example command line that does analysis and synthesis. Requires nthbyte
sox ~/Music/beach_boys-pet_sounds_sessions/disc3/track01.cdda.wav \
    -t f64 -c 1 -r 44100 - | \
    bin/rlspykas 10 0.9999 1 | \
    nthbyte 88 80 8 | \
    bin/rlspykas 10 0.9999 0 | \
    nthbyte 88 80 8 | \
    sox -t f64 -c 1 -r 44100 - -d
