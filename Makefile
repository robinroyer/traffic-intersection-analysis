CC=g++
EXT=cpp

EXEC=Carrefour

CFLAGS=-std=c++11 -O2
LDFLAGS=-L. -L/share/public/tp/tp-multitache -ltp -ltcl8.5 -lncurses -I /share/public/tp/tp-multitache #Remplace -L. par -L{path} ## -I {path} pour rajouter un chemin d'includes

OBJDIR = obj
SRC= $(wildcard *.$(EXT))
HEAD= $(SRC:.$(EXT)=.h)
OBJ= $(SRC:.$(EXT)=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))


.PHONY: all clean clean-all depend

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.$(EXT)
	@mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(LDFLAGS) $(CFLAGS)

clean:
	@echo "Suppression des fichiers objet..."
	@rm -rf $(OBJDIR)
	@echo "Suppression de l'exécutable..."
	@rm -f $(EXEC) core$

depend:
	@makedepend $(SRC) -p$(OBJDIR)/
# DO NOT DELETE

obj/Feux.o: /usr/include/signal.h /usr/include/features.h
obj/Feux.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
obj/Feux.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
obj/Feux.o: /usr/include/gnu/stubs-64.h /usr/include/bits/sigset.h
obj/Feux.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
obj/Feux.o: /usr/include/bits/signum.h /usr/include/time.h
obj/Feux.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
obj/Feux.o: /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h
obj/Feux.o: /usr/include/sys/ucontext.h /usr/include/bits/pthreadtypes.h
obj/Feux.o: /usr/include/bits/sigthread.h /usr/include/sys/sem.h
obj/Feux.o: /usr/include/sys/ipc.h /usr/include/bits/ipctypes.h
obj/Feux.o: /usr/include/bits/ipc.h /usr/include/bits/sem.h
obj/Feux.o: /usr/include/sys/types.h /usr/include/endian.h
obj/Feux.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
obj/Feux.o: /usr/include/sys/select.h /usr/include/bits/select.h
obj/Feux.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
obj/Feux.o: /usr/include/sys/shm.h /usr/include/bits/shm.h
obj/Feux.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
obj/Feux.o: /usr/include/bits/environments.h /usr/include/bits/confname.h
obj/Feux.o: /usr/include/getopt.h Feux.h TMere.h Outils.h
obj/GMenu.o: /usr/include/sys/types.h /usr/include/features.h
obj/GMenu.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
obj/GMenu.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
obj/GMenu.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
obj/GMenu.o: /usr/include/bits/typesizes.h /usr/include/time.h
obj/GMenu.o: /usr/include/endian.h /usr/include/bits/endian.h
obj/GMenu.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
obj/GMenu.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
obj/GMenu.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
obj/GMenu.o: /usr/include/bits/pthreadtypes.h /usr/include/unistd.h
obj/GMenu.o: /usr/include/bits/posix_opt.h /usr/include/bits/environments.h
obj/GMenu.o: /usr/include/bits/confname.h /usr/include/getopt.h
obj/GMenu.o: /usr/include/signal.h /usr/include/bits/signum.h
obj/GMenu.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
obj/GMenu.o: /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h
obj/GMenu.o: /usr/include/sys/ucontext.h /usr/include/bits/sigthread.h
obj/GMenu.o: /usr/include/sys/sem.h /usr/include/sys/ipc.h
obj/GMenu.o: /usr/include/bits/ipctypes.h /usr/include/bits/ipc.h
obj/GMenu.o: /usr/include/bits/sem.h /usr/include/sys/shm.h
obj/GMenu.o: /usr/include/bits/shm.h /usr/include/sys/msg.h
obj/GMenu.o: /usr/include/bits/msq.h /usr/include/sys/wait.h
obj/GMenu.o: /usr/include/sys/resource.h /usr/include/bits/resource.h
obj/GMenu.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
obj/GMenu.o: GMenu.h Outils.h Menu.h Generateur.h Voiture.h TMere.h
obj/TMere.o: /usr/include/signal.h /usr/include/features.h
obj/TMere.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
obj/TMere.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
obj/TMere.o: /usr/include/gnu/stubs-64.h /usr/include/bits/sigset.h
obj/TMere.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
obj/TMere.o: /usr/include/bits/signum.h /usr/include/time.h
obj/TMere.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
obj/TMere.o: /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h
obj/TMere.o: /usr/include/sys/ucontext.h /usr/include/bits/pthreadtypes.h
obj/TMere.o: /usr/include/bits/sigthread.h /usr/include/sys/msg.h
obj/TMere.o: /usr/include/sys/ipc.h /usr/include/bits/ipctypes.h
obj/TMere.o: /usr/include/bits/ipc.h /usr/include/bits/msq.h
obj/TMere.o: /usr/include/sys/shm.h /usr/include/bits/shm.h
obj/TMere.o: /usr/include/sys/sem.h /usr/include/bits/sem.h
obj/TMere.o: /usr/include/sys/types.h /usr/include/endian.h
obj/TMere.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
obj/TMere.o: /usr/include/sys/select.h /usr/include/bits/select.h
obj/TMere.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
obj/TMere.o: /usr/include/sys/wait.h /usr/include/sys/resource.h
obj/TMere.o: /usr/include/bits/resource.h /usr/include/bits/waitflags.h
obj/TMere.o: /usr/include/bits/waitstatus.h /usr/include/unistd.h
obj/TMere.o: /usr/include/bits/posix_opt.h /usr/include/bits/environments.h
obj/TMere.o: /usr/include/bits/confname.h /usr/include/getopt.h Feux.h
obj/TMere.o: GMenu.h Outils.h TMere.h Voie.h Generateur.h Heure.h Menu.h
obj/Voie.o: /usr/include/unistd.h /usr/include/features.h
obj/Voie.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
obj/Voie.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
obj/Voie.o: /usr/include/gnu/stubs-64.h /usr/include/bits/posix_opt.h
obj/Voie.o: /usr/include/bits/environments.h /usr/include/bits/types.h
obj/Voie.o: /usr/include/bits/typesizes.h /usr/include/bits/confname.h
obj/Voie.o: /usr/include/getopt.h /usr/include/sys/ipc.h
obj/Voie.o: /usr/include/bits/ipctypes.h /usr/include/bits/ipc.h
obj/Voie.o: /usr/include/sys/msg.h /usr/include/bits/msq.h
obj/Voie.o: /usr/include/time.h /usr/include/signal.h
obj/Voie.o: /usr/include/bits/sigset.h /usr/include/bits/signum.h
obj/Voie.o: /usr/include/bits/siginfo.h /usr/include/bits/sigaction.h
obj/Voie.o: /usr/include/bits/sigcontext.h /usr/include/bits/sigstack.h
obj/Voie.o: /usr/include/sys/ucontext.h /usr/include/bits/pthreadtypes.h
obj/Voie.o: /usr/include/bits/sigthread.h /usr/include/sys/sem.h
obj/Voie.o: /usr/include/bits/sem.h /usr/include/sys/types.h
obj/Voie.o: /usr/include/endian.h /usr/include/bits/endian.h
obj/Voie.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
obj/Voie.o: /usr/include/bits/select.h /usr/include/bits/time.h
obj/Voie.o: /usr/include/sys/sysmacros.h /usr/include/sys/shm.h
obj/Voie.o: /usr/include/bits/shm.h /usr/include/sys/wait.h
obj/Voie.o: /usr/include/sys/resource.h /usr/include/bits/resource.h
obj/Voie.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
obj/Voie.o: Voie.h Outils.h TMere.h Voiture.h
