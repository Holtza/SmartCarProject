#include "SerialConnection.h"

    ofstream output("/dev/ttyACM0");
    ifstream input("/dev/ttyACM0");
    FILE *file;
SerialConnection::SerialConnection(){
    system("stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
}

void SerialConnection::write(char* str){
    
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

    while(true){
        char result;
        FILE *input = fopen("middleman.txt", "r");
        fread(&result, 1, 1, input);
        cout << result << endl;
        fclose(input);
    }
/*
    SerialConnection s;
    //cout << *args[1] << endl;
  //  while(true){
   //     s.write(args[1]);
    //    s.read();
     //   usleep(100000);
   // }
    s.write("w");
    usleep(1000000);
    s.write("a");
    usleep(500000);
    s.write("d");
    usleep(500000);
    s.write("s");
    usleep(500000);
    s.write("x");
    return 0;
*/
}

