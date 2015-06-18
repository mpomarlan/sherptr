cmake_minimum_required(VERSION 2.8.3)
project(sherptr_msgs)

set(MSG_DEPS
  std_msgs
  geometry_msgs)

find_package(catkin REQUIRED genmsg ${MSG_DEPS})

set(MSG_FILES
  Bot.msg
  CellGrid.msg
  FlightPlanRequest.msg
  FlightPlanResponse.msg
  GridPoint.msg
  GridTrajectory.msg
)

set(SRV_FILES
  PlanFlight.srv
)

set(ACT_FILES
)

add_action_files(DIRECTORY action FILES ${ACT_FILES})
add_message_files(DIRECTORY msg FILES ${MSG_FILES})
add_service_files(DIRECTORY srv FILES ${SRV_FILES})

generate_messages(DEPENDENCIES ${MSG_DEPS})

catkin_package(DEPENDS ${MSG_DEPS})
