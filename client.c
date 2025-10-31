#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUF_SIZE 9

#define RIGHT 0x01
#define LEFT  0x02
#define DOWN  0x04
#define UP    0x08

int main()
{
    int sock;
    struct sockaddr_un addr;

    uint8_t buf[BUF_SEND_SIZE];

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

        for(size_t i = 0; i < BUF_SIZE-2; ++i) {
            CRC16_calc += buf[i];
        }
         
        if (CRC16_calc == (CRC16_recive = (buf[9] << 8) | buf[10])){
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

            buf[5] = horizontal_byte & 0xFF;
            buf[6] = (horizontal_byte >> 8) & 0xFF;


            recv(sock, buf, BUF_SIZE, 0);
        }
        else{
            print("Не верный CRC!\n");
        }
    }
}


