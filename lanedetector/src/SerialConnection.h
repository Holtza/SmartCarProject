#include<iostream>
#include<fstream>
#include<cstdlib>
#include<unistd.h>

using namespace std;

class SerialConnection{
  
    public:
        void write(char const*);
        string read(void);
        SerialConnection();
   // private:

};
