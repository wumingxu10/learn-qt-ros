#pragma once

#include <QThread>
#include <QString>
#include <rclcpp/publisher.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class RosNode : public QThread
{
    Q_OBJECT //这个宏是Qt元对象系统的必需部分，它启用了信号、槽和属性等特性

public:
    RosNode(int argc,char** argv);
    virtual ~RosNode(); //虚析构函数，确保派生类的析构函数被调用
    bool init();
    void run() override;

    void cb_strMsg(const std_msgs::msg::String::ConstPtr msg);

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscribe_;

Q_SIGNALS:
    void signal_rosShutdown();
    void signal_strMsg(const QString&);

public slots:
    void slot_pubStrMsg(const QString&);

private:
    int init_argc_;
    char** init_argv_;
    std::string node_name_;
};