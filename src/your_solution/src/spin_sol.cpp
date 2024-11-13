#include "spin_sol.h"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SpinSolution>());
  rclcpp::shutdown();
  return 0;
}

//your code here
SpinSolution::SpinSolution() : Node("spinsolution") {
  RCLCPP_INFO(this->get_logger(), "node spin_slow_update started");
  // your code here

    // pos = std::make_shared<ArrayMsg>();
    // vel = std::make_shared<ArrayMsg>();

    subscriptionPos = this->create_subscription<ArrayMsg>(
        "/measuredpos", 10,
        std::bind(&SpinSolution::measuredPos, this, std::placeholders::_1)
    );
    subscriptionVel = this->create_subscription<ArrayMsg>(
        "/measuredvel", 10,
        std::bind(&SpinSolution::measuredVel, this, std::placeholders::_1)
    );

    publisher = this->create_publisher<ArrayMsg>("/predictedpos",10);

    timer = this->create_wall_timer(
      std::chrono::milliseconds(50),
      std::bind(&SpinSolution::timerCallback, this)
    );
}

void SpinSolution::measuredPos(const ArrayMsg::SharedPtr msg){
  RCLCPP_INFO(this->get_logger(), "measured pos");
  pos = msg;
  lastTime = this->now();
}

void SpinSolution::measuredVel(const ArrayMsg::SharedPtr msg){
  RCLCPP_INFO(this->get_logger(), "measured vel");
  vel = msg;
}

void SpinSolution::timerCallback(){
  if(pos == nullptr|| vel == nullptr){
    return;
  }

  RCLCPP_INFO(this->get_logger(), "timer");

  rclcpp::Time currentTime = this->now();
  double delta_t = currentTime.seconds() - lastTime.seconds();

  auto predicted_msg = ArrayMsg();
  predicted_msg.data.resize(2);

  predicted_msg.data[0] = pos->data[0] + delta_t * vel->data[0];
  predicted_msg.data[1] = pos->data[1] + delta_t * vel->data[1];

  publisher->publish(predicted_msg);
}