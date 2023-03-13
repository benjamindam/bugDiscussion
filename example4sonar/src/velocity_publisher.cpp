#include <functional>
#include <memory>
#include <chrono>
#include <math.h>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist_stamped.hpp"

using namespace std::chrono_literals;

class VelocityPublisher : public rclcpp::Node
{
public:
  VelocityPublisher()
  : Node("velocity_publisher"), count_(0)
  {
    vel_publisher_ = this->create_publisher<geometry_msgs::msg::TwistStamped>("/capra/remote/direct_velocity",rclcpp::SensorDataQoS());
    timer_ = this->create_wall_timer(10ms, std::bind(&VelocityPublisher::callback, this));
  }

private:
  void callback()
  {
    auto message = geometry_msgs::msg::TwistStamped();
    message.twist.linear.x = 0.5;// + sin(0.1*count_++);
    message.twist.angular.z = 0.2;// + cos(0.1*count_++);
    vel_publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr vel_publisher_;
  //std::shared_ptr<rclcpp::Publisher<std::shared_ptr<geometry_msgs::msg::TwistStamped>>> vel_publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<VelocityPublisher>());
  rclcpp::shutdown();
  return 0;
}

