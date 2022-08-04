#ifndef PID
#define PID

#include "main.h"

/* pid控制器 结构体 */
typedef struct
{
    float target_val;        //目标值
    float actual_val;        //实际值
    float err;               //定义偏差值
    float err_last;          //定义上一个偏差值
    float Kp,Ki,Kd;          //定义比例、积分、微分系数
    float integral;          //定义积分值
}_pid;


//左右轮pid控制器结构体
extern _pid pid_left_speed, pid_right_speed;  
extern _pid pid_left_location, pid_right_location;  

void  PID_param_init(void);
void  set_pid_target(_pid *pid, float temp_val);
float get_pid_target(_pid *pid);
void  set_p_i_d(_pid *pid, float p, float i, float d);

/* pid算法 */
float speed_pid_realize(_pid *pid, float actual_val);
float Location_pid_realize(_pid *pid, float actual_val);



#endif



