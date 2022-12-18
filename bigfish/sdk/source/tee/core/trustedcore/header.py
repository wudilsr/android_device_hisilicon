#!/usr/bin/env python
#trustedcore package header generator
#created by h00206996

from __future__ import print_function
import struct
import os
import sys
import binascii

header_size = 0x400
kernel_load_addr = 0
global_img_symtab_offset = 0
global_img_symtab_size = 0
global_img_strtab_size = 0
global_img_bss_size = 0
rtosck_img_symtab_offset = 0
rtosck_img_symtab_size = 0
rtosck_img_strtab_size = 0
rtosck_img_bss_size = 0


ImgPath = 0
Taskname = 1
Heapsize = 3
Taskuuid = 2

#add by l00202565, set globaltask relocation info to image header
elf_class = 0
dict = { 'TEE_GOT_START' : 0,
'TEE_GOT_END' : 0,
'TEE_RELPLT_START' : 0,
'TEE_RELPLT_END' : 0,
'TEE_RELDYN_START' : 0,
'TEE_RELDYN_END' : 0,
'TEE_RELADYN_START' : 0,
'TEE_RELADYN_END' : 0,
'TEE_DYNAMIC_START' : 0,
'TEE_DYNAMIC_END' : 0,
'TEE_DYNSYM_START' : 0,
'TEE_DYNSYM_END' : 0,
'TEE_RELAPLT_START' : 0,
'TEE_RELAPLT_END' : 0
}

EI_NIDENT = 16
ELFINFO_MAG0_INDEX        = 0
ELFINFO_MAG1_INDEX        = 1
ELFINFO_MAG2_INDEX        = 2
ELFINFO_MAG3_INDEX        = 3
ELFINFO_MAG0              = '\x7f'
ELFINFO_MAG1              = 'E'
ELFINFO_MAG2              = 'L'
ELFINFO_MAG3              = 'F'
ELFINFO_CLASS_INDEX       = 4
ELFINFO_CLASS_32          = '\x01'
ELFINFO_CLASS_64          = '\x02'

def get_elf_info(readelf_args, elf_args):
    #/* get elf file class: 32 or 64 bit */
    global elf_class
    elf = open(elf_args, 'r')
    e_ident = elf.read(EI_NIDENT)
    if (e_ident[ELFINFO_MAG0_INDEX] == ELFINFO_MAG0) and \
       (e_ident[ELFINFO_MAG1_INDEX] == ELFINFO_MAG1) and \
       (e_ident[ELFINFO_MAG2_INDEX] == ELFINFO_MAG2) and \
       (e_ident[ELFINFO_MAG3_INDEX] == ELFINFO_MAG3):
        if (e_ident[ELFINFO_CLASS_INDEX] == ELFINFO_CLASS_32):
            elf_class = 0
        elif (e_ident[ELFINFO_CLASS_INDEX] == ELFINFO_CLASS_64):
            elf_class = 1
        else:
            raise RuntimeError, "The elf file class could not be determine"
    else:
        raise RuntimeError, "not a elf file"
    print("elf class : {0}".format(elf_class))
    elf.close()

    #/* get elf file relocation section info */
    #get symbol value need optmize
    global dict
    elfi = open(readelf_args, 'r')
    for eachline in elfi:
        linelist = eachline.split()
        if len(linelist) > 7:
            #print("linelist: {0}".format(linelist[7]))
            if linelist[7] == "TEE_GOT_START":
                dict['TEE_GOT_START'] = int(linelist[1], 16)
            if linelist[7] == "TEE_GOT_END":
                dict['TEE_GOT_END'] = int(linelist[1], 16)
            if linelist[7] == "TEE_RELPLT_START":
                dict['TEE_RELPLT_START'] = int(linelist[1], 16)
            if linelist[7] == "TEE_RELPLT_END":
                dict['TEE_RELPLT_END'] = int(linelist[1], 16)
            if linelist[7] == "TEE_RELDYN_START":
                dict['TEE_RELDYN_START'] = int(linelist[1], 16)
            if linelist[7] == "TEE_RELDYN_END":
                dict['TEE_RELDYN_END'] = int(linelist[1], 16)
            if linelist[7] == "TEE_RELADYN_START":
                dict['TEE_RELADYN_START'] = int(linelist[1], 16)
            if linelist[7] == "TEE_RELADYN_END":
                dict['TEE_RELADYN_END'] = int(linelist[1], 16)
            if linelist[7] == "TEE_DYNAMIC_START":
                dict['TEE_DYNAMIC_START'] = int(linelist[1], 16)
            if linelist[7] == "TEE_DYNAMIC_END":
                dict['TEE_DYNAMIC_END'] = int(linelist[1], 16)
            if linelist[7] == "TEE_DYNSYM_START":
                dict['TEE_DYNSYM_START'] = int(linelist[1], 16)
            if linelist[7] == "TEE_DYNSYM_END":
                dict['TEE_DYNSYM_END'] = int(linelist[1], 16)
            if linelist[7] == "TEE_RELAPLT_START":
                dict['TEE_RELAPLT_START'] = int(linelist[1], 16)
            if linelist[7] == "TEE_RELAPLT_END":
                dict['TEE_RELAPLT_END'] = int(linelist[1], 16)



    elfi.close()
  #add by l00202565 end

def packHeaderItem(f, img_addr, img_size, img_file):
  task_size = img_file[Heapsize]
  task_name = img_file[Taskname]
  task_uuid = img_file[Taskuuid]
  z = struct.pack('<3I20s16s',
                  img_addr,
                  img_size,
                  task_size,
                  task_name,
                  task_uuid);
  f.write(z)

def getfilesize(name):
  size = os.path.getsize(name)
  #align 4
  mod = size % 4
  if mod:
    size += 4 - mod
  return size


def generate_header(filelist, header_filename):
  with open(header_filename, 'wb') as f:
    offset = header_size

    t_filelist = filelist[1:]
    task_num = len(t_filelist)
    filesize_list = [getfilesize(i[ImgPath]) for i in filelist]

    #filesize_total = sum(filesize_list)
    filesize_total = sum(filesize_list[1:])
    #added by f00208588 for add tag 'TRUSTCORE' at the head of trustcore.img
    header_tag = 'TRSTCORE'

    print("kernel_size==0x{0:x}, load addr==0x{1:x}".format(filesize_list[0], kernel_load_addr))
    z = struct.pack('<8s6I',
                    header_tag,
                    header_size,
                    kernel_load_addr,
                    filesize_list[0],
                    task_num,
                    filesize_total,
                    kernel_got_size)
    f.write(z)

    for index, imgfile in enumerate(t_filelist):
      img_size = filesize_list[index + 1]
      print("[{0}]:img_addr=0x{1:x}, img_size=0x{2:x}, TA={3}".format(index, offset, img_size, imgfile[Taskname]))
      packHeaderItem(f, offset, img_size, imgfile)
      offset += img_size

    z = struct.pack('<4I',
                    global_img_symtab_offset,
                    global_img_symtab_size,
                    global_img_strtab_size,
                    global_img_bss_size)
    f.write(z)

    z = struct.pack('<4I',
                    rtosck_img_symtab_offset,
                    rtosck_img_symtab_size,
                    rtosck_img_strtab_size,
                    rtosck_img_bss_size)
    f.write(z)

    #add by l00202565, set globaltask relocation info to image header
    global dict
    global elf_class
    got_start = dict['TEE_GOT_START']
    got_size = dict['TEE_GOT_END'] - dict['TEE_GOT_START']
    relplt_start = dict['TEE_RELPLT_START']
    relplt_size = dict['TEE_RELPLT_END'] - dict['TEE_RELPLT_START']
    reldyn_start = dict['TEE_RELDYN_START']
    reldyn_size = dict['TEE_RELDYN_END'] - dict['TEE_RELDYN_START']
    reladyn_start = dict['TEE_RELADYN_START']
    reladyn_size = dict['TEE_RELADYN_END'] - dict['TEE_RELADYN_START']
    dynamic_start = dict['TEE_DYNAMIC_START']
    dynamic_size = dict['TEE_DYNAMIC_END'] - dict['TEE_DYNAMIC_START']
    dynsym_start = dict['TEE_DYNSYM_START']
    dynsym_size = dict['TEE_DYNSYM_END'] - dict['TEE_DYNSYM_START']
    relaplt_start = dict['TEE_RELAPLT_START']
    relaplt_size = dict['TEE_RELAPLT_END'] - dict['TEE_RELAPLT_START']

    #dump relocation info
    print("elf class: {0}".format(elf_class))
    print("got start: 0x{0:x} end: 0x{1:x}".format(dict['TEE_GOT_START'], dict['TEE_GOT_END']))
    print("relplt start: 0x{0:x} end: 0x{1:x}".format(dict['TEE_RELPLT_START'], dict['TEE_RELPLT_END']))
    print("reldyn start: 0x{0:x} end: 0x{1:x}".format(dict['TEE_RELDYN_START'], dict['TEE_RELDYN_END']))
    print("reladyn start: 0x{0:x} end: 0x{1:x}".format(dict['TEE_RELADYN_START'], dict['TEE_RELADYN_END']))
    print("dynsym start: 0x{0:x} end: 0x{1:x}".format(dict['TEE_DYNSYM_START'], dict['TEE_DYNSYM_END']))
    print("relaplt start: 0x{0:x} end: 0x{1:x}".format(dict['TEE_RELAPLT_START'], dict['TEE_RELAPLT_END']))
    print("got size: {0}".format(got_size))
    print("relplt size: {0}".format(relplt_size))
    print("reldyn size: {0}".format(reldyn_size))
    print("reladyn size: {0}".format(reladyn_size))
    print("dynamic size: {0}".format(dynamic_size))
    print("dynsym size: {0}".format(dynsym_size))
    print("relaplt size: {0}".format(relaplt_size))

    el = struct.pack('<15I',
            elf_class,
            got_start,
            got_size,
            relplt_start,
            relplt_size,
            reldyn_start,
            reldyn_size,
            reladyn_start,
            reladyn_size,
            dynamic_start,
            dynamic_size,
            dynsym_start,
            dynsym_size,
            relaplt_start,
            relaplt_size)
    f.write(el)
    #add by l00202565 end
 
    offset = header_size
    f.seek(offset)
    #write others
    for index, imgfile in enumerate(filelist):
      if index > 0:
        offset += filesize_list[index - 1]
        f.seek(offset)

      print("place img_[{0}] at 0x{1:x}".format(index, offset))
      with open(imgfile[0], 'rb') as inf:
        f.write(inf.read())

#align image file according 64 bytes
def align_image(img_name):

	img_size = os.path.getsize(img_name)
	print ("The size of image file is {0}".format(img_size))

	mod = img_size % 64
	if mod:
		img_size += 64 - mod

	with open(img_name, 'ab+') as img:
		img.seek(0,2)
		img.truncate(img_size)

	img.close()
	img_size = os.path.getsize(img_name)
	print ("After align, the size of image file is {0}".format(img_size))

#format uuid order
def format_uuid(uuid):
    uuid = list(uuid)

    uuid[0], uuid[6] = uuid[6], uuid[0]
    uuid[1], uuid[7] = uuid[7], uuid[1]
    uuid[2], uuid[4] = uuid[4], uuid[2]
    uuid[3], uuid[5] = uuid[5], uuid[3]

    uuid[8], uuid[10] = uuid[10], uuid[8]
    uuid[9], uuid[11] = uuid[11], uuid[9]

    uuid[12], uuid[14] = uuid[14], uuid[12]
    uuid[13], uuid[15] = uuid[15], uuid[13]

    return ''.join(uuid)

if __name__ == '__main__':

  filelist = []
  dst_file = sys.argv[1]
  kernel_file = sys.argv[2],
  kernel_load_addr = int(sys.argv[3], 16)
  kernel_got_size = int(sys.argv[4], 16)
  filelist.append(kernel_file)

  global_sym_head_args = sys.argv[5]
  global_sym_item = global_sym_head_args.split(',');
  global_img_symtab_offset = int(global_sym_item[0])
  global_img_symtab_size = int(global_sym_item[1], 16)
  global_img_strtab_size = int(global_sym_item[2], 16)
  global_img_bss_size = int(global_sym_item[3], 16)

  rtosck_sym_head_args = sys.argv[6]
  rtosck_sym_item = rtosck_sym_head_args.split(',');
  rtosck_img_symtab_offset = int(rtosck_sym_item[0])
  rtosck_img_symtab_size = int(rtosck_sym_item[1], 16)
  rtosck_img_strtab_size = int(rtosck_sym_item[2], 16)

  #add by l00202565, set globaltask relocation info to image header
  elf = str(sys.argv[7])
  readelf = str(sys.argv[8])

  task_args = sys.argv[9:]
  get_elf_info(readelf, elf)
  #add by l00202565 end

  for task_string in task_args:
    taskitem = task_string.split(',')
    taskitem[Heapsize] = int(taskitem[Heapsize], 16)
    taskitem[Taskuuid] = format_uuid(taskitem[Taskuuid])
    taskitem[Taskuuid] = binascii.unhexlify(taskitem[Taskuuid])

    filelist.append(taskitem)

  generate_header(filelist, dst_file)
  align_image(dst_file)
