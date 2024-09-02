#include "rosNode.h"
#include <QCoreApplication>


/**
 * 构造函数
 */
RosNode::RosNode(int argc,char** argv)
    :init_argc_(argc),
     init_argv_(argv),
     node_name_("node_01")
{


}

RosNode::~RosNode()
{
    
}

bool RosNode::init() 
{
   
    
    QThread::start();
    return true;
}

void RosNode::run() 
{
    /* 初始化rclcpp  */
    rclcpp::init(init_argc_, init_argv_);

    /*产生一个node_01的节点*/
    auto node = std::make_shared<rclcpp::Node>(node_name_);
    // 打印一句自我介绍
    RCLCPP_INFO(node->get_logger(), "node_01节点已经启动.");
    command_subscribe_ = node->create_subscription<std_msgs::msg::String>("command", 10, std::bind(&RosNode::cb_strMsg, this, std::placeholders::_1));
    command_publisher_ = node->create_publisher<std_msgs::msg::String>("command", 10);

    rclcpp::Rate rate(10);
    while(true)
    {
        QCoreApplication::processEvents();//确保Qt的事件循环得到处理
        rclcpp::spin_some(node);
        rate.sleep();
    }
    /* 停止运行 */
    rclcpp::shutdown();
    Q_EMIT signal_rosShutdown();
}

void RosNode::slot_pubStrMsg(const QString& msg)
{
    std_msgs::msg::String str_msg;
    str_msg.data = msg.toStdString();
    command_publisher_->publish(str_msg);
}

void RosNode::cb_strMsg(const std_msgs::msg::String::ConstPtr msg)
{
    Q_EMIT signal_strMsg(QString::fromStdString(msg->data));    
}
