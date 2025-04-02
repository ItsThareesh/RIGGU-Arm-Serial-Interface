#include "UARTProtocol.hpp"
#include <iostream>
#include <stdint.h>

using namespace std;

int main()
{
    ProtocolConfig config = {
        .portName = "/dev/cu.usbserial-1140",
    };

    UARTProtocol protocol(config);

    if (protocol.begin())
    {
        int command = 0;
        int degrees[3];

        while (1)
        {
            cout << "Enter Command: ";
            cin >> command;

            cout << "Enter First Angle: ";
            cin >> degrees[0];

            cout << "Enter Second Angle: ";
            cin >> degrees[1];

            cout << "Enter Third Angle: ";
            cin >> degrees[2];

            protocol.sendCommand(uint8_t(command));

            uint8_t degrees_bytes[3] = {static_cast<uint8_t>(degrees[0]),
                                        static_cast<uint8_t>(degrees[1]),
                                        static_cast<uint8_t>(degrees[2])};

            protocol.sendData(degrees_bytes, 3);
        }
    }
}
