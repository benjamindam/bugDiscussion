#include <iostream>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/range.hpp"

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("my_node");

  // Create a subscription to the topic
  auto sub = node->create_subscription<sensor_msgs::msg::Range>(
    "my_topic", 10, [](const sensor_msgs::msg::Range::SharedPtr msg) {

    // Convert the message to a string
    std::string msg_str = "Range message:\n";
    msg_str += "Header:\n";
    msg_str += "  stamp: " + std::to_string(msg->header.stamp.sec) + "." +
      std::to_string(msg->header.stamp.nanosec) + "\n";
    msg_str += "  frame_id: " + msg->header.frame_id + "\n";
    msg_str += "Field of view: " + std::to_string(msg->field_of_view) + "\n";
    msg_str += "Min range: " + std::to_string(msg->min_range) + "\n";
    msg_str += "Max range: " + std::to_string(msg->max_range) + "\n";
    msg_str += "Range: " + std::to_string(msg->range) + "\n";

    // Print the message string
    std::cout << msg_str << std::endl;
  });

  // Spin the node to receive messages
  rclcpp::spin(node);

  return 0;
}