default:
	gcc -g -o ripl -lm -lportaudio -lasound -ljack -pthread \
	src/backend/backend.c \
	src/nodes/node.c \
	src/nodes/synth.c \
	src/ripl.c \
	main.c \
	&& ./ripl
