#include <opendavinci/odcore/io/StringListener.h>
#include <string>
#include <cstring>
#include <stdio.h>

// This class will handle the bytes received via a serial link.
class SerialReceive : public odcore::io::StringListener {

    // Your class needs to implement the method void nextString(const std::string &s).
    virtual void nextString(const std::string &s);
};