CXX=g++
CXX_FLAGS=-std=c++17 -Iincludes -Idist
exec: bin/exec
socket: bin/socket
JSON=-ljsoncpp
bin/exec: src/main.cc src/Calculator.cc src/Recipe.cc src/ItemGraph.cc src/ItemNode.cc src/Preprocess.cc dist/jsoncpp.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@
bin/socket: src/socket.cc src/Calculator.cc src/Recipe.cc src/ItemGraph.cc src/ItemNode.cc src/Preprocess.cc dist/jsoncpp.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@
.DEFAULT_GOAL := exec
.PHONY: exec clean socket

clean:
	rm -f bin/*
