g++ -std=c++11 -I /usr/include -c SerialReceiveBytes.cpp -o SerialReceiveBytes.o
g++ -o serialreceivebytes SerialReceiveBytes.o -lopendavinci -lpthread
