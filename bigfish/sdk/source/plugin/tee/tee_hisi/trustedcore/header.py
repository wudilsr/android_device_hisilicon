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

ImgPath = 0
Taskname = 1
Heapsize = 3
Taskuuid = 2

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
      print("[{0}]:img_addr=0x{1:x}, img_size=0x{2:x}".format(index, offset, img_size))
      packHeaderItem(f, offset, img_size, imgfile)
      offset += img_size


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

if __name__ == '__main__':

  filelist = []
  dst_file = sys.argv[1]
  kernel_file = sys.argv[2],
  kernel_load_addr = int(sys.argv[3], 16)
  kernel_got_size = int(sys.argv[4], 16)
  filelist.append(kernel_file)

  task_args = sys.argv[5:]

  for task_string in task_args:
    taskitem = task_string.split(',')
    taskitem[Heapsize] = int(taskitem[Heapsize], 16)
    taskitem[Taskuuid] = binascii.unhexlify(taskitem[Taskuuid])

    filelist.append(taskitem)

  generate_header(filelist, dst_file)
