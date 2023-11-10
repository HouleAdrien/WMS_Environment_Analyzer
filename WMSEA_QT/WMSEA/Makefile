########################################
#~ définitions
########################################

# Executables à générer
BIN=main

# liste des fichiers sources 
SRCS0=main.cpp
IMAGE=sources/ImageBase.cpp
KMEAN=sources/KMeansAnalyser.cpp

default: $(BIN)

########################################
#~ regles pour l'executable
########################################

%.o: %.cpp
	gcc -Wall -Iinclude -c $< -o $@

main: $(SRCS0:%.cpp=%.o) $(IMAGE:%.cpp=%.o)  $(KMEAN:%.cpp=%.o)
	g++ -o $@ $+

clean:
	rm -f $(BIN) *.o *~
