#include "ti_msp_dl_config.h"
#include "stdint.h"
#include "board.h"
#include "OLED.h"
#include "LED.h"
#include "Trace.h"
#include "Car.h"
#include "PID.h"
#include "Encoder.h"
#include "bsp_mpu6050.h"
#include "inv_mpu.h"
#include "KEY.h"

#define STRAIGHT_SPEED 180      // 小车直行基础速度
#define LINE_FOLLOWING_SPEED 140  // 小车巡线基础速度

// 电机A转速PID初始化
PID MotorAPID;
float MotorA_Kp = 0.1984, MotorA_Ki = 0.0502, MotorA_Kd = 0.0075;
float MotorA_target = 0;
float MotorA_now = 0;
float MotorA_pidout = 0;

// 电机B转速PID初始化
PID MotorBPID;
float MotorB_Kp = 0.1984, MotorB_Ki = 0.0502, MotorB_Kd = 0.0075;
float MotorB_target = 0;
float MotorB_now = 0;
float MotorB_pidout = 0;

// 红外寻迹PID初始化
IncPID TracePID;
float Trace_Kp = 14, Trace_Ki = 0, Trace_Kd = 0;
float Trace_target = 10;
char Trace_now = 0;
float Trace_pidout = 0;

// 偏航角PID初始化
PID yawPID;
float yaw_Kp = 1.2, yaw_Ki = 0, yaw_Kd = 2.5;
float yaw_target = 180;
float yaw_now = 0;
float yaw_pidout = 0;

// MPU6050相关变量初始化
// 注：MPU6050姿态角解算需要大量栈空间，因此需要增大启动文件中Stack_Size的值（0x00004000）
float pitch = 0, roll = 0, yaw = 0;
float yawSelectedTarget = 0, yawP = 0;
float yawTarget2A_B = 0, yawTarget2C_D = 0;
float yawTarget3A_C = 0, yawTarget3B_D = 0;
float MPU6050runflag = 1;

uint8_t LED_BEEP_Flag = 0;

int main(void)
{
    uint8_t Key3Count = 0;             // 按键3计数，设定目标偏航角
    uint8_t Run = 0;                   // 小车启停运行标志位
    uint8_t SwitchTasks = 0;           // 题号标志位
    uint8_t CarStatus = 0;             // 小车状态，0直行，1寻迹
    uint8_t Task34Turn = 0;            // 第3、4题到点强制转向标志位
    uint8_t PassPointCount = 0;        // 经过标志点次数
    uint8_t PassPointTarget = 0;       // 所需过圆弧端点次数，3题4次，4题16次

	board_init();
	OLED_Init();
    OLED_ColorTurn(1);
    OLED_ShowString(2,1,"****Starting****",8);
    OLED_ShowString(4,33,"DLOU03-H",8);
    OLED_ShowString(6,25,"NUEDC-2024",8);

    MPU6050_Init();
    mpu_dmp_init();

    Encoder_Init();

    PID_Init(&MotorAPID,
             MotorA_Kp, MotorA_Ki, MotorA_Kd,
             MotorA_target, 0, 100, 0, 75); // 所用电机最大输入电压9v，电源电压12v，故PID输出限幅到75
    PID_Init(&MotorBPID,
             MotorB_Kp, MotorB_Ki, MotorB_Kd,
             MotorB_target, 0, 100, 0, 75); // 所用电机最大输入电压9v，电源电压12v，故PID输出限幅到75
    PID_Init(&yawPID,
             yaw_Kp, yaw_Ki, yaw_Kd,
             yaw_target, -5, 5, -STRAIGHT_SPEED, STRAIGHT_SPEED);
    IncPID_Init(&TracePID,
                Trace_Kp, Trace_Ki, Trace_Kd,
                Trace_target, -LINE_FOLLOWING_SPEED, LINE_FOLLOWING_SPEED);

    delay_ms(500);
    OLED_Clear();
    OLED_ColorTurn(0);
    OLED_ShowFloat(3,1,yawTarget2A_B,3,2,8);
    OLED_ShowFloat(3,65,yawTarget2C_D,3,2,8);
    OLED_ShowFloat(5,1,yawTarget3A_C,3,2,8);
    OLED_ShowFloat(5,65,yawTarget3B_D,3,2,8);

    NVIC_EnableIRQ(TIMER_PID_INST_INT_IRQN);  // 使能PID运算任务定时器
    NVIC_EnableIRQ(TIMER_1_INST_INT_IRQN);    // 使能MPU6050读取任务定时器
    while(1)
    {
        OLED_ShowFloat(1,1,yaw_now,3,2,8);
        OLED_ShowNum(1,65,MPU6050flag,1,8);

        // 仅需要时读取MPU6050数据
        if(MPU6050runflag)
        {
            // 间隔一定时间读取mpu6050数据，防止卡死
            if(MPU6050flag)
            {
                uint8_t temp;
                temp = mpu_dmp_get_data(&pitch, &roll, &yaw);
                yawP = yaw + 180;
                MPU6050flag = 0;
            }
            // 若MPU6050超时未响应则重新初始化
            if(MPU6050reInitFlag > 10)
            {
                MPU6050_Init();
                mpu_dmp_init();
                MPU6050reInitFlag = 0;
            }
        }

        // 按键3设定当前目标偏航角
        if(get_Key3Num() == 0)
        {
            Key3Count++;

            switch (Key3Count)
            {
            case 1:
                yawTarget2A_B = yawP;
                break;
            case 2:
                yawTarget2C_D = yawP;
                break;
            case 3:
                yawTarget3A_C = yawP;
                break;
            case 4:
                yawTarget3B_D = yawP;
                Key3Count = 0;
                break;
            default:
                break;
            }

            OLED_ShowFloat(3,1,yawTarget2A_B,3,2,8);
            OLED_ShowFloat(3,65,yawTarget2C_D,3,2,8);
            OLED_ShowFloat(5,1,yawTarget3A_C,3,2,8);
            OLED_ShowFloat(5,65,yawTarget3B_D,3,2,8);
        }

        // 按键1切换题目
        if(get_Key1Num() == 0)
        {
            Run = 0;
            SwitchTasks++;
            if(SwitchTasks > 4)
                SwitchTasks = 1;

            switch (SwitchTasks)
            {
            case 1:
                OLED_ShowString(7,1,"(1):A-B         ",8);
                break;
            case 2:
                OLED_ShowString(7,1,"(2):A-B-C-D-A   ",8);
                break;
            case 3:
                PassPointTarget = 4;
                OLED_ShowString(7,1,"(3):A-C-B-D-A   ",8);
                break;
            case 4:
                PassPointTarget = 16;
                OLED_ShowString(7,1,"(4):(3)x4       ",8);
                break;
            default:
                break;
            }
        }

        // 按键2确定执行
        if(get_Key2Num() == 0)
        {
            Run = !Run;
            if(Run)
            {
                delay_ms(500);
                OLED_ShowString(7,121,"*",8);
            }
        }

        if(Run)    // 小车运行
        {
            /**
             * 要求1：
             * 将小车放在位置A点，小车能自动行驶到B点停车，
             * 停车时有声光提示。用时不大于15秒。
             */
            if(SwitchTasks == 1)
            {
                // 检测不到黑线，前进
                if(get_T_ALL() == 0x00)
                {
                    MPU6050runflag = 1;

                    PID_ResetTarget(&MotorAPID, STRAIGHT_SPEED - yaw_pidout);
                    PID_ResetTarget(&MotorBPID, STRAIGHT_SPEED + yaw_pidout);

                    yawSelectedTarget = yawTarget2A_B;
                    PID_ResetTarget(&yawPID, yawSelectedTarget);

                    Car_Status(Car_F, MotorA_pidout, MotorB_pidout);
                }
                // 检测到黑线，停车，声光提示
                else
                {
                    LED_BEEP_Flag = 1;    // 启动声光提示
                    Run = 0;
                }
            }

            /**
             * 要求2：
             * 将小车放在位置A点，小车能自动行驶到B点后，沿半弧线行驶到C点，
             * 再由C点自动行驶到D点，最后沿半弧线行驶到A点停车，
             * 每经过一个点，声光提示一次。完成一圈用时不大于30秒。
             */
            if(SwitchTasks == 2)
            {
                // 直行模式，检测到黑线时声光提示并切换到寻迹模式
                if(CarStatus == 0)
                {
                    MPU6050runflag = 1;  // 启动陀螺仪

                    PID_ResetTarget(&MotorAPID, STRAIGHT_SPEED - yaw_pidout);
                    PID_ResetTarget(&MotorBPID, STRAIGHT_SPEED + yaw_pidout);

                    yawSelectedTarget = yawTarget2A_B;
                    if(PassPointCount == 2)
                        yawSelectedTarget = yawTarget2C_D;
                    PID_ResetTarget(&yawPID, yawSelectedTarget);

                    Car_Status(Car_F, MotorA_pidout, MotorB_pidout);
                    // 出现黑线
                    if(get_T_ALL() != 0x00)
                    {
                        CarStatus = 1;    // 切换到寻迹模式
                        PassPointCount++;
                        LED_BEEP_Flag = 1;    // 启动声光提示
                    }
                }
                // 寻迹模式，走过一定距离仍检测不到黑线则切换到直行模式
                if(CarStatus == 1)
                {
                    MPU6050runflag = 0;    // 关闭陀螺仪
                    // PID巡线
                    PID_ResetTarget(&MotorAPID, LINE_FOLLOWING_SPEED + Trace_pidout);
                    PID_ResetTarget(&MotorBPID, LINE_FOLLOWING_SPEED - Trace_pidout);

                    Car_Status(Car_F, MotorA_pidout, MotorB_pidout);

                    // 未检测到黑线，启动左右轮编码器计数
                    if(get_T_ALL() == 0x00)
                    {
                        switchCumulativePulse(START);

                        // 左右轮平均脉冲数超过一定值认为走出圆弧，声光提示并切换到直行
                        if(getCumulativePulse() > 550)
                        {
                            CarStatus = 0;
                            switchCumulativePulse(STOP);
                            clearCumulativePulse();
                            PassPointCount++;
                            LED_BEEP_Flag = 1;    // 启动声光提示
                        }
                    }
                    // 左右轮平均脉冲数未达到一定值时检测到黑线，则证明未出圆弧，重置累加计数值
                    else
                    {
                        switchCumulativePulse(STOP);
                        clearCumulativePulse();
                    }
                }
                // 经过4个点，停车
                if(PassPointCount == 4)
                {
                    Run = 0;
                }
            }

            /**
             * 要求3：
             * 将小车放在位置A点，小车能自动行驶到C点后，沿半弧线行驶到B点，
             * 再由B点自动行驶到D点，最后沿半弧线行驶到A点停车。
             * 每经过一个点，声光提示一次。完成一圈用时不大于40秒
             *****************************************************************
             * 要求4：
             * 按要求3的路径自动行驶4圈停车，用时越少越好
             */
            if(SwitchTasks == 3 || SwitchTasks == 4)
            {
                // 直行模式，检测到黑线时声光提示并切换到寻迹模式
                if(CarStatus == 0)
                {
                    MPU6050runflag = 1;

                    PID_ResetTarget(&MotorAPID, STRAIGHT_SPEED - yaw_pidout);
                    PID_ResetTarget(&MotorBPID, STRAIGHT_SPEED + yaw_pidout);

                    yawSelectedTarget = yawTarget3A_C;
                    if(PassPointCount == 2 || PassPointCount == 6 || PassPointCount == 10 || PassPointCount == 14)
                        yawSelectedTarget = yawTarget3B_D;
                    PID_ResetTarget(&yawPID, yawSelectedTarget);

                    Car_Status(Car_F, MotorA_pidout, MotorB_pidout);
                    // 出现黑线
                    if(get_T_ALL() != 0x00)
                    {
                        CarStatus = 1;
                        PassPointCount++;
                        if(PassPointCount == 1 || PassPointCount == 5 || PassPointCount == 9 || PassPointCount == 13)
                            Task34Turn = 1;
                        else if(PassPointCount == 3 || PassPointCount == 7 || PassPointCount == 11 || PassPointCount == 15)
                            Task34Turn = 2;
                        else
                            Task34Turn = 0;
                        LED_BEEP_Flag = 1;    // 启动声光提示
                    }
                }
                // 寻迹模式，走过一定距离仍检测不到黑线则切换到直行模式
                if(CarStatus == 1)
                {
                    MPU6050runflag = 0;

                    // 方向调整：从A出发到C，左转找线
                    if(Task34Turn == 1)
                    {
                        PID_ResetTarget(&MotorAPID, 90);
                        PID_ResetTarget(&MotorBPID, 90);
                        switchCumulativePulse(START);
                        while((getCumulativePulse() < 850) && (Run == 1))
                        {
                            if (get_Key2Num() == 0)
                            {
                                Run = 0;
                            }
                            Car_Status(Car_F, MotorA_pidout, MotorB_pidout);
                            delay_ms(5);
                        }
                        switchCumulativePulse(STOP);
                        clearCumulativePulse();

                        PID_ResetTarget(&MotorAPID, 60);
                        PID_ResetTarget(&MotorBPID, 60);
                        while((get_T_ALL() != 0x08) && (Run == 1))  // 0001000
                        {
                            if(get_Key2Num() == 0)
                            {
                                Run = 0;
                            }
                            Car_Status(Car_L, MotorA_pidout, MotorB_pidout);
                            delay_ms(5);
                        }

                        Task34Turn = 0;
                    }

                    // 方向调整：从B出发到D，右转找线
                    if(Task34Turn == 2)
                    {
                        PID_ResetTarget(&MotorAPID, 90);
                        PID_ResetTarget(&MotorBPID, 90);
                        switchCumulativePulse(START);
                        while((getCumulativePulse() < 850) && (Run == 1))
                        {
                            if(get_Key2Num() == 0)
                            {
                                Run = 0;
                            }
                            Car_Status(Car_F, MotorA_pidout, MotorB_pidout);
                            delay_ms(5);
                        }
                        switchCumulativePulse(STOP);
                        clearCumulativePulse();

                        PID_ResetTarget(&MotorAPID, 60);
                        PID_ResetTarget(&MotorBPID, 60);
                        while((get_T_ALL() != 0x08) && (Run == 1))  // 0001000
                        {
                            if((get_Key2Num() == 0))
                            {
                                Run = 0;
                            }
                            Car_Status(Car_R, MotorA_pidout, MotorB_pidout);
                            delay_ms(5);
                        }
                        Task34Turn = 0;
                    }

                    // PID巡线
                    PID_ResetTarget(&MotorAPID, LINE_FOLLOWING_SPEED + Trace_pidout);
                    PID_ResetTarget(&MotorBPID, LINE_FOLLOWING_SPEED - Trace_pidout);

                    Car_Status(Car_F, MotorA_pidout, MotorB_pidout);

                    // 未检测到黑线，启动左右轮编码器计数
                    if(get_T_ALL() == 0x00)
                    {
                        switchCumulativePulse(START);

                        // 左右轮平均脉冲数超过一定值认为走出圆弧，声光提示并切换到直行
                        if(getCumulativePulse() > 550)
                        {
                            CarStatus = 0;
                            switchCumulativePulse(STOP);
                            clearCumulativePulse();
                            PassPointCount++;
                            LED_BEEP_Flag = 1;    // 启动声光提示
                        }
                    }
                    // 左右轮平均脉冲数未达到一定值时检测到黑线，则证明未出圆弧，重置累加计数值
                    else
                    {
                        switchCumulativePulse(STOP);
                        clearCumulativePulse();
                    }
                }
                // 经过位置点达到设定次数，停车
                if(PassPointCount == PassPointTarget)
                {
                    Run = 0;
                }
            }
        }
        else    // 小车停止
        {
            PID_ResetTarget(&MotorAPID, 0);
            PID_ResetTarget(&MotorBPID, 0);
            Car_Status(Car_F, 0, 0);

            OLED_ShowString(7,121," ",8);
            MPU6050runflag = 1;
            CarStatus = 0;
            PassPointCount = 0;
        }
    }
}

// PID运算任务定时器中断函数,50ms
void TIMER_PID_INST_IRQHandler(void)
{
    // 电机A速度环PID
    MotorA_now = getEAPulseNum();
    MotorA_pidout = PID_Compute(&MotorAPID, MotorA_now);

    // 电机B速度环PID
    MotorB_now = getEBPulseNum();
    MotorB_pidout = PID_Compute(&MotorBPID, MotorB_now);

    // 寻迹PID
    Trace_now = get_Terror();
    Trace_pidout = IncPID_Compute(&TracePID, Trace_now);

    // 偏航角PID
    yaw_now = yawP;
    yaw_pidout = PID_Compute(&yawPID, yaw_now);
}

// 50ms定时器中断函数, MPU6050定时读取、声光提示
uint8_t LED_BEEP_Count = 0;
void TIMER_1_INST_IRQHandler(void)
{
    if(MPU6050flag == 0)
    {
        MPU6050flag = 1;
    }
    if(initflag == 1)
    {
        MPU6050reInitFlag++;
    }

    if(LED_BEEP_Flag)
    {
        LED_BEEP_On();
        LED_BEEP_Count++;
    }
    if(LED_BEEP_Count > 6)
    {
        LED_BEEP_Off();
        LED_BEEP_Flag = 0;
        LED_BEEP_Count = 0;
    }
}
