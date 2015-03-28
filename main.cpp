#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

int main()
{
    sf::Time timeout = sf::seconds(7.0f);
    
//    sf::IpAddress ip = sf::IpAddress::getPublicAddress(timeout);
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    char connectionType, mode;
    char buffer[2000];
    std::size_t received;
    std::string text = "Connected to: ";
    
    std::cout << ip.toString() << '\n';
    
    
    std::cout << "Enter (s) for Server, Enter (c) for client" << '\n';
    std::cin >> connectionType;
    
    if (connectionType == 's')
    {
        sf::TcpListener listener;
        listener.listen(54000);
        listener.accept(socket);
        text += "Server";
        mode = 's';
    }
    else if (connectionType == 'c')
    {
        socket.connect(ip, 54000);
        text += "Client";
        mode = 'r';
    }
    socket.send(text.c_str(), text.length() + 1);
    
    socket.receive(buffer, sizeof(buffer), received);
    
    std::cout << buffer << std::endl;
    
    bool done = false;
    
    while (!done)
    {
        if (mode == 's')
        {
            std::getline(std::cin, text);
            socket.send(text.c_str(), text.length() + 1);
            mode = 'r';
        }
        else if (mode == 'r')
        {
            socket.receive(buffer, sizeof(buffer), received);
            if (received > 0)
            {
                std::cout << "Received: " << buffer << '\n';
                mode = 's';
            }
        }
    }
    
    return 0;
}