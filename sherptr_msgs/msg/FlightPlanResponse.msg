# State of the cell values after running the trajectories
CellGrid new_world

# List of planned trajectories, including robots they apply to and some perf. metrics
GridTrajectory[] trajectories

# Sum of the values of the inspected cells over all trajectories
int32 value

# Number of robots that reached retrieval locations
int32 retrieved

# Max(trajectory length)
int32 time
