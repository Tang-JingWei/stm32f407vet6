#include "pid.h"

//左右轮pid控制器结构体
_pid pid_left_speed, pid_right_speed;
_pid pid_left_location, pid_right_location;

/**
 * @brief  PID参数初始化
 *	@note 	无
 * @retval 无
 */
void PID_param_init()
{
  /************* Location **************/
  /* left pid结构体初始化 */
  pid_left_location.target_val = 0.0;
  pid_left_location.actual_val = 0.0;
  pid_left_location.err = 0.0;
  pid_left_location.err_last = 0.0;
  pid_left_location.integral = 0.0;

  /* pid 参数 */
  pid_left_location.Kp = 0.13;
  pid_left_location.Ki = 0.003;
  pid_left_location.Kd = 0.002;

  /* right pid结构体初始化 */
  pid_right_location.target_val = 0.0;
  pid_right_location.actual_val = 0.0;
  pid_right_location.err = 0.0;
  pid_right_location.err_last = 0.0;
  pid_right_location.integral = 0.0;

  /* pid 参数 */
  pid_right_location.Kp = 0.13;
  pid_right_location.Ki = 0.003;
  pid_right_location.Kd = 0.002;

  /************** Speed *************/
  /* left pid结构体初始化 */
  pid_left_speed.target_val = 0.0;
  pid_left_speed.actual_val = 0.0;
  pid_left_speed.err = 0.0;
  pid_left_speed.err_last = 0.0;
  pid_left_speed.integral = 0.0;

  /* pid 参数 */
  pid_left_speed.Kp = 4;
  pid_left_speed.Ki = 0.01;
  pid_left_speed.Kd = 0.00;

  /* right pid结构体初始化 */
  pid_right_speed.target_val = 0.0;
  pid_right_speed.actual_val = 0.0;
  pid_right_speed.err = 0.0;
  pid_right_speed.err_last = 0.0;
  pid_right_speed.integral = 0.0;

  /* pid 参数 */
  pid_right_speed.Kp = 4;
  pid_right_speed.Ki = 0.01;
  pid_right_speed.Kd = 0.00;
}

/**
 * @brief  设置目标值
 * @param  val		目标值
 *	@note 	无
 * @retval 无
 */
void set_pid_target(_pid *pid, float temp_val)
{
  pid->target_val = temp_val; // 设置当前的目标值
}

/**
 * @brief  获取目标值
 * @param  无
 *	@note 	无
 * @retval 目标值
 */
float get_pid_target(_pid *pid)
{
  return pid->target_val; // 设置当前的目标值
}

void set_p_i_d(_pid *pid, float p, float i, float d)
{
  pid->Kp = p; // 设置比例系数 P
  pid->Ki = i; // 设置积分系数 I
  pid->Kd = d; // 设置微分系数 D
}

/**
 * @brief  根据实际速度获得期望pwm PID算法实现
 * @param  actual_val:实际值
 *	@note 	无
 * @retval 通过PID计算后的输出 pwm
 */
float speed_pid_realize(_pid *pid, float actual_val)
{
  /*计算目标值与实际值的误差*/
  pid->err = pid->target_val - actual_val;

  if ((pid->err < 1) && (pid->err > -1)) //假如以最大允许速度偏差运行1分钟，输出轴最大偏差为半圈
  {
    pid->err = 0.0f;
  }

  pid->integral += pid->err; // 误差累积

  /*积分限幅*/
  if (pid->integral >= 50000)
  {
    pid->integral = 50000;
  }
  else if (pid->integral < -50000)
  {
    pid->integral = -50000;
  }

  /*PID算法实现*/
  pid->actual_val = pid->Kp * pid->err + pid->Ki * pid->integral + pid->Kd * (pid->err - pid->err_last);

  /*误差传递*/
  pid->err_last = pid->err;

  /*返回当前实际值*/
  return pid->actual_val;
}

/**
 * @brief  根据实际路程获得期望速度  PID算法实现
 * @param  actual_val:实际值
 *	@note 	无
 * @retval 通过PID计算后的输出 速度
 */
float Location_pid_realize(_pid *pid, float actual_val)
{
  /*计算目标值与实际值的误差*/
  pid->err = pid->target_val - actual_val;

  if ((pid->err < 10) && (pid->err > -10)) //假如以最大允许速度偏差运行1分钟，输出轴最大偏差为半圈
  {
    pid->err = 0.0f;
  }

  pid->integral += pid->err; // 误差累积

  /*积分限幅*/
  if (pid->integral >= 15000)
  {
    pid->integral = 15000;
  }
  else if (pid->integral < -15000)
  {
    pid->integral = -15000;
  }

  /*PID算法实现*/
  pid->actual_val = pid->Kp * pid->err + pid->Ki * pid->integral + pid->Kd * (pid->err - pid->err_last);

  /*误差传递*/
  pid->err_last = pid->err;

  /* 速度上限处理 */
  if ((pid->actual_val) > 350)
  {
    pid->actual_val = 350;
  }
  else if ((pid->actual_val) < -350)
  {
    pid->actual_val = -350;
  }

  /*返回当前实际值*/
  return pid->actual_val;
}
