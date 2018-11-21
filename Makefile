default:
	gcc -g -O3 -Wall -ffast-math -o ripl -lm -lportaudio -lasound -ljack -pthread -llua \
	src/snd/backend/backend.c \
	src/snd/dsp/dummy.c \
	src/snd/dsp/osc.c \
	src/snd/processors/osc.c \
	src/snd/processors/dummy.c \
	src/snd/processors/processor.c \
	src/snd/graph.c \
	src/snd/node.c \
	src/snd/snd.c \
	src/main.c \
	&& ./ripl
