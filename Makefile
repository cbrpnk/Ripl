default:
	gcc -o ripl -lportaudio -lasound -ljack -pthread \
	src/backend/backend.c \
	src/dsp/synth.c \
	src/modules/module.c \
	src/modules/synth.c \
	src/mixer.c \
	src/ripl.c \
	main.c \
	&& ./ripl
