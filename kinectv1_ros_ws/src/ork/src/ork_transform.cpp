#include "ros/ros.h"
#include "std_msgs/String.h"
#include <object_recognition_msgs/RecognizedObjectArray.h>
#include <std_msgs/Float32MultiArray.h>
#include <vector>
#include <string>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <tf/exceptions.h>
#include <tf/tfMessage.h>

typedef struct object
{
    std::string id;
    float x;
    float y;
    float z;
}Object;
std::vector<object> object_send;

void chatterCallback(const object_recognition_msgs::RecognizedObjectArray::ConstPtr &msg_receive)
{
  for (int i=0;i<msg_receive->objects.size();++i)
    {
      ROS_INFO("i: [%d]",i);
      ROS_INFO("frame id: [%s]", msg_receive->objects[i].header.frame_id.c_str());
      ROS_INFO("key: [%s]", msg_receive->objects[i].type.key.c_str());
      ROS_INFO("position x: [%f]", msg_receive->objects[i].pose.pose.pose.position.x);
      ROS_INFO("position y: [%f]", msg_receive->objects[i].pose.pose.pose.position.y);
      ROS_INFO("position z: [%f]", msg_receive->objects[i].pose.pose.pose.position.z);
      ROS_INFO("orientation x: [%f]", msg_receive->objects[i].pose.pose.pose.orientation.x);
      ROS_INFO("orientation y: [%f]", msg_receive->objects[i].pose.pose.pose.orientation.y);
      ROS_INFO("orientation z: [%f]", msg_receive->objects[i].pose.pose.pose.orientation.z);
      ROS_INFO("orientation w: [%f]\n", msg_receive->objects[i].pose.pose.pose.orientation.w);
      Object buffer;
      buffer.id=msg_receive->objects[i].type.key.c_str();
      buffer.x=float(msg_receive->objects[i].pose.pose.pose.position.x);
      buffer.y=float(msg_receive->objects[i].pose.pose.pose.position.y);
      buffer.z=float(msg_receive->objects[i].pose.pose.pose.position.z);
      object_send.push_back(buffer);
    }
  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ork_transform");
  ros::NodeHandle n;
  ros::AsyncSpinner spinner(1);
  spinner.start();
  ros::Subscriber sub = n.subscribe("recognized_object_array", 5, chatterCallback);
  /*ros::Publisher chatter_pub_1 = n.advertise<std_msgs::Float32MultiArray>("bottle_topic", 5);
  ros::Publisher chatter_pub_2 = n.advertise<std_msgs::Float32MultiArray>("glass_topic", 5);
  std_msgs::Float32MultiArrayPtr send_info_msg;
  std_msgs::Float32MultiArray send_info;
  send_info_msg=std_msgs::Float32MultiArrayPtr(new std_msgs::Float32MultiArray);
  send_info.data.resize(5);
  send_info.data[0]=0;
  send_info.data[1]=0;
  send_info.data[2]=0;
  send_info.data[3]=0;
  send_info.data[4]=0;
  *send_info_msg=send_info;*/
  
  tf::TransformBroadcaster br1;
  while(ros::ok())
  {
      ros::spinOnce();      
      for(int i=0;i<object_send.size();++i)
  
      {
      
          if(object_send[i].id=="e682109ebe032b6019b5ff0440000bcc")
          {
          
              /*send_info.data[2]=object_send[i].x;
              send_info.data[3]=object_send[i].y;
              send_info.data[4]=object_send[i].z;
              chatter_pub_1.publish(send_info);
              ROS_INFO("bottle \n");*/
ROS_INFO("bottle \n");
              try
              {
                  tf::Transform transform;
                  transform.setOrigin(tf::Vector3(object_send[i].x,object_send[i].y,object_send[i].z));
                  tf::Quaternion q;  
                  q.setRPY(0, 0, 0); 
                  transform.setRotation(q);       
                  br1.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "camera_rgb_optical_frame", "bottle"));
              }
              catch(tf::TransformException ex)
              {  
                  ROS_ERROR("%s",ex.what());
                  ros::Duration(1.0).sleep();
                  continue;
              }
          }
      
          if(object_send[i].id=="e682109ebe032b6019b5ff044001fdd1")
          {
          
              /*send_info.data[2]=object_send[i].x;
              send_info.data[3]=object_send[i].y;
              send_info.data[4]=object_send[i].z;
              chatter_pub_2.publish(send_info);
              ROS_INFO("glass \n");*/
              try
              {
                  tf::Transform transform;
                  transform.setOrigin(tf::Vector3(object_send[i].x,object_send[i].y,object_send[i].z));
                  tf::Quaternion q;  
                  q.setRPY(0, 0, 0); 
                  transform.setRotation(q);       
                  br1.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "camera_rgb_optical_frame", "bottle"));
              }
              catch(tf::TransformException ex)
              {  
                  ROS_ERROR("%s",ex.what());
                  ros::Duration(1.0).sleep();
                  continue;
              }
          }  
      } 
      object_send.clear();
  }
  return 0;
}
