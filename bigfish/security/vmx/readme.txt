vmx ǩ���ű�ʹ��˵����

������Լ��汾�������á�

1����boot ����ǩ���������ã�
	��1��key_file
		 ----  ���������Լ����á�
	��2��id_name
		 ----  id to create an individual signature ,Ĭ��û�С�
	��3��nosign_file_dir
		 ---- ԭ��������Ŀ¼
	��4��other_subarea_file
		 ---- ��boot������Ҫǩ�������ļ����������Ը��ݰ汾��ӻ�ɾ����
	��5��sign_file_dir_flash
		 ---- ǩ������д����Ŀ¼��ַ
	��6��sign_file_dir_upgrade
		 ---- ǩ������������Ŀ¼��ַ

2��boot ����ǩ���������ã�
	��1��boot_subarea_file
		 ---- boot ������Ҫǩ�������ļ��� �������Ը��ݰ汾��ӻ�ɾ����

	��2��board_CFG_file
		 ---- ����fastbootʹ�õ� cfg ����
		 ---- sample�� board_CFG_file="hi3798mdmo1d_hi3798mv100_ddr3_2gbyte_8bitx4_4layers_emmc.cfg"
	��3��hisi_sdk_path
		 ---- hisi �����汾sdk Ŀ¼��ַ��
		 ---- sample:  hisi_sdk_path="${sh_dir}/../../sdk"
	��4��x86_tool_dir
		 ---- vmx�汾 x86 ����Ŀ¼���ڵ�ַ
		 ---- sample�� x86_tool_dir="${hisi_sdk_path}/../../../../out/host/linux-x86/bin"
	��5��tool_sign_name
		 ---- boot ǩ����������
		 ---- sample�� tool_sign_name="ca_sign_tool"



�ű�ʹ�÷�����
��1�� ����ǩ�����������о���ǩ��  ��  ./vmxBuild.sh (�����κβ�����
��2�� ������������ǩ��  ��  ./vmxBuild.sh  image  ����һ����Ҫǩ����ԭ��������
			----  sample��  ./vmxBuild.sh  system.squashfs
