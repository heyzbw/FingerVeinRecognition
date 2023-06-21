#ifndef libfv_errdef_h
#define libfv_errdef_h

/**
*	@file		libfverrdef.h
*	@brief		ָ����SDK-�����붨��
*	@author		scar chen
*	@date		2016-01-26
*	@version	1.0
*	@par	��Ȩ��
*				Teco
*	@par	��ʷ�汾			
*
*	@note
*
*/

#define FV_ERR_ALREADY_INIT	1	/**<	�Ѿ���ʼ�� */
#define FV_ERR_OK			0	/**<	�����ɹ� */
#define FV_ERR_INITLIB	-1	/**<	��ʼ���㷨��ʧ�� */
#define FV_ERR_INIT		-2	/**<	��ʼ���ɼ���ʧ�� */
#define FV_ERR_NO_DEVICE	-3	/**<	���豸���� */
#define FV_ERR_NOT_SUPPORT	-4	/**<	�ӿ��ݲ�֧�� */
#define FV_ERR_INVALID_PARAM	-5	/**<	��Ч���� */
#define FV_ERR_OPEN			-6	/**<	���豸ʧ�� */
#define FV_ERR_INVALID_HANDLE	-7	/**<	��Ч��� */
#define FV_ERR_CAPTURE		-8	/**<	ȡ��ʧ�� */
#define FV_ERR_EXTRACT_FP		-9	/**<	��ȡָ��ģ��ʧ�� */
#define FV_ERR_ABSORT			-10	/**<	�ж� */
#define FV_ERR_MEMORY_NOT_ENOUGH			-11	/**<	�ڴ治�� */
#define FV_ERR_BUSY			-12	/**<	��ǰ���ڲɼ� */
#define FV_ERR_ADD_FINGER		-13	/**<	���ָ��ģ��ʧ�� */
#define FV_ERR_DEL_FINGER		-14	/**<	ɾ��ָ��ʧ�� */
#define FV_ERR_ADD_VEIN		-15	/**<	��Ӿ���ģ��ʧ�� */
#define FV_ERR_DEL_VEIN		-16	/**<	ɾ��������ʧ�� */
#define FV_ERR_FAIL			-17	/**<	����ʧ�� */
#define FV_ERR_CANCEL			-18	/**<	ȡ���ɼ� */
#define FV_ERR_EXTRACT_FV		-19	/**<	��ȡָ����ģ��ʧ�� */
#define FV_ERR_VERIFY_FP		-20 /**<	�ȶ�ָ��ʧ�� */
#define FV_ERR_VERIFY_FV		-21 /**<	�ȶ�ָ����ʧ�� */
#define FV_ERR_MERGE			-22 /**<	�ϲ��Ǽ�ָ��ģ��ʧ��	*/
#define FV_ERR_FP_EXIST		-23	/**<	�ظ�ָ��ID	*/

#endif