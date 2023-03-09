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
#include "term_colors.h"
#include "control.hpp"
#include <iostream>
#include <vector>
#include <memory>


using json = nlohmann::json;

// initialize vectors
std::vector<std::shared_ptr<Control::Motor>> Control::motors; 
std::vector<std::shared_ptr<Control::CMotor>> Control::cmotors; 
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
    
    for (int i = 0; i <= N_CMOTORS; i++)
    {
        cmotors.emplace_back(std::make_shared<CMotor>(i));
        cmotors[i]->disablePositionControl();
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
    std::string request = data.at("request");

    // motors
    if (request == "motor")
    {
        if (!data.contains("port"))
        {
            out["success"] = false;
            out["reason"] = "message doesn't contain \"port\" key";
            return;
        }

        int port = data.at("port");
        if (!(0 <= port && port <= 4))
        {
            out["success"] = false;
            out["reason"] = "invalid motor port";
            return;
        }

        out["success"] = true;
        out["value"] = Control::motors[port]->getPosition();
    }

    // servos
    else if (request == "servo_pos")
    {
        if (!data.contains("port"))
        {
            out["success"] = false;
            out["reason"] = "message doesn't contain \"port\" key";
            return;
        }

        int port = data.at("port");
        if (!(0 <= port && port <= 4))
        {
            out["success"] = false;
            out["reason"] = "invalid servo port";
            return;
        }

        out["success"] = true;
        out["value"] = Control::servos[port]->position();
    }
    else if (request == "servo_enabled")
    {
        if (!data.contains("port"))
        {
            out["success"] = false;
            out["reason"] = "message doesn't contain \"port\" key";
            return;
        }

        int port = data.at("port");
        if (!(0 <= port && port <= 4))
        {
            out["success"] = false;
            out["reason"] = "invalid servo port";
            return;
        }

        out["success"] = true;
        out["value"] = Control::servos[port]->isEnabled();
    }

    // digitals
    else if (request == "digital")
    {
        if (!data.contains("port"))
        {
            out["success"] = false;
            out["reason"] = "message doesn't contain \"port\" key";
            return;
        }

        int port = data.at("port");
        if (!(0 <= port && port <= 10))
        {
            out["success"] = false;
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
            out["success"] = false;
            out["reason"] = "message doesn't contain \"port\" key";
            return;
        }

        int port = data.at("port");
        if (!(0 <= port && port <= 5))
        {
            out["success"] = false;
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


/**
 * @brief handle all set requests
 * 
 * @param data input json object
 * @param out output json object
 */
void handle_set(json data, json &out)
{
    std::string request = data["request"];

    // motors
    if (request == "motor")
    {
        if (!data.contains("port"))
        {
            out["success"] = false;
            out["reason"] = "message doesn't contain \"port\" key";
            return;
        }

        int port = data.at("port");
        if (!(0 <= port && port <= 4))
        {
            out["success"] = false;
            out["reason"] = "invalid motor port";
            return;
        }

        if (!data.contains("velocity"))
        {
            out["success"] = false;
            out["reason"] = "message doesn't contain \"velocity\" key";
            return;
        }

        int velocity = data.at("velocity");
        if (!(-1500 <= velocity && velocity <= 1500))
        {
            out["success"] = false;
            out["reason"] = "invalid motor velocity";
            return;
        }

        Control::motors[port]->moveAtVelocity(velocity);

        out["success"] = true;
    }

    // create motors
    else if (request == "create_motor")
    {
        if (!data.contains("port"))
        {
            out["success"] = false;
            out["reason"] = "message doesn't contain \"port\" key";
            return;
        }

        int port = data.at("port");
        if (port < 0 || port > 1)
        {
            out["success"] = false;
            out["reason"] = "invalid motor port";
            return;
        }

        if (!data.contains("velocity"))
        {
            out["success"] = false;
            out["reason"] = "message doesn't contain \"velocity\" key";
            return;
        }

        int velocity = data.at("velocity");
        if (!(-500 <= velocity && velocity <= 500))
        {
            out["success"] = false;
            out["reason"] = "invalid motor velocity";
            return;
        }

        Control::cmotors[port]->moveAtVelocity(velocity);

        out["success"] = true;
    }

    // servos
    else if (request == "servo_pos")
    {
        if (!data.contains("port"))
        {
            out["success"] = false;
            out["reason"] = "message doesn't contain \"port\" key";
            return;
        }

        int port = data.at("port");
        if (!(0 <= port && port <= 4))
        {
            out["success"] = false;
            out["reason"] = "invalid servo port";
            return;
        }

        if (!data.contains("position"))
        {
            out["success"] = false;
            out["reason"] = "message doesn't contain \"position\" key";
            return;
        }

        int position = data.at("position");
        if (!(0 <= position && position <= 2047))
        {
            out["success"] = false;
            out["reason"] = "invalid servo position";
            return;
        }


        Control::servos[port]->setPosition(position);
        out["success"] = true;
    }
    else if (request == "servo_enabled")
    {
        if (!data.contains("port"))
        {
            out["success"] = false;
            out["reason"] = "message doesn't contain \"port\" key";
            return;
        }

        int port = data.at("port");
        if (!(0 <= port && port <= 4))
        {
            out["success"] = false;
            out["reason"] = "invalid servo port";
            return;
        }

        if (!data.contains("enabled"))
        {
            out["success"] = false;
            out["reason"] = "message doesn't contain \"enabled\" key";
            return;
        }


        Control::servos[port]->setEnabled(data["enabled"]);
        out["success"] = true;
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
        std::string type = data.at("type");

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
        else if (type == "set")
        {
            if (!data.contains("request"))
            {
                out["reason"] = "message doesn't contain \"request\" key";
            }
            else
            {
                handle_set(data, out);
            }
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
