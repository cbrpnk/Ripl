#ifndef SND_MIDI_H
#define SND_MIDI_H

#include <math.h>

// Transforms a midi note into its corresponding frequency
#define SND_MIDI_TO_FREQ(m) 440 * pow(2,(((m)-69)/12))

// Note to MIDI note number

#define SND_C1  0
#define SND_Db1 1
#define SND_D1  2
#define SND_Eb1 3
#define SND_E1  4
#define SND_F1  5
#define SND_Gb1 6
#define SND_G1  7
#define SND_Ab1 8
#define SND_A1  9
#define SND_Bb1 10
#define SND_B1  11

#define SND_C2  12
#define SND_Db2 13
#define SND_D2  14
#define SND_Eb2 15
#define SND_E2  16
#define SND_F2  17
#define SND_Gb2 18
#define SND_G2  19
#define SND_Ab2 20
#define SND_A2  21
#define SND_Bb2 22
#define SND_B2  23

#define SND_C3  24
#define SND_Db3 25
#define SND_D3  26
#define SND_Eb3 27
#define SND_E3  28
#define SND_F3  29
#define SND_Gb3 30
#define SND_G3  31
#define SND_Ab3 32
#define SND_A3  33
#define SND_Bb3 34
#define SND_B3  35

#define SND_C4  36
#define SND_Db4 37
#define SND_D4  38
#define SND_Eb4 39
#define SND_E4  40
#define SND_F4  41
#define SND_Gb4 42
#define SND_G4  43
#define SND_Ab4 44
#define SND_A4  45
#define SND_Bb4 46
#define SND_B4  47

#define SND_C5  48
#define SND_Db5 49
#define SND_D5  50
#define SND_Eb5 51
#define SND_E5  52
#define SND_F5  53
#define SND_Gb5 54
#define SND_G5  55
#define SND_Ab5 56
#define SND_A5  57
#define SND_Bb5 58
#define SND_B5  59

#define SND_C6  60
#define SND_Db6 61
#define SND_D6  62
#define SND_Eb6 63
#define SND_E6  64
#define SND_F6  65
#define SND_Gb6 66
#define SND_G6  67
#define SND_Ab6 68
#define SND_A6  69
#define SND_Bb6 70
#define SND_B6  71

#define SND_C7  72
#define SND_Db7 73
#define SND_D7  74
#define SND_Eb7 75
#define SND_E7  76
#define SND_F7  77
#define SND_Gb7 78
#define SND_G7  79
#define SND_Ab7 80
#define SND_A7  81
#define SND_Bb7 82
#define SND_B7  83

#define SND_C8  84
#define SND_Db8 85
#define SND_D8  86
#define SND_Eb8 87
#define SND_E8  88
#define SND_F8  89
#define SND_Gb8 90
#define SND_G8  91
#define SND_Ab8 92
#define SND_A8  93
#define SND_Bb8 94
#define SND_B8  95

#define SND_C9  96
#define SND_Db9 97
#define SND_D9  98
#define SND_Eb9 99
#define SND_E9  100
#define SND_F9  101
#define SND_Gb9 102
#define SND_G9  103
#define SND_Ab9 104
#define SND_A9  105
#define SND_Bb9 106
#define SND_B9  107

#define SND_C10  108
#define SND_Db10 109
#define SND_D10  110
#define SND_Eb10 111
#define SND_E10  112
#define SND_F10  113
#define SND_Gb10 114
#define SND_G10  115
#define SND_Ab10 116
#define SND_A10  117
#define SND_Bb10 118
#define SND_B10  119

#define SND_C11  120
#define SND_Db11 121
#define SND_D11  122
#define SND_Eb11 123
#define SND_E11  124
#define SND_F11  125
#define SND_Gb11 126
#define SND_G11  127

#endif
