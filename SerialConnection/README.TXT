g++ -std=c++11 -I /usr/include -c SerialSendBytes.cpp -o SerialSendBytes.o
g++ -o serialsendbytes SerialSendBytes.o -lopendavinci -lpthread
