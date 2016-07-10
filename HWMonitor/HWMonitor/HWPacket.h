#ifndef HWPACKET_H
#define HWPACKET_H

typedef int hwpacket_t;

#define MODULES_VALUE_COUNT     32
#define MODULES_COUNT           32
struct LinPackModule{
    int  name;
    char type;
    char mode;
    char io_values_count;
    char modify;
    short int value[MODULES_VALUE_COUNT];
};
struct HWPacketHeader
{
    hwpacket_t cmd;
    hwpacket_t res;
    hwpacket_t host_id;
    hwpacket_t local_id;
    hwpacket_t modules_count;
};

struct HWPacketData
{
    LinPackModule modules[MODULES_COUNT];
};

struct HWPacket
{
    HWPacketHeader  Header;
    HWPacketData    Data;
};

#endif // HWPACKET_H
