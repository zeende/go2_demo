#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "unitree_go/msg/sport_mode_cmd.hpp"

class Cmd_Sender : public rclcpp::Node
{
public:
    // 构造函数,有一个参数为节点名称
    Cmd_Sender() : Node("Cmd_Sender")
    {
        //RCLCPP_INFO(this->get_logger(), "大家好，我是%s.", name.c_str());
        // 创建发布者
        command_publisher_ = this->create_publisher<unitree_go::msg::SportModeCmd>("/sportmodecmd", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&Cmd_Sender::timer_callback, this));
    }

private:
    void timer_callback()
    {
        // 创建消息
        unitree_go::msg::SportModeCmd message;
        message.mode = 2;
        message.gait_type = 1;
        message.yaw_speed = 0.0;
        // 日志打印
        // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        // 发布消息
        command_publisher_->publish(message);
    }
    // 声名定时器指针
    rclcpp::TimerBase::SharedPtr timer_;
    // 声明话题发布者
    rclcpp::Publisher<unitree_go::msg::SportModeCmd>::SharedPtr command_publisher_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::TimerBase::SharedPtr timer_;
    /*创建对应节点的共享指针对象*/
    auto node = std::make_shared<Cmd_Sender>();
    /* 运行节点，并检测退出信号*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
