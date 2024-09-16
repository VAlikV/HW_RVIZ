#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <sstream>

float pose[] {0, 0, 0, 0, 0, 0};
int8_t joints = 6;

std::string ss = "joint";

void recalc_angle(float* pose)
{
    float pi = 3.14159265;
    for (int8_t i = 0; i < joints; ++i)
    {
        pose[i] = pose[i]*pi/180;
    }
}

int main(int argc, char **argv)
{

    ros::init(argc, argv, "talker");

    ros::NodeHandle n;

    ros::Publisher pub_command = n.advertise<sensor_msgs::JointState>("/joint_states", 1000);

    ros::Rate loop_rate(10);

    int count = 0;
    while (ros::ok())
    {
        std::cin >> pose[0] >> pose[1] >> pose[2] >> pose[3] >> pose[4] >> pose[5];

        recalc_angle(pose);

        sensor_msgs::JointState msg;

        msg.header.seq = 1;
        msg.header.stamp = ros::Time::now();

        for (int8_t i = 0; i < joints; ++i)
        {
            msg.name.push_back(ss + std::to_string(i+1));
            msg.position.push_back(pose[i]);
        }  

        ROS_INFO("In process");

        pub_command.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
        ++count;
    }


    return 0;
}
