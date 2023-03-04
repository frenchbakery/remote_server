/**
 * @file main.cpp
 * @author Nilusink
 * @brief runs the server
 * @version 1.0
 * @date 2023-03-04
 * 
 * @copyright Copyright frenchbakery (c) 2023
 * 
 */

#include "server/server.hpp"
#include "control/control.hpp"
#include <kipr/time/time.h>

#define PORT 9999


int main()
{
    Control::setup();
    Server::setup(PORT, Control::message_handler);

    Server::run();
}
