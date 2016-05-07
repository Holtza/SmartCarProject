#include "newSerial.h"
#include <signal.h>
    void sigint_handler(int sig);
    volatile bool STOP = false;

    ofstream output("/dev/ttyACM1");
    ifstream input("/dev/ttyACM1");
    FILE *usbfile;
SerialConnection::SerialConnection(){
    system("stty -F /dev/ttyACM1 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
}

void SerialConnection::write(char const *str){

    usbfile = fopen("/dev/ttyACM1", "w");
    cout << str << endl;
  //  fwrite(str, 1, 1, file);
    fprintf(usbfile, "%s", str);
    fclose(usbfile);
}


int main(){
    SerialConnection s;
    char buffer;
    signal(SIGINT, sigint_handler);
    usleep(2000000);
    s.write("w");
    //usleep(2000);
    //s.write("w");
    while(!STOP){
        std::ifstream middleman("/root/middleman.txt");
        std::string str; 
        while (std::getline(middleman, str) && !STOP){
            const char *cstr = str.c_str();
            if(buffer != *cstr){
                s.write(cstr);
                buffer = *cstr;
            }
        }
        usleep(100000);
    }
    return 1;
}

void sigint_handler(int sig) {
    if(sig==0)
        printf("\nCTRL-C detected\n");
    else
        printf("\nProgram Exiting\n");
    SerialConnection s;
    s.write("x");
    STOP = true;
}
