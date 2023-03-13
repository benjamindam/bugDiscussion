#include <functional>
#include <memory>
//#include <stdio.h>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/range.hpp"
//#include <yaml-cpp/yaml.h> //For parsing

using std::placeholders::_1;

class SonarSubscriber : public rclcpp::Node
{
public:
  SonarSubscriber()
  : Node("sonar_subscriber")
  {
    range_subscription_ = this->create_subscription<sensor_msgs::msg::Range>(
      "/capra/sensors/ultrasound/measurement",
      10, 
      std::bind(&SonarSubscriber::topic_callback, this, _1)
      );
  }
private:
  void topic_callback(const sensor_msgs::msg::Range::SharedPtr & msg) const
  {
    //printf("Topic: %g", msg->range);
    RCLCPP_INFO(this->get_logger(), "The topic shows: '%f'", msg->range); //Log directly to terminal.
  }
  std::shared_ptr<rclcpp::Subscription<std::shared_ptr<sensor_msgs::msg::Range>>> range_subscription_;
  //rclcpp::Subscription<sensor_msgs::msg::Range>::SharedPtr range_subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SonarSubscriber>());
  rclcpp::shutdown();
  return 0;
}
