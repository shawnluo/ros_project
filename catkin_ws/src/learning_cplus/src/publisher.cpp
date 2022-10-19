#include "ros/ros.h" //导入ROS系统包含核心公共头文件 
#include "std_msgs/String.h" //导入std_msgs/String消息头文件，这个是由std_m sgs包的string.msg文件自动生成。
#include <sstream> 

int main(int argc, char **argv) 
{ 
    ros::init(argc, argv, "talker"); //初始化ROS，指定节点名称为“talker”，节点 名称要保持唯一性。名称定义参考 
    ros::NodeHandle n; //实例化节点 
    //ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000); //发布一个消息类型为std_msgs/String，命名为chatter的话题。 
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("roar", 1000);
    //定义消息队列大小为1000，即超过1000条消息之后，旧的消息就会丢弃。
    ros::Rate loop_rate(10); //指定发布消息的频率，这里指10Hz，也即每秒10次 
    //通过 Rate::sleep()来处理睡眠的时间来控制对应的发布频率。 
    int count = 0; 
    while (ros::ok()) 
    { 
        /* 
        默认roscpp会植入一个SIGINT处理机制，当按下Ctrl‐C，就会让ros::ok()返回false, 那循环就会结束。 
        ros::ok() 返回false的几种情况： 
            SIGINT收到(Ctrl‐C)信号 
            另一个同名节点启动，会先中止之前的同名节点 
            ros::shutdown()被调用
            所有的ros::NodeHandles被销毁 
        */ 
        std_msgs::String msg; 
        std::stringstream ss; 
        ss << "hello world " << count; 
        msg.data = ss.str(); 
        //实例化消息msg, 定义字符串流“hello world”并赋值给ss, 最后转成为字符串赋值给 msg.data 
        ROS_INFO("%s", msg.data.c_str()); //输出调试信息 

        chatter_pub.publish(msg); //发布msg 

        ros::spinOnce();
        //不是必需的，但是保持增加这个调用，是好习惯 
        //如果程序里也有订阅话题，就必需，否则回调函数不能起作用
        //只处理一次回调函数，如果没有回调函数

        loop_rate.sleep(); 
        //根据之前ros::Rate loop_rate(10)的定义来控制发布话题的频率。定义10即为每秒1 0次
        ++count; 
    } 
    return 0; 
}
