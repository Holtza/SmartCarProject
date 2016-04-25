#include "SerialConnection.h"
#include <signal.h>

using namespace std;

    void sigint_handler(int sig);
    volatile bool STOP = false;

    ofstream output("/dev/ttyACM0");
    ifstream input("/dev/ttyACM0");
    FILE *file;
SerialConnection::SerialConnection(){
    system("stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
}

void SerialConnection::write(char const *str){

    file = fopen("/dev/ttyACM0", "w");
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

int main(){
    SerialConnection s;
    char buffer;
    signal(SIGINT, sigint_handler);
    s.write("w");
    while(!STOP){
        std::ifstream sFile("/root/middleman.txt");
        std::string str; 
        while (std::getline(sFile, str)){
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

    if(sig != 0){
        printf("Unknown error code");
    }
}
