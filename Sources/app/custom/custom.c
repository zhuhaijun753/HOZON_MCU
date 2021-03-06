#include <app/can_mgr/can_mgr.h>
#include <app/scom/scom_tl.h>
#include <config.h>
#include <mid/kernel/kernel.h>
#include <mid/kernel/task.h>
#include <scom.h>
#include <scom_msg_def.h>
#include <string.h>
#include <sys/_stdint.h>
#include <timer.h>
#include <pm.h>
#include <app/custom/custom.h>
#include <app/can_mgr/can_broadCast.h>
#include <app/can_mgr/can_basic.h>
#include <app/nm_osek/nm_osekCore.h>
#include <app/can_mgr/canbus_off.h>
#include <app/can_mgr/can_basic_cfg.h>

extern CAN_BASIC_CFG_ST can_basic_cfg;

unsigned char custom_can_ctrl_state = 0;


/*合众维护开始*/
unsigned char buf_0x440state[8];
unsigned char buf_0x445state[8];
unsigned char buf_0x526state[8];
unsigned char buf_0x3d2state[8];
/*合众维护结束*/


#if USED_NM_OSEK
extern NMControlBlock_ST  nm_OsekCB[2];//定义两个nm控制块变量;

#endif

/*
    ctrl_value  1:禁止收发，0：允许收发
*/
void custom_CAN_CTRL(MES_TYPE_E mes_type, unsigned char ctrl_value)
{
    switch (mes_type)
    {
        case mes_app:
            {
                if (ctrl_value == 0)
                {
                    custom_can_ctrl_state &= (~APP_DIS);
                    printk(PRINTK_LEVEL_LOG, "msg APP EN");
                }
                else if (ctrl_value == 1)
                {
                    custom_can_ctrl_state |= APP_DIS;
                    printk(PRINTK_LEVEL_LOG, "msg APP DISEN");
                }
                else
                {}

                break;
            }

        case mes_NM:
            {
                if (ctrl_value == 0)
                {
                    custom_can_ctrl_state &= (~NM_DIS);
                    printk(PRINTK_LEVEL_LOG, "msg NM EN");
                }
                else if (ctrl_value == 1)
                {
                    custom_can_ctrl_state |= NM_DIS;
                    
                    printk(PRINTK_LEVEL_LOG, "msg NM DISEN");
                }
                else
                {
                    //
                }


                break;
            }

        case mes_all:
            {
                if (ctrl_value == 0)
                {
                    //  custom_can_ctrl_state &=(~ALL_DIS);
                    custom_can_ctrl_state &= (~NM_DIS);
                    custom_can_ctrl_state &= (~APP_DIS);
                    //D_Online(0);
                    //TalkNM(0);
                    printk(PRINTK_LEVEL_LOG, "msg ALL EN");
                }
                else if (ctrl_value == 1)
                {
                    //custom_can_ctrl_state |=ALL_DIS;
                    custom_can_ctrl_state |= NM_DIS;
                    custom_can_ctrl_state |= APP_DIS;
                    //D_Offline(0);
                    //SilentNM(0);
                    printk(PRINTK_LEVEL_LOG, "msg ALL DISEN");
                }
                else
                {
                    //
                }

                break;
            }

        default:
            {
                //打印消息类型错误
                break;
            }
    }
}



static int scom_Custom_Msg_Proc(unsigned char msgid, unsigned char *msg,
                                unsigned int len)//此函数在SCOM任务，不会被SCOM任务本身打断
{
    unsigned int id;
    unsigned char port;
    unsigned char lenaa;
    unsigned char *pmsg;
    unsigned char num;
    unsigned int cycle;

    if (len < 1)
    {
        return 1;
    }

    switch (msgid)
    {
        case SCOM_TL_CMD_CTRL:   // 同步事件性报文。
        {
			if (*msg == 0x01)		//事件性报文。
			{
			
				id = ((msg[4] << 24) + (msg[3] << 16) + (msg[2] << 8) + msg[1]);
				port = msg[5];
				lenaa = msg[6];
				pmsg = (msg + 7);
				num = *(msg + 7 + msg[6]);
				cycle = (msg[7 + msg[6] + 1] + (msg[7 + msg[6] + 2] << 8) + (msg[7 + msg[6] + 3] << 16) +
										(msg[7 + msg[6] + 4] << 24));
			
				BC_Event_handle(id, port, lenaa, pmsg, num, cycle);
			}

			break;
        }

        case SCOM_MPU_MCU_VIRTUAL_ON:   //维护虚拟ON线
        {
			update_NM_Local_WakeupCondition(WP_TYPE_ON_VT,msg[0]);
			local_Condition_trigger_NM();
			pm_set_virtual_on(msg[0]);//铏氭嫙on绾夸繚鎸佸敜閱�	
            break;
        }
		case SCOM_MPU_MCU_0x440:      // 合众，维护0X440报文
		{
			if(len == 8)
			{
				memcpy(buf_0x440state,msg,8);				
			}
			else
			{
				printk(PRINTK_LEVEL_LOG, "0x440 len is wrong!!!");
			}
			
			break;	
		}
		case SCOM_MPU_MCU_0x445:      // 合众，维护0X445报文
		{
			if(len == 8)
			{
				memcpy(buf_0x445state,msg,8);				
			}
			else
			{
				printk(PRINTK_LEVEL_LOG, "0x445 len is wrong!!!");
			}

			break;  
		}
		case SOCM_MCU_MPU_0x526:      // 合众，维护0X526报文
		{
			if(len == 8)
			{
				memcpy(buf_0x526state,msg,8);				
			}
			else
			{
				printk(PRINTK_LEVEL_LOG, "0x526 len is wrong!!!");
			}

			break;
		}
		case SCOM_MCU_MPU_0x3d2:
		{
			if(len == 8)
			{
				memcpy(buf_0x3d2state,msg,8);				
			}
			else
			{
				printk(PRINTK_LEVEL_LOG, "0x3d2 len is wrong!!!");
			}

			break;
		}
		case SCOM_MPU_MCU_CAN_CTRL:
            {
                custom_CAN_CTRL(msg[0], msg[1]);
                break;
            }
		default:
            break;
    }

    return 0;
}




void custom_evt_proc(CUSTOM_EVENT evt)
{
    ;
}

void scom_Custom_Init(void)
{
    scom_reg_custom_msg_cb(scom_Custom_Msg_Proc);  //注册私有协议回调函数
    memset(buf_0x440state,0,8);                  //给定初始值
	memset(buf_0x445state,0,8);
	buf_0x445state[5] = 16;
	buf_0x445state[5] = buf_0x445state[5]<<2;
	buf_0x445state[6] = 16;
	buf_0x445state[6] = buf_0x445state[6]<<2;
}


