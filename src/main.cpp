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
        int degree = 0;

        while (1)
        {
            cout << "Enter Command: ";
            cin >> command;

            cout << "Enter Int Data: ";
            cin >> degree;

            protocol.sendCommand(uint8_t(command));
            protocol.sendData((uint8_t *)(&degree), 1);
        }
    }
}
