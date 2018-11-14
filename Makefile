default:
	gcc -g -o ripl -lm -lportaudio -lasound -ljack -pthread \
	src/backend/backend.c \
	src/processors/processor.c \
	src/processors/dummy/dummy.c \
	src/processors/osc/osc.c \
	src/graph.c \
	src/node.c \
	src/ripl.c \
	main.c \
	&& ./ripl
