#include <chrono>
#include <functional>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>

using namespace std::chrono_literals;

class VTOLFlightController : public rclcpp::Node {
public:
    VTOLFlightController() : Node("vtol_flight_node"), flight_state_(0), loop_counter_(0) {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&VTOLFlightController::flight_loop, this));
        RCLCPP_INFO(this->get_logger(), "VTOL Flight Controller initialized. Standby for Takeoff sequence...");
    }

private:
    void flight_loop() {
        auto twist = geometry_msgs::msg::Twist();
        loop_counter_++;

        switch(flight_state_) {
            case 0: // Vertical Lift / Takeoff (Quad-copter Mode)
                twist.linear.z = 1.0; // Ascend vertically on Z-axis
                RCLCPP_INFO(this->get_logger(), "State [TAKEOFF]: Ascending vertically on Z-Axis...");
                if (loop_counter_ >= 10) { // After 5 seconds
                    flight_state_ = 1;
                    loop_counter_ = 0;
                }
                break;

            case 1: // Hover Translation (Transition Mode)
                twist.linear.z = 0.0;  // Stop ascending, maintain altitude
                twist.linear.x = 1.5;  // Engaged pusher motor! Accelerate forward
                RCLCPP_INFO(this->get_logger(), "State [FORWARD FLIGHT]: Pusher prop active, cruising forward...");
                if (loop_counter_ >= 20) { // Cruising for 10 seconds
                    flight_state_ = 2;
                    loop_counter_ = 0;
                }
                break;

            case 2: // Descend / Land
                twist.linear.x = 0.0;  // Kill forward velocity
                twist.linear.z = -0.5; // Descend slowly
                RCLCPP_INFO(this->get_logger(), "State [LANDING]: Vertical descent initiated...");
                if (loop_counter_ >= 10) {
                    RCLCPP_INFO(this->get_logger(), "VTOL has safely touched down.");
                    timer_->cancel(); // Stop running flight logic
                }
                break;
        }
        publisher_->publish(twist);
    }

    int flight_state_;
    int loop_counter_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<VTOLFlightController>());
    rclcpp::shutdown();
    return 0;
}
