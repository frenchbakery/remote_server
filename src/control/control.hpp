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
#include <kiprplus/create_motor.hpp>
#include <kipr/servo/servo.hpp>
#include <kipr/digital/digital.hpp>
#include <kipr/analog/analog.hpp>
#include <string>


// port number setup  (0...n)
#define N_MOTORS 4
#define N_CMOTORS 2
#define N_SERVOS 4
#define N_DIGITALS 10
#define N_ANALOGS 5


namespace Control
{
    typedef kp::PIDMotor Motor;
    typedef kp::CreateMotor CMotor;
    typedef kipr::servo::Servo Servo;
    typedef kipr::digital::Digital Digital;
    typedef kipr::analog::Analog Analog;

    extern std::vector<std::shared_ptr<Motor>> motors; 
    extern std::vector<std::shared_ptr<CMotor>> cmotors; 
    extern std::vector<std::shared_ptr<Servo>> servos;
    extern std::vector<std::shared_ptr<Digital>> digitals;
    extern std::vector<std::shared_ptr<Analog>> analogs;

    void setup();
    std::string message_handler(std::string message);
} // namespace Control
