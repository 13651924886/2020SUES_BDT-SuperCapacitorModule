#include "Start_Task.h"

uint32_t test_dT_1000hz[3],test_rT[6];

static void Loop_1000Hz(void)	//1msִ��һ�Σ�ִ��ʱ���ԼΪ
{
	test_dT_1000hz[0] = test_dT_1000hz[1];
	test_rT[3] = test_dT_1000hz[1] = GetSysTime_us ();
	test_dT_1000hz[2] = (u32)(test_dT_1000hz[1] - test_dT_1000hz[0]) ;//test_dT_1000hz[2] �Ǹ�����ʱ��Ƭ����
//////////////////////////////////////////////////////////////////////	
			
			SuperCapControl_Task();
//////////////////////////////////////////////////////////////////////	
			test_rT[4]= GetSysTime_us ();
			test_rT[5] = (u32)(test_rT[4] - test_rT[3]) ;	//test_rT[5] rT��˼��RunTime ��1000HZʱ��Ƭ�������ִ��ʱ��
}

static void Loop_500Hz(void)	//2msִ��һ��   ��̬���ٶȻ���������
{	

}

static void Loop_200Hz(void)	//5msִ��һ��  RPY���㡢��̬�ǶȻ�
{
}
static void Loop_100Hz(void)	//10msִ��һ�Σ�ִ��ʱ���ԼΪ20us  �߶��ٶȻ����߶Ȼ�
{
//			test_rT[0]= GetSysTime_us ();
////////////////////////////////////////////////////////////////////////				
			OLED_Task();

////////////////////////////////////////////////////////////////////////		
//			test_rT[1]= GetSysTime_us ();
//			test_rT[2] = (u32)(test_rT[1] - test_rT[0]) ;	//test_rT[2] rT��˼��RunTime ��100HZʱ��Ƭ�������ִ��ʱ��
				
}

static void Loop_50Hz(void)	//20msִ��һ��   λ���ٶȻ�
{	
	
}

static void Loop_20Hz(void)	//50msִ��һ��
{	

}

static void Loop_2Hz(void)	//500msִ��һ��
{

}
//ϵͳ�������ã�������ִͬ��Ƶ�ʵġ��̡߳�
static sched_task_t sched_tasks[] = 
{
	{Loop_1000Hz,1000,  0, 0},			//void(*task_func)(void); ����ָ��  ָ����������ͣ�int ���γ�����float��ָ�� ��ַ)
	{Loop_500Hz , 500,  0, 0},			//uint16_t rate_hz;
	{Loop_200Hz , 200,  0, 0},			//uint16_t interval_ticks;
	{Loop_100Hz , 100,  0, 0},			//uint32_t last_run; 
	{Loop_50Hz  ,  50,  0, 0},
	{Loop_20Hz  ,  20,  0, 0},
	{Loop_2Hz   ,   2,  0, 0},
};
//�������鳤�ȣ��ж��߳�����
#define TASK_NUM (sizeof(sched_tasks)/sizeof(sched_task_t))

void Scheduler_Setup(void)
{
	uint8_t index = 0;
	//��ʼ�������
	for(index=0;index < TASK_NUM;index++)
	{
		//����ÿ���������ʱ������
		sched_tasks[index].interval_ticks = TICK_PER_SECOND/sched_tasks[index].rate_hz; //  TICK_PER_SECOND = 1000
		//�������Ϊ1��Ҳ����1ms
		if(sched_tasks[index].interval_ticks < 1)
		{
			sched_tasks[index].interval_ticks = 1;
		}
	}
}
//��������ŵ�main������while(1)�У���ͣ�ж��Ƿ����߳�Ӧ��ִ��
void Scheduler_Run(void)
{
	uint8_t index = 0;
	//ѭ���ж������̣߳��Ƿ�Ӧ��ִ��

	
	for(index=0;index < TASK_NUM;index++)
	{
		//��ȡϵͳ��ǰʱ�䣬��λMS
		uint32_t tnow = SysTick_GetTick();//��ȡ��systime_ms��ֵ����ֵ��Systick_Handler��ÿ1ms�ݼ�1
		//�����жϣ������ǰʱ���ȥ��һ��ִ�е�ʱ�䣬���ڵ��ڸ��̵߳�ִ�����ڣ���ִ���߳�
		if(tnow - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
		{
			
			//�����̵߳�ִ��ʱ�䣬������һ���ж�
			sched_tasks[index].last_run = tnow;
			//ִ���̺߳�����ʹ�õ��Ǻ���ָ��
			sched_tasks[index].task_func();

		}	 
	}
	

}
