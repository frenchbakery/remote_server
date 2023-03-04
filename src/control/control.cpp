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

// initialize vectors
std::vector<std::shared_ptr<Control::Motor>> Control::motors; 
std::vector<std::shared_ptr<Control::Servo>> Control::servos;
std::vector<std::shared_ptr<Control::Digital>> Control::digitals;
std::vector<std::shared_ptr<Control::Analog>> Control::analogs;


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


/**
 * @brief handle all get requests
 * 
 * @param data input json object
 * @param out output json object
 */
void handle_get(json data, json &out)
{
    std::string request = data["request"];

    // motors
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
            return;
        }

        out["success"] = true;
        out["value"] = Control::motors[port]->getPosition();
    }

    // servos
    else if (request == "servo")
    {
        if (!data.contains("port"))
        {
            out["reason"] = "message doesn't contain \"port\" key";
            return;
        }

        int port = data["port"];
        if (!(0 <= port && port <= 4))
        {
            out["reason"] = "invalid servo port";
            return;
        }

        out["success"] = true;
        out["value"] = Control::servos[port]->position();
    }

    // digitals
    else if (request == "digital")
    {
        if (!data.contains("port"))
        {
            out["reason"] = "message doesn't contain \"port\" key";
            return;
        }

        int port = data["port"];
        if (!(0 <= port && port <= 10))
        {
            out["reason"] = "invalid digital port";
            return;
        }

        out["success"] = true;
        out["value"] = Control::digitals[port]->value();
    }

    // analogs
    else if (request == "analog")
    {
        if (!data.contains("port"))
        {
            out["reason"] = "message doesn't contain \"port\" key";
            return;
        }

        int port = data["port"];
        if (!(0 <= port && port <= 5))
        {
            out["reason"] = "invalid analog port";
            return;
        }

        out["success"] = true;
        out["value"] = Control::analogs[port]->value();

    }

    // undefined
    else
    {
        out["success"] = false;
        out["reason"] = "invalid request type";
    }
}


std::string Control::message_handler(std::string message)
{
    // decode data
    json data = json::parse(message);
    json out = {
        {"success", false},
    };

    std::cout << CLR_BLUE << ":receive:" << CLR_RESET << "  " << data << std::endl;

    // process data
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
            out["success"] = false;
            out["reason"] = "Not implemented yet";
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

    std::cout << CLR_GREEN << ":return:" << CLR_RESET << "  " << out << std::endl;

    return out.dump();
}
