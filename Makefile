default:
	gcc -g -O3 -ffast-math -o ripl -lm -lportaudio -lasound -ljack -pthread \
	src/backend/backend.c \
	src/dsp/dummy.c \
	src/dsp/osc.c \
	src/processors/osc.c \
	src/processors/dummy.c \
	src/processors/processor.c \
	src/graph.c \
	src/node.c \
	src/ripl.c \
	main.c \
	&& ./ripl
