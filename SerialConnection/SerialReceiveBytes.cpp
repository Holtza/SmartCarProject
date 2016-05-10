/**
 * OpenDaVINCI - Tutorial.
 * Copyright (C) 2015 Christian Berger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <memory>
#include <opendavinci/odcore/base/Thread.h>
#include <opendavinci/odcore/wrapper/SerialPort.h>
#include <opendavinci/odcore/wrapper/SerialPortFactory.h>

#include "SerialReceiveBytes.hpp"

#define PACKETLENGTH 20

using namespace std;
using namespace odcore;
using namespace odcore::wrapper;

void serialConnection(std::string SERIAL_PORT, const std::uint32_t BAUD_RATE);

void SerialReceiveBytes::nextString(const string &s) {
    FILE *f;
    f = fopen("/root/serialIn.txt","a");
    //cout << "Received " << s.length() << " bytes containing '" << s << "'" << endl;
    fputs(s.c_str(),f);
    fclose(f);

    std::ifstream t("/root/serialIn.txt");
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());

    while(str.length() > 0 && str[0] != '<'){
        str.erase(0, 1);
    }
    
    //cout << str << endl;
    
    if(str.length() > PACKETLENGTH+2){
        if(str[PACKETLENGTH+1] == '>'){
            std::string dataPacket = str.substr(1, PACKETLENGTH);
            cout << dataPacket << endl;
            FILE *f2;
            f2 = fopen("/root/lastPacket.txt","w");
            fputs(dataPacket.c_str(),f2);
            fclose(f2);
        }
        str = "";
    }    
    f = fopen("/root/serialIn.txt","w");
    fputs(str.c_str(),f);
    fclose(f);
}

// We add some of OpenDaVINCI's namespaces for the sake of readability.


void serialConnection(string SERIAL_PORT, const uint32_t BAUD_RATE){ 
    std::shared_ptr<SerialPort>
    serial(SerialPortFactory::createSerialPort(SERIAL_PORT, BAUD_RATE));

    // This instance will handle any bytes that are received
    // from our serial port.
    SerialReceiveBytes handler;
    serial->setStringListener(&handler);

    // Start receiving bytes.
    serial->start();

    const uint32_t ONE_SECOND = 1000 * 1000;
    while(true)    
        odcore::base::Thread::usleepFor(10 * ONE_SECOND);

    serial-> stop();
}


int32_t main(int32_t argc, char **argv) {
    string SERIAL_PORT = "/dev/ttyACM0";
    const uint32_t BAUD_RATE = 19200;
    try {
        serialConnection(SERIAL_PORT, BAUD_RATE);
    } catch(string &exception) {
        cerr << "Error while creating serial port: " << exception << endl;
        SERIAL_PORT = "/dev/ttyACM1";
        try {
            serialConnection(SERIAL_PORT, BAUD_RATE);
        } catch(string &exception) {
            cerr << "Error on 2nd attempt of serial port: " << exception << endl;
            SERIAL_PORT = "/dev/ttyACM2";
            try {
                serialConnection(SERIAL_PORT, BAUD_RATE);
            } catch(string &exception) {
                cerr << "Error on 3rd attempt of serial port: " << exception << endl;
            }
        }
    }
    // We are using OpenDaVINCI's std::shared_ptr to automatically
    // release any acquired resources.
}

