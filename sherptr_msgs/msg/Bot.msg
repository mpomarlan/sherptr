# This is used to name the robot in the response
int32 robot_id

# Enforce the return of this robot to a retrieval point
int32 boomerang

# Does the robot have a 3x3 or a 1x1 view range?
int32 wideview

# Number of charge units the robot can store
int32 max_charge

# Number of charge units a robot needs to travel one distance unit
int32 travel_cost

# Number of charge units left
int32 charge

# Starting position
GridPoint start

