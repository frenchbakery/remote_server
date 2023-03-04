/**
 * @file server.hpp
 * @author Nilusink
 * @brief defines the websocket interface
 * @version 1.0
 * @date 2023-03-04
 * 
 * @copyright Copyright frenchbakery (c) 2023
 * 
 */
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#pragma once


namespace Server
{
    typedef std::function<std::string (std::string)> callback_func_t;
    typedef websocketpp::server<websocketpp::config::asio> server;
    extern server c_server;

    void setup(unsigned int port, callback_func_t callback_func);
    void run();
}
