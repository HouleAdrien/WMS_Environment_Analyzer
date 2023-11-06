########################################
#~ définitions
########################################

# Executables à générer
BIN=main

# liste des fichiers sources 
SRCS0=main.cpp
SRCS1=sources/ImageBase.cpp
SRCS2=sources/KMeansAnalyser.cpp

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

obj/%.o: %.c
	gcc -Wall -Iinclude -c $< -o $@

main: $(SRCS0:%.c=obj/%.o) $(SRCS1:%.c=obj/%.o)  $(SRCS2:%.c=obj/%.o)
	g++ -o $@ $+

clean:
	rm -f $(BIN) obj/*.o *~
