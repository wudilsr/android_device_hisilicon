Purpose: read a 'bootargs_input.txt' to generat 'bootargs.bin' and 'Partition_table.xml'.
Command: Usage: mkbootargs:
       -r bootargs_input: read a bootargs.txt
       -o bootargs_bin: write a bootargs.bin
       -s bootargssize: size in KB. usually, bootargssize is set to the bootargs partition size. default:512.
       -p SPI flash size: size in MB. usually, SPI flash size-Total partition size is set to 'other' partition of SPI flash . default:0MB.
       -n Nand flash size: size in MB. usually, Nand flash size-Total partition size is set to 'other' partition of Nand flash . default:256MB.
       mkbootargs will read a 'bootargs_input.txt' and generat a 'bootargs.bin' and 'Partition_table.xml'.
Example:./makebootargs -s 64
