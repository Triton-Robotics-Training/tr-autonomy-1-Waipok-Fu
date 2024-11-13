#ifndef YOUR_SOLUTION_SRC_SPIN_SOL_H_
#define YOUR_SOLUTION_SRC_SPIN_SOL_H_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"
using ArrayMsg = std_msgs::msg::Float64MultiArray;

class SpinSolution : public rclcpp::Node {
 public:
  SpinSolution();
 private:
    // your code here
    void measuredPos(const ArrayMsg::SharedPtr msg);
    void measuredVel(const ArrayMsg::SharedPtr msg);

    void timerCallback();

    rclcpp::Subscription<ArrayMsg>::SharedPtr subscriptionPos;
    rclcpp::Subscription<ArrayMsg>::SharedPtr subscriptionVel;
    rclcpp::Publisher<ArrayMsg>::SharedPtr publisher;

    rclcpp::TimerBase::SharedPtr timer;

    ArrayMsg::SharedPtr pos;
    ArrayMsg::SharedPtr vel;

    rclcpp::Time lastTime;
};

#endif //YOUR_SOLUTION_SRC_SPIN_SOL_H_
