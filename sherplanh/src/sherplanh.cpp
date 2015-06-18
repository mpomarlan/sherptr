#include "ros/ros.h"
#include <signal.h>

#include <cstdlib>
#include <iostream>

#include <sherptr/sherplanh/flight_planner.h>
#include <sherptr_msgs/PlanFlight.h>

bool planFlightService(sherptr_msgs::PlanFlight::Request &req, sherptr_msgs::PlanFlight::Response &res)
{
  return true;
}

int main(int argc, char *argv[])
{
  //init ROS node
  ros::init (argc, argv, "sherplanh");
  ros::WallDuration sleep_t(0.5);
  ros::AsyncSpinner spinner(1);
  spinner.start();

  ROS_INFO("Started sherplanh.");

  ros::NodeHandle node_handle;

  sleep_t.sleep();
  ROS_INFO("Setting up service ...");

  ros::ServiceServer servicePlanFlight = node_handle.advertiseService("PlanFlight", planFlightService);
  ROS_INFO("                   ... PlanFlight.");
  sleep_t.sleep();

  //signal(SIGINT, onQuit);
  
  ROS_INFO("Just chillin'.");

  ros::spin();


  return 0;
}
