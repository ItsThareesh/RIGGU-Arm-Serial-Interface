#include "UARTProtocol.hpp"

UARTProtocol::UARTProtocol(const ProtocolConfig &cfg) : config(cfg), serialFd(-1) {}

UARTProtocol::~UARTProtocol()
{
    if (serialFd != -1)
    {
        close(serialFd);
    }
}

bool UARTProtocol::begin()
{
    serialFd = open(config.portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (serialFd == -1)
    {
        perror("Error opening serial port");
        return false;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(serialFd, &tty) != 0)
    {
        perror("Error getting serial port attributes");
        return false;
    }

    cfsetispeed(&tty, config.baudRate);
    cfsetospeed(&tty, config.baudRate);

    tty.c_cflag = config.baudRate | CS8 | CLOCAL | CREAD;
    tty.c_iflag = IGNPAR;
    tty.c_oflag = 0;
    tty.c_lflag = 0;

    if (config.stopBits == 2)
    {
        tty.c_cflag |= CSTOPB;
    }
    else
    {
        tty.c_cflag &= ~CSTOPB;
    }

    if (config.parity)
    {
        tty.c_cflag |= PARENB;
    }
    else
    {
        tty.c_cflag &= ~PARENB;
    }

    tcflush(serialFd, TCIFLUSH);
    if (tcsetattr(serialFd, TCSANOW, &tty) != 0)
    {
        perror("Error setting serial port attributes");
        return false;
    }

    return true;
}

void UARTProtocol::sendCommand(uint8_t command)
{
    uint8_t commandArr[2] = {config.header, command};
    write(serialFd, commandArr, 2);
    tcflush(serialFd, TCIFLUSH);
}

void UARTProtocol::sendData(const uint8_t *data, size_t length)
{
    write(serialFd, data, length);
}