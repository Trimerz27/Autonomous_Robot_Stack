#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class MotorController : public rclcpp::Node
{
public:
    MotorController()
    : Node("motor_controller")
    {
        this->declare_parameter("max_speed", 1.0);

        max_speed_ = this->get_parameter("max_speed")
                         .as_double();

        cmd_subscriber_ =
            this->create_subscription<geometry_msgs::msg::Twist>(
                "/cmd_vel",
                10,
                std::bind(
                    &MotorController::cmd_callback,
                    this,
                    _1));

        status_publisher_ =
            this->create_publisher<std_msgs::msg::String>(
                "/motor_status",
                10);

        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(
                &MotorController::publish_status,
                this));

        RCLCPP_INFO(
            this->get_logger(),
            "Motor Controller started. Max speed: %.2f",
            max_speed_);
    }

private:

    void cmd_callback(
        const geometry_msgs::msg::Twist::SharedPtr msg)
    {
        RCLCPP_INFO(
            this->get_logger(),
            "Command received: linear %.2f angular %.2f",
            msg->linear.x,
            msg->angular.z);
    }


    void publish_status()
    {
        auto message =
            std_msgs::msg::String();

        message.data = "Motors online";

        status_publisher_->publish(message);
    }


    double max_speed_;

    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr
        cmd_subscriber_;

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr
        status_publisher_;

    rclcpp::TimerBase::SharedPtr timer_;
};


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    rclcpp::spin(
        std::make_shared<MotorController>());

    rclcpp::shutdown();

    return 0;
}
