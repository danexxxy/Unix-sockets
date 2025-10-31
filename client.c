#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 9

#define RIGHT 0x01
#define LEFT  0x02
#define DOWN  0x04
#define UP    0x08

uint16_t calc_crc16(const uint8_t *buf, size_t len)
{
    uint16_t crc = 0;
    for(size_t i = 0; i < len-2; ++i) {
        crc += buf[i];
    }

    return crc;
}

uint8_t split_uint16_byte(uint16_t byte)
{
    uint8_t lower = byte & 0xFF;
    uint8_t upper = (byte >> 8) & 0xFF;

    return lower, upper;
}

int main()
{
    int sock;
    struct sockaddr_un addr;

    uint8_t buf[BUF_SEND_SIZE];
    buf[3] = 0x01;

    unsigned int recive_bytes = 0;
    unsigned int nap1б nap2;

    uint16_t horizontal_byte;
    uint16_t CRC16_recive;
    uint16_t CRC16_calc;


    if((ock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_UNIX;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("connect");
        exit(2);
    }

    printf("Вводите напривления движения по вертикали и горизонтали через пробел\n")
    while(1)
    {   
        recv(sock, buf, BUF_SIZE, 0);

        
        if (calc_crc16(buf, BUF_SIZE) == ((buf[9] << 8) | buf[10])){
            

            horizontal_byte = (buf[6] << 8) | buf[5]

            if (scanf("%x %x", &nap1, &nap2) != 2) {
                printf("Ошибка ввода, введите два значения. По горизонтали и вертикали\n");
                continue;
            } 

            switch (nap1){
                case '0x01':
                    horizontal_byte |= 0x01;
                    break;
                
                case '0x02':
                    horizontal_byte |= 0x02;
                    break;
                
                default:
                    printf("Неизвестная команда. Повторите ввод (0x01 - вправо, 0x02 - влево)\n")
                    continue;
            }

            switch (nap2){
                case '0x04':
                    buf[7] |= 0x04;
                    break;

                case '0x08':
                    buf[7] |= 0x08;
                    break;
                
                default:
                    printf("Неизвестная команда. Повторите ввод (0x04 - вниз, 0x08 - вверх)\n")
                    continue;
            }
            
            buf[1] = BUF_SIZE - 3;
            buf[2] = 0xFF - buf[1];
            buf[3] = nap1;
            buf[4] = nap2;
            buf[5], buf[6] = split_uint16_byte(horizontal_byte);
            buf[8], buf[9] = split_uint16_byte(calc_crc16(buf, BUF_SIZE));


            recv(sock, buf, BUF_SIZE, 0);
        }
        else{
            print("Неверный CRC!\n");
        }
    }
}


