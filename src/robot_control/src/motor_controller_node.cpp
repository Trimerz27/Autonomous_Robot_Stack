#include <chrono>
#include <functional>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

class GroundTargetController : public rclcpp::Node {
public:
    GroundTargetController() : Node("motor_controller_node") {
        // Hardcoded straight to the native Gazebo Sim bridge topic
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/model/ground_robot/cmd_vel", 10);
        timer_ = this->create_wall_timer(100ms, std::bind(&GroundTargetController::drive_loop, this));
        RCLCPP_INFO(this->get_logger(), "Ground Wheeled Vehicle active. Commencing movement...");
    }

private:
    void drive_loop() {
        auto twist = geometry_msgs::msg::Twist();
        twist.linear.x = 0.6;   // Forward cruise speed
        twist.angular.z = 0.2;  // Safe arc turn rate
        publisher_->publish(twist);
    }
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GroundTargetController>());
    rclcpp::shutdown();
    return 0;
}
