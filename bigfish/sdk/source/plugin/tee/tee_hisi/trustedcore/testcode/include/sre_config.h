/**
* @file sre_config.h
*
* Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
*
* ������UniDSP����ͷ�ļ����ü����غ������ \n
*/

#ifndef _SRE_CONFIG_H
#define _SRE_CONFIG_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/****************************** ����ϵͳ������Ϣ ****************************/
#define OS_SYS_CLOCK                                    361000000               // оƬ��Ƶ
#define OS_SYS_CORE_RUN_NUM                             1               // ʵ�����еĺ���,��λ����
#define OS_SYS_CORE_MAX_NUM                             1               // ���֧�ֵĺ���,��λ����
#define OS_SYS_CORE_START                               0               // ����UniDSP���ϵͳ�ĺ˺����
#define OS_SYS_CORE_MASTER                              0               // ����ID
#define OS_SYS_CORE_SMP_MASK                            0x0
#define OS_SYS_REBOOT_HOOK                              NULL            // �û��ҽӵĵ��帴λ����
#define OS_PERI_ERR_HDL_CORE                            12              // �����쳣�ӹܺ�ID��ֻ��82��Ч

/****************************** ���ö�ʱ��ģ�� ******************************/
#define OS_INCLUDE_HW_TIMER                             YES             // Ӳ����ʱ��ģ��ü�����

/****************************** ����Tick�ж�ģ�� ****************************/
#define OS_INCLUDE_TICK                                 NO             // Tick�ж�ģ��ü�����
#define OS_TICK_PER_SECOND                              5000            // Tick�ж�ʱ�䵥��

/****************************** �������ж�ģ�� ******************************/
#define OS_INCLUDE_SWI                                  YES             // ���ж�ģ��ü�����
#define OS_INCLUDE_MCSWI                                NO             // �˼����жϲü�����
#define OS_SWI_MAX_SUPPORT_NUM                         16              // ���֧�ֵ����жϸ���,��������ֵΪ125

/****************************** ��������ģ�� ********************************/
#define OS_INCLUDE_TASK                                 YES             // ����ģ��ü�����
#define OS_TSK_MAX_SUPPORT_NUM                          8               // ���֧�ֵ�������
#define OS_TSK_DEFAULT_STACK_SIZE                       0x400           // ȱʡ������ջ��С
#define OS_TSK_IDLE_STACK_SIZE                          0x400           // IDLE����ջ�Ĵ�С
#define OS_TSK_STACK_AREA_START_ADDR                    NULL            // ����ջ������ʼ��ַ��
#define OS_TSK_STACK_AREA_SIZE                          1024               // ����ջ�����С
#define OS_TSK_IDLE_HOOK                                NULL            // IDLE��������жϵ�ע�ṳ��

/****************************** ����������ģ�� ***************************/
#define OS_INCLUDE_TSKMON                               NO              // ����(ջ)���ģ��ü�����
#define OS_TSKMON_OVERRUN                               NO              // ����������ü�����
#define OS_TSKMON_OVERRUN_THRESHOLD                     20              // ���������ֵ
#define OS_TSKMON_DOMODE                                NO              // ������ѭ������ʽ
#define OS_TSKMON_STARVATION                            NO              // ����������ü�����
#define OS_TSKMON_STARVATION_THRESHOLD                  400             // ���������ֵ

/****************************** ��������ջԽ����ģ�� *********************/
#define OS_INCLUDE_TSKSTACKMON                          NO              // ����ջԽ����ü�����

/****************************** �����쳣����ģ�� ***************************/
#define OS_INCLUDE_EXCEPTION                            NO             // �쳣ģ��ü�����
#define OS_EXC_STACK_SIZE                               512             // ���������ջ��С
#define OS_EXC_PROC_HOOK                                NULL            // �쳣��Ϣ��¼�󣬸�λǰ����
#define OS_DOUBLE_EXC_STACK_START                       NULL            // DoubleException��ջ��ʼ��ַ

/****************************** ����CPUռ���ʼ�CPU�澯ģ�� *****************/
#define OS_INCLUDE_CPUP                                 NO              // CPUռ����ģ��ü�����
#define OS_CPUP_SAMPLE_RECORD_NUM                       10              // CPU����������������
#define OS_CPUP_SAMPLE_INTERVAL                         10              // ����ʱ����(��λtick)
#define OS_CPUP_WARN                                    NO              // CPUռ���ʸ澯�ü�����
#define OS_CPUP_SHORT_WARN                              80              // CPUռ���ʸ澯��ֵ(�ٷֱ�)
#define OS_CPUP_SHORT_RESUME                            75              // CPUռ���ʸ澯�ָ���ֵ(�ٷֱ�)

/****************************** ���ú�ϻ��ģ�� *****************************/
#define OS_INCLUDE_BOX                                  NO             // ��ϻ��ģ��ü�����
#define OS_BOX_SPACE_START_ADDR                         &m_aucMemRegionBox[0][0]            // ��ϻ�ӿռ���ʼ��ַ
#define OS_BOX_SPACE_LENGTH                             0xB400          // ��ϻ�ӿռ䳤��
#define OS_BOX_REGION_INIT_NUM                          40              // ��ϻ�ӵ�Ԫ������
#define OS_BOX_CLEANALL                                 NO             // ��������պ�ϻ�ӿռ�

/****************************** �����ڴ����ģ�� ***************************/
#define OS_MEM_MAX_PT_NUM                               20              // ���Դ����������������������������20������

#define OS_MEM_ALGORITHM_MCDYNFSC                       NO             // ֧�ֹ���̬FSC�ڴ��㷨
#define OS_MEM_ALGORITHM_POOL                           YES             // ֧��˽��Pool�ڴ��㷨
#define OS_MEM_ALGORITHM_MCPOOL                         NO             // ֧�ֹ���Pool�ڴ��㷨

#define OS_MEM_FSC_PT_ADDR                              &m_aucMemRegion00[0]            // ˽��FSC�ڴ������ʼ��ַ
#ifdef STB_CIPHER_DRIVER
#define OS_MEM_FSC_PT_SIZE                              0x00020000               // ˽��FSC�ڴ������С
#else
#define OS_MEM_FSC_PT_SIZE                              0x00008000               // ˽��FSC�ڴ������С
#endif

/****************************** �����ź�������ģ�� **************************/
#define OS_INCLUDE_SEM                                  YES              // �ź���ģ��ü�����
#define OS_SEM_MAX_SUPPORT_NUM                          8               // ���֧�ֵ��ź�����

/****************************** ���ú˼��ź���ģ�� **************************/
#define OS_INCLUDE_MCSEM                                NO              // �˼��ź���ģ��ü�����
#define OS_MCSEM_MAX_SUPPORT_NUM                        10               // ���֧�ֵĺ˼��ź�����

/****************************** ���ú˼�����ź��� ***************************/
#define OS_INCLUDE_MCFSEM                               NO              // �˼�����ź�ģ��ü�����

/****************************** ������Ϣ����ģ�� *****************************/
#define OS_INCLUDE_MSG                                  YES              // ��Ϣģ��ü�����
#define OS_INCLUDE_MCMSG                                NO              // �˼���Ϣģ��ü�����
#define OS_MSG_MAX_SUPPORT_NUM                          8               // ���֧�ֵ���Ϣ������

/****************************** ���ö��ͨ��ģ�� *****************************/
#define OS_INCLUDE_SYNC                                 NO             // �˼�ͬ�����ܼ��ÿ���

/****************************** ����Ӳ���ź���ģ�� ***************************/
#define OS_HWSEM_GLOBE_NUM                              0               // ȫ��Ӳ���ź���������������������˵������μ��ֲᡣ
#define OS_HWSEM_LOCAL_NUM                              0               // �ֲ�Ӳ���ź�������(ÿ�����ڵĸ���)��������������˵������μ��ֲᡣ

/****************************** ����ϵͳ����ģ�� *****************************/
#define OS_TRACE_INCLUDE                                NO              // ϵͳ����ģ����ÿ��أ�������ΪYES��ʹ����Ӳ�ж�/���ж�/�����ϵͳ���٣����ή��ϵͳ���ȵ�����
#define OS_TRACE_AREA_ADDR                              NULL            // ϵͳ���ٿռ���ʼ��ַ, ��16�ֽڶ���
#define OS_TRACE_AREA_SIZE                              0x410           // ϵͳ���ٿռ��С,������ͷ(16�ֽ�),�۳�����ͷ��СӦΪ2��N�����Ҳ�С��16
#define OS_TRACE_STUB_NUM                               10              // �������ͬʱ������ж�����

/****************************** ��������ģ�� ********************************/
#define  OS_INCLUDE_DEVICE                              NO

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_CONFIG_H */

/**
 * History:
 * 2008-02-20 l66919: Create this file.
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
 */

