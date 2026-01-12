// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from bicycle_control_interfaces:action/FollowPath.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "bicycle_control_interfaces/action/follow_path.hpp"


#ifndef BICYCLE_CONTROL_INTERFACES__ACTION__DETAIL__FOLLOW_PATH__BUILDER_HPP_
#define BICYCLE_CONTROL_INTERFACES__ACTION__DETAIL__FOLLOW_PATH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "bicycle_control_interfaces/action/detail/follow_path__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace bicycle_control_interfaces
{

namespace action
{


}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::bicycle_control_interfaces::action::FollowPath_Goal>()
{
  return ::bicycle_control_interfaces::action::FollowPath_Goal(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace bicycle_control_interfaces


namespace bicycle_control_interfaces
{

namespace action
{

namespace builder
{

class Init_FollowPath_Result_final_distance
{
public:
  explicit Init_FollowPath_Result_final_distance(::bicycle_control_interfaces::action::FollowPath_Result & msg)
  : msg_(msg)
  {}
  ::bicycle_control_interfaces::action::FollowPath_Result final_distance(::bicycle_control_interfaces::action::FollowPath_Result::_final_distance_type arg)
  {
    msg_.final_distance = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_Result msg_;
};

class Init_FollowPath_Result_success
{
public:
  Init_FollowPath_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowPath_Result_final_distance success(::bicycle_control_interfaces::action::FollowPath_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_FollowPath_Result_final_distance(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::bicycle_control_interfaces::action::FollowPath_Result>()
{
  return bicycle_control_interfaces::action::builder::Init_FollowPath_Result_success();
}

}  // namespace bicycle_control_interfaces


namespace bicycle_control_interfaces
{

namespace action
{

namespace builder
{

class Init_FollowPath_Feedback_current_theta
{
public:
  explicit Init_FollowPath_Feedback_current_theta(::bicycle_control_interfaces::action::FollowPath_Feedback & msg)
  : msg_(msg)
  {}
  ::bicycle_control_interfaces::action::FollowPath_Feedback current_theta(::bicycle_control_interfaces::action::FollowPath_Feedback::_current_theta_type arg)
  {
    msg_.current_theta = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_Feedback msg_;
};

class Init_FollowPath_Feedback_current_y
{
public:
  explicit Init_FollowPath_Feedback_current_y(::bicycle_control_interfaces::action::FollowPath_Feedback & msg)
  : msg_(msg)
  {}
  Init_FollowPath_Feedback_current_theta current_y(::bicycle_control_interfaces::action::FollowPath_Feedback::_current_y_type arg)
  {
    msg_.current_y = std::move(arg);
    return Init_FollowPath_Feedback_current_theta(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_Feedback msg_;
};

class Init_FollowPath_Feedback_current_x
{
public:
  explicit Init_FollowPath_Feedback_current_x(::bicycle_control_interfaces::action::FollowPath_Feedback & msg)
  : msg_(msg)
  {}
  Init_FollowPath_Feedback_current_y current_x(::bicycle_control_interfaces::action::FollowPath_Feedback::_current_x_type arg)
  {
    msg_.current_x = std::move(arg);
    return Init_FollowPath_Feedback_current_y(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_Feedback msg_;
};

class Init_FollowPath_Feedback_distance_to_goal
{
public:
  Init_FollowPath_Feedback_distance_to_goal()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowPath_Feedback_current_x distance_to_goal(::bicycle_control_interfaces::action::FollowPath_Feedback::_distance_to_goal_type arg)
  {
    msg_.distance_to_goal = std::move(arg);
    return Init_FollowPath_Feedback_current_x(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::bicycle_control_interfaces::action::FollowPath_Feedback>()
{
  return bicycle_control_interfaces::action::builder::Init_FollowPath_Feedback_distance_to_goal();
}

}  // namespace bicycle_control_interfaces


namespace bicycle_control_interfaces
{

namespace action
{

namespace builder
{

class Init_FollowPath_SendGoal_Request_goal
{
public:
  explicit Init_FollowPath_SendGoal_Request_goal(::bicycle_control_interfaces::action::FollowPath_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::bicycle_control_interfaces::action::FollowPath_SendGoal_Request goal(::bicycle_control_interfaces::action::FollowPath_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_SendGoal_Request msg_;
};

class Init_FollowPath_SendGoal_Request_goal_id
{
public:
  Init_FollowPath_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowPath_SendGoal_Request_goal goal_id(::bicycle_control_interfaces::action::FollowPath_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_FollowPath_SendGoal_Request_goal(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::bicycle_control_interfaces::action::FollowPath_SendGoal_Request>()
{
  return bicycle_control_interfaces::action::builder::Init_FollowPath_SendGoal_Request_goal_id();
}

}  // namespace bicycle_control_interfaces


namespace bicycle_control_interfaces
{

namespace action
{

namespace builder
{

class Init_FollowPath_SendGoal_Response_stamp
{
public:
  explicit Init_FollowPath_SendGoal_Response_stamp(::bicycle_control_interfaces::action::FollowPath_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::bicycle_control_interfaces::action::FollowPath_SendGoal_Response stamp(::bicycle_control_interfaces::action::FollowPath_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_SendGoal_Response msg_;
};

class Init_FollowPath_SendGoal_Response_accepted
{
public:
  Init_FollowPath_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowPath_SendGoal_Response_stamp accepted(::bicycle_control_interfaces::action::FollowPath_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_FollowPath_SendGoal_Response_stamp(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::bicycle_control_interfaces::action::FollowPath_SendGoal_Response>()
{
  return bicycle_control_interfaces::action::builder::Init_FollowPath_SendGoal_Response_accepted();
}

}  // namespace bicycle_control_interfaces


namespace bicycle_control_interfaces
{

namespace action
{

namespace builder
{

class Init_FollowPath_SendGoal_Event_response
{
public:
  explicit Init_FollowPath_SendGoal_Event_response(::bicycle_control_interfaces::action::FollowPath_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::bicycle_control_interfaces::action::FollowPath_SendGoal_Event response(::bicycle_control_interfaces::action::FollowPath_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_SendGoal_Event msg_;
};

class Init_FollowPath_SendGoal_Event_request
{
public:
  explicit Init_FollowPath_SendGoal_Event_request(::bicycle_control_interfaces::action::FollowPath_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_FollowPath_SendGoal_Event_response request(::bicycle_control_interfaces::action::FollowPath_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_FollowPath_SendGoal_Event_response(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_SendGoal_Event msg_;
};

class Init_FollowPath_SendGoal_Event_info
{
public:
  Init_FollowPath_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowPath_SendGoal_Event_request info(::bicycle_control_interfaces::action::FollowPath_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_FollowPath_SendGoal_Event_request(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::bicycle_control_interfaces::action::FollowPath_SendGoal_Event>()
{
  return bicycle_control_interfaces::action::builder::Init_FollowPath_SendGoal_Event_info();
}

}  // namespace bicycle_control_interfaces


namespace bicycle_control_interfaces
{

namespace action
{

namespace builder
{

class Init_FollowPath_GetResult_Request_goal_id
{
public:
  Init_FollowPath_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::bicycle_control_interfaces::action::FollowPath_GetResult_Request goal_id(::bicycle_control_interfaces::action::FollowPath_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::bicycle_control_interfaces::action::FollowPath_GetResult_Request>()
{
  return bicycle_control_interfaces::action::builder::Init_FollowPath_GetResult_Request_goal_id();
}

}  // namespace bicycle_control_interfaces


namespace bicycle_control_interfaces
{

namespace action
{

namespace builder
{

class Init_FollowPath_GetResult_Response_result
{
public:
  explicit Init_FollowPath_GetResult_Response_result(::bicycle_control_interfaces::action::FollowPath_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::bicycle_control_interfaces::action::FollowPath_GetResult_Response result(::bicycle_control_interfaces::action::FollowPath_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_GetResult_Response msg_;
};

class Init_FollowPath_GetResult_Response_status
{
public:
  Init_FollowPath_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowPath_GetResult_Response_result status(::bicycle_control_interfaces::action::FollowPath_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_FollowPath_GetResult_Response_result(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::bicycle_control_interfaces::action::FollowPath_GetResult_Response>()
{
  return bicycle_control_interfaces::action::builder::Init_FollowPath_GetResult_Response_status();
}

}  // namespace bicycle_control_interfaces


namespace bicycle_control_interfaces
{

namespace action
{

namespace builder
{

class Init_FollowPath_GetResult_Event_response
{
public:
  explicit Init_FollowPath_GetResult_Event_response(::bicycle_control_interfaces::action::FollowPath_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::bicycle_control_interfaces::action::FollowPath_GetResult_Event response(::bicycle_control_interfaces::action::FollowPath_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_GetResult_Event msg_;
};

class Init_FollowPath_GetResult_Event_request
{
public:
  explicit Init_FollowPath_GetResult_Event_request(::bicycle_control_interfaces::action::FollowPath_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_FollowPath_GetResult_Event_response request(::bicycle_control_interfaces::action::FollowPath_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_FollowPath_GetResult_Event_response(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_GetResult_Event msg_;
};

class Init_FollowPath_GetResult_Event_info
{
public:
  Init_FollowPath_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowPath_GetResult_Event_request info(::bicycle_control_interfaces::action::FollowPath_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_FollowPath_GetResult_Event_request(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::bicycle_control_interfaces::action::FollowPath_GetResult_Event>()
{
  return bicycle_control_interfaces::action::builder::Init_FollowPath_GetResult_Event_info();
}

}  // namespace bicycle_control_interfaces


namespace bicycle_control_interfaces
{

namespace action
{

namespace builder
{

class Init_FollowPath_FeedbackMessage_feedback
{
public:
  explicit Init_FollowPath_FeedbackMessage_feedback(::bicycle_control_interfaces::action::FollowPath_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::bicycle_control_interfaces::action::FollowPath_FeedbackMessage feedback(::bicycle_control_interfaces::action::FollowPath_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_FeedbackMessage msg_;
};

class Init_FollowPath_FeedbackMessage_goal_id
{
public:
  Init_FollowPath_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_FollowPath_FeedbackMessage_feedback goal_id(::bicycle_control_interfaces::action::FollowPath_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_FollowPath_FeedbackMessage_feedback(msg_);
  }

private:
  ::bicycle_control_interfaces::action::FollowPath_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::bicycle_control_interfaces::action::FollowPath_FeedbackMessage>()
{
  return bicycle_control_interfaces::action::builder::Init_FollowPath_FeedbackMessage_goal_id();
}

}  // namespace bicycle_control_interfaces

#endif  // BICYCLE_CONTROL_INTERFACES__ACTION__DETAIL__FOLLOW_PATH__BUILDER_HPP_
