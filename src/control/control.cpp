/**
 * @file control.hpp
 * @author Nilusink
 * @version 1.0
 * @date 2023-03-04
 * 
 * @copyright Copyright frenchbakery (c) 2023
 * 
 */
#include <kipr/create/create.h>
#include <nlohmann/json.hpp>
#include "control.hpp"
#include <iostream>
#include <vector>
#include <memory>


using json = nlohmann::json;

// initialize literally everything
std::vector<Control::Motor> Control::motors;
std::vector<Control::Servo> Control::servos;
std::vector<Control::Digital> Control::digitals;
std::vector<Control::Analog> Control::analogs;


void Control::setup()
{
    // initialize motors / servos / digitals / analogs
    for (int i = 0; i <= N_MOTORS; i++)
    {
        motors.emplace_back(std::make_shared<Motor>(i));
    }

    for (int i = 0; i <= N_SERVOS; i++)
    {
        servos.emplace_back(std::make_shared<Servo>(i));
    }

    for (int i = 0; i <= N_DIGITALS; i++)
    {
        digitals.emplace_back(std::make_shared<Digital>(i));
    }

    for (int i = 0; i <= N_ANALOGS; i++)
    {
        analogs.emplace_back(std::make_shared<Analog>(i));
    }
}


void handle_get(json data, json &out)
{
    std::string request = data["request"];
    if (request == "motor")
    {
        if (!data.contains("port"))
        {
            out["reason"] = "message doesn't contain \"port\" key";
            return;
        }

        int port = data["port"];
        if (!(0 <= port && port <= 4))
        {
            out["reason"] = "invalid motor port";
        }

        out["success"] = true;
        out["value"] = Control::motors[port].getPosition();
    }
    else
    {
        out["success"] = false;
        out["reason"] = "invalid request type";
    }
}


std::string Control::message_handler(std::string message)
{
    json data = json::parse(message);
    json out = {
        {"success", false},
    };

    if (data.contains("type"))
    {
        std::string type = data["type"];

        if (type == "get")
        {
            if (!data.contains("request"))
            {
                out["reason"] = "message doesn't contain \"request\" key";
            }
            else
            {
                handle_get(data, out);
            }
        }
        else if (type == "post")
        {
            std::cout << "POST\n";
        }
        else if (type == "NaN")
        {
            std::cout << "tpye not found in data\n";
        }   
    }
    else
    {
        std::cout << "doesn't contain \"type\"\n";
        out["reason"] = "message doesn't contain \"type\" key";
    }

    return out.dump();
}
