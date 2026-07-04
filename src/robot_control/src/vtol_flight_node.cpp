#include <chrono>
#include <functional>
#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <nav_msgs/msg/odometry.hpp>

using namespace std::chrono_literals;

class VTOLRelativeTrackingController : public rclcpp::Node {
public:
    VTOLRelativeTrackingController() : Node("vtol_flight_node"), 
        target_x_(2.0), target_y_(0.0), jet_x_(0.0), jet_y_(0.0) 
    {
        // 1. Subscribe to Ground Robot Odometry
        ground_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/model/ground_robot/odometry", 10, 
            std::bind(&VTOLRelativeTrackingController::ground_callback, this, std::placeholders::_1));

        // 2. Subscribe to Jet's own native Odometry position
        jet_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/model/standard_vtol/odometry", 10, 
            std::bind(&VTOLRelativeTrackingController::jet_callback, this, std::placeholders::_1));

        // 3. Publish flight commands straight to the VTOL bridge channel
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/model/standard_vtol/cmd_vel", 10);
        
        timer_ = this->create_wall_timer(50ms, std::bind(&VTOLRelativeTrackingController::control_loop, this));
        RCLCPP_INFO(this->get_logger(), "VTOL Fixed-Height Tracking Escort Node Engaged.");
    }

private:
    void ground_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
        target_x_ = msg->pose.pose.position.x;
        target_y_ = msg->pose.pose.position.y;
    }

    void jet_callback(const nav_msgs::msg::Odometry::SharedPtr msg) {
        jet_x_ = msg->pose.pose.position.x;
        jet_y_ = msg->pose.pose.position.y;
    }

    void control_loop() {
        auto twist = geometry_msgs::msg::Twist();

        // Let Gazebo handle the altitude physics directly
        twist.linear.z = 0.0; 

        // Calculate 2D relative tracking errors
        double error_x = target_x_ - jet_x_;
        double error_y = target_y_ - jet_y_;
        
        // Proportional steering multiplier
        double kp = 0.7;

        // Apply tracking velocities directly to follow the rover's path
        twist.linear.x = kp * error_x;
        twist.linear.y = kp * error_y;

        // Velocity clipping limits to keep flight trajectories completely smooth
        if (twist.linear.x > 1.5)  twist.linear.x = 1.5;
        if (twist.linear.x < -1.5) twist.linear.x = -1.5;
        if (twist.linear.y > 1.5)  twist.linear.y = 1.5;
        if (twist.linear.y < -1.5) twist.linear.y = -1.5;

        publisher_->publish(twist);
    }

    double target_x_;
    double target_y_;
    double jet_x_;
    double jet_y_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr ground_sub_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr jet_sub_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<VTOLRelativeTrackingController>());
    rclcpp::shutdown();
    return 0;
}
