#include <iostream>
#include <string>
#include <iomanip>
#include <socket>

int     main(int ac, char** av) {
    int     server_fd;

    if (ac != 2) {
        std::cerr << "Please try: ./WebServer <something path>" << std::endl;
        return 0;
    }

    /* открываем сокет для нашей системы
     * A socket is the mechanism that most popular operating systems provide to give programs access to the network.
     * It allows messages to be sent and received between applications (unrelated processes) on different networked machines.
     */
    try {
        if ((server_fd = socket(AF_NET, SOCK_STREAM, 0)) < 0) {
            std::cerr << "Can`t create socket" << std::endl;
            return 0;
        }
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}