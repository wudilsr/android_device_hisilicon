/*reference arm-linux-androideabi-ld.bfd --verbose*/
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS
{
    . = 0x00000000;

    .globaltask : {
        PROCESS_START = .;
        *global_task.o(.text.start*)
    }

    /*TEE export sections*/
    TEE_SYMTAB_START = .;
    __tee_symtab : {
        *(__tee_symtab)
    }
    . = ALIGN(0x4);
    TEE_SYMTAB_END = .;


    TEE_SYMSTR_START = .;
    __tee_symstr : {
         *(__tee_symstr)
    }

    .text : {
        TEE_TEXT_START = .;
        *(.text)           /* .text sections (code) */
    }


    .data :  {
        *(.data)
    }

    .rel.dyn : {
        TEE_GOT_START = .;
        *(.rel.dyn)
    }

    .bss : {
        TEE_BSS_START = .;
        *(.bss)
    }

    TEE_LIB_END = .;
}
