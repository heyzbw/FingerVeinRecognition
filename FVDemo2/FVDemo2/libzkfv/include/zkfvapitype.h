#ifndef libfv_type_h
#define libfv_type_h

/**
*	@file		libfvtype.h
*	@brief		ָ����SDK-�ṹ�嶨��
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



#ifndef MAX_TEMPLATE_SIZE
#define MAX_TEMPLATE_SIZE 2048		/**<	ģ����󳤶� */
#endif

#ifndef MAX_FVTEMPLATE_COUNT
#define MAX_FVTEMPLATE_COUNT	6	/**<	���ָ����ģ���� */
#endif

#define FP_THRESHOLD_CODE		1	/**<	ָ��1:1��ֵ */
#define FP_MTHRESHOLD_CODE		2	/**<	ָ��1:N��ֵ */
#define FV_THRESHOLD_CODE		3	/**<	ָ����1:1��ֵ */
#define FV_MTHRESHOLD_CODE		4	/**<	ָ����1:N��ֵ */

#define BIO_TYPE_FP				0	/**<	����ʶ������:ָ��	*/
#define BIO_TYPE_FV				1	/**<	����ʶ������:ָ����	*/

#define IDENTIFY_MODE_ANY		0	/**<	��ϱȶ�ģʽ-��ͨ����	*/
#define IDENTIFY_MODE_FAKE		1	/**<	��ϱȶ�ģʽ-����ģʽ	*/
#define IDENTIFY_MODE_BOTH		2	/**<	��ϱȶ�ģʽ-��ȫģʽ	*/

#endif