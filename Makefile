default:
	gcc -o ripl -lportaudio -lasound -ljack -pthread \
	src/mixer.c \
	src/backend/backend.c \
	src/state.c \
	src/module.c \
	src/dsp/synth.c \
	main.c \
	&& ./ripl
