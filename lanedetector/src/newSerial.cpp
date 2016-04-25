#include "SerialConnection.h"
#include <signal.h>
    void sigint_handler(int sig);
    volatile bool STOP = false;

    ofstream output("/dev/ttyACM3");
    ifstream input("/dev/ttyACM3");
    FILE *file;
SerialConnection::SerialConnection(){
    system("stty -F /dev/ttyACM3 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
}

void SerialConnection::write(char const *str){

    file = fopen("/dev/ttyACM3", "w");
    cout << str << endl;
  //  fwrite(str, 1, 1, file);
    fprintf(file, "%s", str);
    fclose(file);
}

string SerialConnection::read(){
    string s = "";
    char voltage;
    while(!input.eof() || voltage == '?'){
        cout << ":)" << endl;
        input>>voltage;
        cout << voltage << endl;
        s += voltage;
    }
    return s;
}

int main(int argc, char** args){
    SerialConnection s;
    char buffer;
    signal(SIGINT, sigint_handler);
    s.write("w");
    while(!STOP){
        std::ifstream file("/root/middleman.txt");
        std::string str; 
        while (std::getline(file, str)){
            const char *cstr = str.c_str();
            if(buffer != *cstr){
                s.write(cstr);
                buffer = *cstr;
            }
        }
        usleep(100000);
    }
    return 0;
}

void sigint_handler(int sig) {
    printf("\nCTRL-C detected\n");
    SerialConnection s;
    s.write("x");
    STOP = true;
}
