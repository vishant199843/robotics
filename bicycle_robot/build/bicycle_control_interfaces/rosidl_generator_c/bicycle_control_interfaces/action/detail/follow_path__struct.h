// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from bicycle_control_interfaces:action/FollowPath.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "bicycle_control_interfaces/action/follow_path.h"


#ifndef BICYCLE_CONTROL_INTERFACES__ACTION__DETAIL__FOLLOW_PATH__STRUCT_H_
#define BICYCLE_CONTROL_INTERFACES__ACTION__DETAIL__FOLLOW_PATH__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in action/FollowPath in the package bicycle_control_interfaces.
typedef struct bicycle_control_interfaces__action__FollowPath_Goal
{
  uint8_t structure_needs_at_least_one_member;
} bicycle_control_interfaces__action__FollowPath_Goal;

// Struct for a sequence of bicycle_control_interfaces__action__FollowPath_Goal.
typedef struct bicycle_control_interfaces__action__FollowPath_Goal__Sequence
{
  bicycle_control_interfaces__action__FollowPath_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bicycle_control_interfaces__action__FollowPath_Goal__Sequence;

// Constants defined in the message

/// Struct defined in action/FollowPath in the package bicycle_control_interfaces.
typedef struct bicycle_control_interfaces__action__FollowPath_Result
{
  bool success;
  double final_distance;
} bicycle_control_interfaces__action__FollowPath_Result;

// Struct for a sequence of bicycle_control_interfaces__action__FollowPath_Result.
typedef struct bicycle_control_interfaces__action__FollowPath_Result__Sequence
{
  bicycle_control_interfaces__action__FollowPath_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bicycle_control_interfaces__action__FollowPath_Result__Sequence;

// Constants defined in the message

/// Struct defined in action/FollowPath in the package bicycle_control_interfaces.
typedef struct bicycle_control_interfaces__action__FollowPath_Feedback
{
  double distance_to_goal;
  double current_x;
  double current_y;
  double current_theta;
} bicycle_control_interfaces__action__FollowPath_Feedback;

// Struct for a sequence of bicycle_control_interfaces__action__FollowPath_Feedback.
typedef struct bicycle_control_interfaces__action__FollowPath_Feedback__Sequence
{
  bicycle_control_interfaces__action__FollowPath_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bicycle_control_interfaces__action__FollowPath_Feedback__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "bicycle_control_interfaces/action/detail/follow_path__struct.h"

/// Struct defined in action/FollowPath in the package bicycle_control_interfaces.
typedef struct bicycle_control_interfaces__action__FollowPath_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  bicycle_control_interfaces__action__FollowPath_Goal goal;
} bicycle_control_interfaces__action__FollowPath_SendGoal_Request;

// Struct for a sequence of bicycle_control_interfaces__action__FollowPath_SendGoal_Request.
typedef struct bicycle_control_interfaces__action__FollowPath_SendGoal_Request__Sequence
{
  bicycle_control_interfaces__action__FollowPath_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bicycle_control_interfaces__action__FollowPath_SendGoal_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/FollowPath in the package bicycle_control_interfaces.
typedef struct bicycle_control_interfaces__action__FollowPath_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} bicycle_control_interfaces__action__FollowPath_SendGoal_Response;

// Struct for a sequence of bicycle_control_interfaces__action__FollowPath_SendGoal_Response.
typedef struct bicycle_control_interfaces__action__FollowPath_SendGoal_Response__Sequence
{
  bicycle_control_interfaces__action__FollowPath_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bicycle_control_interfaces__action__FollowPath_SendGoal_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  bicycle_control_interfaces__action__FollowPath_SendGoal_Event__request__MAX_SIZE = 1
};
// response
enum
{
  bicycle_control_interfaces__action__FollowPath_SendGoal_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/FollowPath in the package bicycle_control_interfaces.
typedef struct bicycle_control_interfaces__action__FollowPath_SendGoal_Event
{
  service_msgs__msg__ServiceEventInfo info;
  bicycle_control_interfaces__action__FollowPath_SendGoal_Request__Sequence request;
  bicycle_control_interfaces__action__FollowPath_SendGoal_Response__Sequence response;
} bicycle_control_interfaces__action__FollowPath_SendGoal_Event;

// Struct for a sequence of bicycle_control_interfaces__action__FollowPath_SendGoal_Event.
typedef struct bicycle_control_interfaces__action__FollowPath_SendGoal_Event__Sequence
{
  bicycle_control_interfaces__action__FollowPath_SendGoal_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bicycle_control_interfaces__action__FollowPath_SendGoal_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/FollowPath in the package bicycle_control_interfaces.
typedef struct bicycle_control_interfaces__action__FollowPath_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} bicycle_control_interfaces__action__FollowPath_GetResult_Request;

// Struct for a sequence of bicycle_control_interfaces__action__FollowPath_GetResult_Request.
typedef struct bicycle_control_interfaces__action__FollowPath_GetResult_Request__Sequence
{
  bicycle_control_interfaces__action__FollowPath_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bicycle_control_interfaces__action__FollowPath_GetResult_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "bicycle_control_interfaces/action/detail/follow_path__struct.h"

/// Struct defined in action/FollowPath in the package bicycle_control_interfaces.
typedef struct bicycle_control_interfaces__action__FollowPath_GetResult_Response
{
  int8_t status;
  bicycle_control_interfaces__action__FollowPath_Result result;
} bicycle_control_interfaces__action__FollowPath_GetResult_Response;

// Struct for a sequence of bicycle_control_interfaces__action__FollowPath_GetResult_Response.
typedef struct bicycle_control_interfaces__action__FollowPath_GetResult_Response__Sequence
{
  bicycle_control_interfaces__action__FollowPath_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bicycle_control_interfaces__action__FollowPath_GetResult_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  bicycle_control_interfaces__action__FollowPath_GetResult_Event__request__MAX_SIZE = 1
};
// response
enum
{
  bicycle_control_interfaces__action__FollowPath_GetResult_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/FollowPath in the package bicycle_control_interfaces.
typedef struct bicycle_control_interfaces__action__FollowPath_GetResult_Event
{
  service_msgs__msg__ServiceEventInfo info;
  bicycle_control_interfaces__action__FollowPath_GetResult_Request__Sequence request;
  bicycle_control_interfaces__action__FollowPath_GetResult_Response__Sequence response;
} bicycle_control_interfaces__action__FollowPath_GetResult_Event;

// Struct for a sequence of bicycle_control_interfaces__action__FollowPath_GetResult_Event.
typedef struct bicycle_control_interfaces__action__FollowPath_GetResult_Event__Sequence
{
  bicycle_control_interfaces__action__FollowPath_GetResult_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bicycle_control_interfaces__action__FollowPath_GetResult_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "bicycle_control_interfaces/action/detail/follow_path__struct.h"

/// Struct defined in action/FollowPath in the package bicycle_control_interfaces.
typedef struct bicycle_control_interfaces__action__FollowPath_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  bicycle_control_interfaces__action__FollowPath_Feedback feedback;
} bicycle_control_interfaces__action__FollowPath_FeedbackMessage;

// Struct for a sequence of bicycle_control_interfaces__action__FollowPath_FeedbackMessage.
typedef struct bicycle_control_interfaces__action__FollowPath_FeedbackMessage__Sequence
{
  bicycle_control_interfaces__action__FollowPath_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} bicycle_control_interfaces__action__FollowPath_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BICYCLE_CONTROL_INTERFACES__ACTION__DETAIL__FOLLOW_PATH__STRUCT_H_
