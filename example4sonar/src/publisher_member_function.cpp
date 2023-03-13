#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/range.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class SonarPublisher : public rclcpp::Node
{
public:
  SonarPublisher()
  : Node("sonar_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<sensor_msgs::msg::Range>("capra/sensors/ultrasound/measurement", 10);
    timer_ = this->create_wall_timer(
      500ms, std::bind(&SonarPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = sensor_msgs::msg::Range();
    message.range = 2.0;
    //RCLCPP_INFO(this->get_logger(), "Output %f ", message);
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<sensor_msgs::msg::Range>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SonarPublisher>());
  rclcpp::shutdown();
  return 0;
}
