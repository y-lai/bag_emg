#include <ros/ros.h>
#include <track_robot_msgs/Trigger.h>
#include <labjackt7test/labjackt7test_streaming.h>
#include <rosbag/bag.h>
#include <mutex>
#include <algorithm>


rosbag::Bag bag;
// ros::Subscriber sub;
ros::Subscriber emgsub;
ros::NodeHandle* nh;
bool subbed;
std::mutex _mtx;


// void triggerCallback(const track_robot_msgs::TriggerConstPtr& msg);
// void emgCallback(const labjackt7test::labjackt7test_streamingConstPtr& emgmsg);

void emgCallback(const labjackt7test::labjackt7test_streamingConstPtr& emgmsg)
{
    std::lock_guard<std::mutex> lock(_mtx);
    bag.write("labjack/channelstream",ros::Time::now(),*emgmsg);
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"bag_emg_node");
    nh = new ros::NodeHandle;
    ros::NodeHandle pnh("~");
    
    // sub = nh->subscribe("/track/trigger",1,triggerCallback);
    std::string bagname;
    if(!pnh.getParam("bagname",bagname))
    {
        bagname = "emgbag.bag";
    }
    std::cout << "bag opening" << std::endl;
    bag.open(bagname.c_str(),rosbag::bagmode::Write);
    // subbed = false;

    emgsub = nh->subscribe("/labjack/channelstream",1,emgCallback);
    ros::spin();

    std::cout << "closing bag" << std::endl;
    bag.close();
    return 0;
}


// void triggerCallback(const track_robot_msgs::TriggerConstPtr& msg)
// {
//     if(msg->trig && !subbed)
//     {
//         emgsub = nh->subscribe("/labjack/channelstream",1,emgCallback);
//         subbed = true;
//     }
//     if(!msg->trig && subbed)
//     {
//         emgsub.shutdown();
//         subbed = false;
//     }
// }
