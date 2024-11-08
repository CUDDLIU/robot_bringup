#include "robot_bringup/robot.h"

double RobotV_ = 0;
double RobotYawRate_ = 0;

// 速度控制消息的回调函数
void cmdCallback(const geometry_msgs::Twist &msg)
{
    RobotV_ = msg.linear.x * 1000; // mm/s
    RobotYawRate_ = msg.angular.z; // rad/s
}

int main(int argc, char **argv)
{
    // 初始化ROS节点
    ros::init(argc, argv, "mbot_bringup");
    ros::NodeHandle nh;

    // 初始化robot
    robot::robot myrobot;
    if (!myrobot.init())
        ROS_ERROR("myrobot initialized failed.");
    ROS_INFO("huangbinbinrobot initialized successful.");

    ros::Subscriber sub = nh.subscribe("cmd_vel", 100, cmdCallback);

    // 循环运行
    ros::Rate loop_rate(100);
    while (ros::ok())
    {
        ros::spinOnce();
        // 机器人控制
        myrobot.deal(RobotV_, RobotYawRate_);
        loop_rate.sleep();
    }

    return 0;
}
