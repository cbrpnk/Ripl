#ifndef RIPL_MIDI_H
#define RIPL_MIDI_H

#include <math.h>

// Transforms a midi note into its corresponding frequency
#define RIPL_MIDI_TO_FREQ(m) 440 * pow(2,(((m)-69)/12))

// Note to MIDI note number

#define RIPL_C1  0
#define RIPL_Db1 1
#define RIPL_D1  2
#define RIPL_Eb1 3
#define RIPL_E1  4
#define RIPL_F1  5
#define RIPL_Gb1 6
#define RIPL_G1  7
#define RIPL_Ab1 8
#define RIPL_A1  9
#define RIPL_Bb1 10
#define RIPL_B1  11

#define RIPL_C2  12
#define RIPL_Db2 13
#define RIPL_D2  14
#define RIPL_Eb2 15
#define RIPL_E2  16
#define RIPL_F2  17
#define RIPL_Gb2 18
#define RIPL_G2  19
#define RIPL_Ab2 20
#define RIPL_A2  21
#define RIPL_Bb2 22
#define RIPL_B2  23

#define RIPL_C3  24
#define RIPL_Db3 25
#define RIPL_D3  26
#define RIPL_Eb3 27
#define RIPL_E3  28
#define RIPL_F3  29
#define RIPL_Gb3 30
#define RIPL_G3  31
#define RIPL_Ab3 32
#define RIPL_A3  33
#define RIPL_Bb3 34
#define RIPL_B3  35

#define RIPL_C4  36
#define RIPL_Db4 37
#define RIPL_D4  38
#define RIPL_Eb4 39
#define RIPL_E4  40
#define RIPL_F4  41
#define RIPL_Gb4 42
#define RIPL_G4  43
#define RIPL_Ab4 44
#define RIPL_A4  45
#define RIPL_Bb4 46
#define RIPL_B4  47

#define RIPL_C5  48
#define RIPL_Db5 49
#define RIPL_D5  50
#define RIPL_Eb5 51
#define RIPL_E5  52
#define RIPL_F5  53
#define RIPL_Gb5 54
#define RIPL_G5  55
#define RIPL_Ab5 56
#define RIPL_A5  57
#define RIPL_Bb5 58
#define RIPL_B5  59

#define RIPL_C6  60
#define RIPL_Db6 61
#define RIPL_D6  62
#define RIPL_Eb6 63
#define RIPL_E6  64
#define RIPL_F6  65
#define RIPL_Gb6 66
#define RIPL_G6  67
#define RIPL_Ab6 68
#define RIPL_A6  69
#define RIPL_Bb6 70
#define RIPL_B6  71

#define RIPL_C7  72
#define RIPL_Db7 73
#define RIPL_D7  74
#define RIPL_Eb7 75
#define RIPL_E7  76
#define RIPL_F7  77
#define RIPL_Gb7 78
#define RIPL_G7  79
#define RIPL_Ab7 80
#define RIPL_A7  81
#define RIPL_Bb7 82
#define RIPL_B7  83

#define RIPL_C8  84
#define RIPL_Db8 85
#define RIPL_D8  86
#define RIPL_Eb8 87
#define RIPL_E8  88
#define RIPL_F8  89
#define RIPL_Gb8 90
#define RIPL_G8  91
#define RIPL_Ab8 92
#define RIPL_A8  93
#define RIPL_Bb8 94
#define RIPL_B8  95

#define RIPL_C9  96
#define RIPL_Db9 97
#define RIPL_D9  98
#define RIPL_Eb9 99
#define RIPL_E9  100
#define RIPL_F9  101
#define RIPL_Gb9 102
#define RIPL_G9  103
#define RIPL_Ab9 104
#define RIPL_A9  105
#define RIPL_Bb9 106
#define RIPL_B9  107

#define RIPL_C10  108
#define RIPL_Db10 109
#define RIPL_D10  110
#define RIPL_Eb10 111
#define RIPL_E10  112
#define RIPL_F10  113
#define RIPL_Gb10 114
#define RIPL_G10  115
#define RIPL_Ab10 116
#define RIPL_A10  117
#define RIPL_Bb10 118
#define RIPL_B10  119

#define RIPL_C11  120
#define RIPL_Db11 121
#define RIPL_D11  122
#define RIPL_Eb11 123
#define RIPL_E11  124
#define RIPL_F11  125
#define RIPL_Gb11 126
#define RIPL_G11  127

#endif
