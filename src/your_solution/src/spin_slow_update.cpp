#include "spin_slow_update.h"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SlowSolution>());
  rclcpp::shutdown();
  return 0;
}

SlowSolution::SlowSolution() : Node("slowsolution") {
  RCLCPP_INFO(this->get_logger(), "Node slowSolution started");
  // your code here
  subscription=this->create_subscription<ArrayMsg>(
    "/measuredpos",10,
    std::bind(&SlowSolution::measuredPos,this,std::placeholders::_1)
  );

  publisher=this->create_publisher<ArrayMsg>("/predictedpos",10);
}

// your code here
void SlowSolution::measuredPos(const ArrayMsg::SharedPtr msg){
  auto predictedMsg = ArrayMsg();
  predictedMsg.data = msg->data;
  publisher->publish(predictedMsg);
}