default:
	gcc -g -o ripl -lm -lportaudio -lasound -ljack -pthread \
	src/backend/backend.c \
	src/modules/module.c \
	src/modules/synth.c \
	src/ripl.c \
	main.c \
	&& ./ripl
