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

    protocol.begin();

    int command;
    int degree;

    while (1)
    {
        cout << "Enter Command: ";
        cin >> command;

        cout << "Enter Int Data: ";
        cin >> degree;

        fflush(stdin);

        protocol.sendCommand(uint8_t(command));
        protocol.sendData((uint8_t *)(&degree), 1);
    }
}
