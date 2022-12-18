#+++++++++++++++++++++++++++++++++++++
menu "PowerManagement Config"
#+++++++++++++++++++++++++++++++++++++

config HI_DVFS_CPU_SUPPORT
	bool "CPU DVFS Support"
	default y

config HI_DVFS_CORE_SUPPORT
	bool "CORE DVFS Support"
	default y

config HI_DVFS_GPU_SUPPORT
	bool "GPU DVFS Support"
	depends on HI_GPU
	default y

config HI_AVS_SUPPORT
	bool "AVS Support"
	default y

menuconfig HI_DONGLE_CONFIG
	bool "Dongle Config"
	default n

choice
	prompt "Dongle Power Mode"
	default HI_DONGLE_MODE_NORMAL
	depends on HI_DONGLE_CONFIG

config HI_DONGLE_MODE_NORMAL
	bool "Noraml Mode(CPU:1.2G;GPUx2:250M;About 2.8W)"

config HI_DONGLE_MODE_LOW
	bool "Low Mode(CPU:1.0G;GPUx2:150M;About 2.5W)"

config HI_DONGLE_MODE_CRITICAL
	bool "Critical Low Mode(CPU:800M;GPUx1:150M;About 2.4W)"

endchoice

# for HMD power up standby
config HI_PM_POWERUP_MODE1_SUPPORT
	bool "Power Up Standby Mode1 Support"
	depends on !HI_ADVCA_SUPPORT
	default n

menuconfig HI_TEMP_CTRL_CONFIG
	bool "Temperature Control"
	default n
        config  HI_TEMP_CTRL_DOWN_THRESHOLD
                depends on HI_TEMP_CTRL_CONFIG
                hex "Down Threshold Value of Temperature"
                default 0x73 
        config  HI_TEMP_CTRL_UP_THRESHOLD
                depends on HI_TEMP_CTRL_CONFIG
                hex "Up Threshold Value of Temperature"
                default 0x64
        config  HI_TEMP_CTRL_REBOOT_THRESHOLD
                depends on HI_TEMP_CTRL_CONFIG
                hex "Reboot Threshold Value of Temperature"
                default 0x7d
#+++++++++++++++++++++++++++++++++++++
endmenu
#+++++++++++++++++++++++++++++++++++++
