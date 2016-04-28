#include "SerialConnection.h"
#include <signal.h>
    void sigint_handler(int sig);
    volatile bool STOP = false;

    ofstream output("/dev/ttyACM0");
    ifstream input("/dev/ttyACM0");
<<<<<<< HEAD
    FILE *usbfile;
=======
    FILE *file;
>>>>>>> 7a548e40da4b221cf1f935d13cdaa398b043f4a8
SerialConnection::SerialConnection(){
    system("stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
}

void SerialConnection::write(char const *str){

<<<<<<< HEAD
    usbfile = fopen("/dev/ttyACM0", "w");
    cout << str << endl;
  //  fwrite(str, 1, 1, file);
    fprintf(usbfile, "%s", str);
    fclose(usbfile);
}


int main(){
=======
    file = fopen("/dev/ttyACM0", "w");
    cout << str << endl;
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
>>>>>>> 7a548e40da4b221cf1f935d13cdaa398b043f4a8
    SerialConnection s;
    char buffer;
    signal(SIGINT, sigint_handler);
    s.write("w");
<<<<<<< HEAD
    usleep(2000);
    s.write("w");
    while(!STOP){
        std::ifstream middleman("/root/middleman.txt");
        std::string str; 
        while (std::getline(middleman, str) && !STOP){
=======
    while(!STOP){
        std::ifstream file("/root/middleman.txt");
        std::string str; 
        while (std::getline(file, str)){
>>>>>>> 7a548e40da4b221cf1f935d13cdaa398b043f4a8
            const char *cstr = str.c_str();
            if(buffer != *cstr){
                s.write(cstr);
                buffer = *cstr;
            }
        }
        usleep(100000);
    }
<<<<<<< HEAD
    return 1;
}

void sigint_handler(int sig) {
    if(sig==0)
        printf("\nCTRL-C detected\n");
    else
        printf("\nProgram Exiting\n");
=======
    return 0;
}

void sigint_handler(int sig) {
    printf("\nCTRL-C detected\n");
>>>>>>> 7a548e40da4b221cf1f935d13cdaa398b043f4a8
    SerialConnection s;
    s.write("x");
    STOP = true;
}
