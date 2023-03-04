/**
 * @file server.hpp
 * @author Nilusink
 * @version 1.0
 * @date 2023-03-04
 * 
 * @copyright Copyright frenchbakery (c) 2023
 * 
 */
#include "server.hpp"

#include <websocketpp/message_buffer/message.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "term_colors.h"
#include <iostream>


using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;


// Create a server endpoint
Server::server Server::c_server;


void on_message(Server::server* s, websocketpp::connection_hdl hdl, Server::server::message_ptr msg, Server::callback_func_t func)
{
    std::string ret = func(msg->get_payload());

    // check for a special command to instruct the server to stop listening so
    // it can be cleanly exited.
    if (msg->get_payload() == "stop-listening") {
        s->stop_listening();
        return;
    }

    try {
        s->send(hdl, ret, msg->get_opcode());
    } catch (websocketpp::exception const & e) {
        std::cout << CLR_RED << "Failed because: "
                  << "(" << e.what() << ")" << CLR_RESET << std::endl;
    }
}


void Server::setup(unsigned int port, callback_func_t callback_func)
{
    try
    {
        // Set logging settings
        // we don't want any websocketpp log messages
        c_server.clear_access_channels(websocketpp::log::alevel::all);
        c_server.clear_error_channels(websocketpp::log::elevel::all);

        // Initialize Asio
        c_server.init_asio();

        // Register our message handler
        c_server.set_message_handler(bind(&on_message,&c_server,::_1,::_2, callback_func));

        // Listen on port 9002
        c_server.listen(port);

        // set reuse addr flag to allow faster restart times
        c_server.set_reuse_addr(true);
    }
    catch (websocketpp::exception const & e)
    {
        std::cout << CLR_RED << e.what() << CLR_RESET << std::endl;
    }
    catch (...)
    {
        std::cout << CLR_RED << "other exception" << CLR_RESET << std::endl;
    }
}


void Server::run()
{
    for (;;)
    {
        try
        {
            c_server.start_accept();

            // Start the ASIO io_service run loop
            std::cout << "starting server\n";
            c_server.run();
        }
        catch (websocketpp::exception const & e)
        {
            std::cout << CLR_RED << "error\n";
            std::cout << e.what() << CLR_RESET << std::endl;
            return;
        }
        catch (...)
        {
            std::cout << CLR_RED << "other exception" << CLR_RESET << std::endl;
            continue;
        }
    }
}
