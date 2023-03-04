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


using json = nlohmann::json;

// initialize literally everything
Control::Motor Control::motor0(0);
Control::Motor Control::motor1(1);
Control::Motor Control::motor2(2);
Control::Motor Control::motor3(3);
const std::vector<Control::Motor> Control::motors
{
    motor0,
    motor1,
    motor2,
    motor3
};

// const std::vector<Control::Servo> Control::servos
// {{0}, {1}, {2}, {3}};

// const std::vector<Control::Digital> Control::digitals
// {{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}};

// const std::vector<Control::Analog> Control::analogs
// {{0}, {1}, {2}, {3}, {4}};


void Control::setup()
{}


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
