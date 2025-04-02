#ifndef UARTPROTOCOL_H
#define UARTPROTOCOL_H

#include <iostream>
#include <iomanip>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <cstdint>

struct ProtocolConfig
{
    std::string portName = "/dev/ttyUSB0"; // Change as needed
    speed_t baudRate = B115200;
    tcflag_t byteSize = CS8;
    uint8_t stopBits = 1;
    uint8_t parity = 0;
    uint8_t header = 0xAA;
    uint8_t maxPacketSize = 100;
};

class UARTProtocol
{
private:
    int serialFd;
    ProtocolConfig config;

public:
    UARTProtocol(const ProtocolConfig &config);
    ~UARTProtocol();
    /**
     * @brief Initializes the UART protocol with the specified configuration.
     * @return Returns true if the initialization is successful, false otherwise.
     */
    bool begin();
    /**
     * @brief Sends a command over UART.
     * @param command The command byte to be transmitted.
     */
    void sendCommand(uint8_t command);
    /**
     * @brief Sends a command over UART.
     * @param command The data byte to be transmitted.
     * @param length The length of the data to be trasmitted.
     */
    void sendData(const uint8_t *data, size_t length);
};

#endif // UARTPROTOCOL_Hz