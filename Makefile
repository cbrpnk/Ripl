default:
	gcc -o ripl -lportaudio -lasound -ljack -pthread \
	src/mixer.c \
	src/backend/backend.c \
	src/state.c \
	src/modules/module.c \
	src/modules/synth.c \
	main.c \
	&& ./ripl
