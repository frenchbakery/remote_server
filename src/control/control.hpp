/**
 * @file control.hpp
 * @author Nilusink
 * @brief defines the interface to the hardware (driver)
 * @version 1.0
 * @date 2023-03-04
 * 
 * @copyright Copyright frenchbakery (c) 2023
 * 
 */

#include <kiprplus/pid_motor.hpp>
#include <kipr/servo/servo.hpp>
#include <kipr/digital/digital.hpp>
#include <kipr/analog/analog.hpp>
#include <string>


#define N_MOTORS 4
#define N_SERVOS 4
#define N_DIGITALS 10
#define N_ANALOGS 5


namespace Control
{
    typedef kp::PIDMotor Motor;
    typedef kipr::servo::Servo Servo;
    typedef kipr::digital::Digital Digital;
    typedef kipr::analog::Analog Analog;

    extern std::vector<Motor> motors;
    extern std::vector<Servo> servos;
    extern std::vector<Digital> digitals;
    extern std::vector<Analog> analogs;

    void setup();
    std::string message_handler(std::string message);
} // namespace Control
