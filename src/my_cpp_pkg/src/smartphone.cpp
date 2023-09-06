#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

using namespace std;

class SmartphoneNode : public rclcpp::Node // CHANGE
{
public:
    SmartphoneNode() : Node("cpp_test") // CHANGE NODE NAME
    {
       subscriber_= this->create_subscription<example_interfaces::msg::String>("robot_news",10,
       std::bind(&SmartphoneNode::callbackRobotNews,this,std::placeholders::_1));   
       RCLCPP_INFO(this->get_logger(), "Smartphone has been started");
    }
    
private:
    void callbackRobotNews(const example_interfaces::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
    }

    rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscriber_;

    
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = make_shared<SmartphoneNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}