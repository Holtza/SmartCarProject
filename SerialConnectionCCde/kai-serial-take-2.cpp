#include<iostream>
#include<fstream>
#include<cstdlib>

#define PORT "/dev/ttyACM0"

using namespace std;

int main()
{
    system("stty -F /dev/ttyACM0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts");
    FILE *file;

    ifstream Arduino_Input("/dev/ttyACM0");
    ofstream Arduino_Output("/dev/ttyACM0");
    char Voltage;
    long int Time = time(NULL);
    int i= 0;
    while(time(NULL)-Time < 5){}
    while(true)
    {
        Time = time(NULL);
        while(time(NULL)-Time < 1){}
        while(!Arduino_Input.eof())
        {
            Arduino_Input >> Voltage;
            if(Voltage == '?')cout << endl;
            else cout << Voltage;
            i++;
          //  cout << "---" << endl;
            file = fopen(PORT, "w");
            if(i>100)fprintf(file,"a");
            else fprintf(file,"d");
            fclose(file);
        }
        Arduino_Input.clear();
    }

    Arduino_Input.close();
    return(0);
}
