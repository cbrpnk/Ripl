default:
	gcc -g -o ripl -lm -lportaudio -lasound -ljack -pthread \
	src/backend/backend.c \
	src/graph/graph.c \
	src/graph/node.c \
	src/graph/dummy/dummy.c \
	src/graph/synth/synth.c \
	src/ripl.c \
	main.c \
	&& ./ripl
