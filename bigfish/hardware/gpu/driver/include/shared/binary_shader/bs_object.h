/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2015 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

/**
 * @file bs_object.h
 * @brief The binary state of a program/shader object. Contains all linked/compiled states.
 */
#ifndef BS_OBJECT_H
#define BS_OBJECT_H

#include <mali_system.h>
#include <base/mali_memory.h>
#include <shared/mali_linked_list.h>
#include <shared/mali_named_list.h>

/* forward declaration */
struct bs_symbol;
struct bs_symbol_table;

enum mali_core
{
	MALI_GP = 1,
	MALI_GP2 = 2,
	MALI_55 = 3,
	MALI_110 = 4,
	MALI_200 = 5,
	MALI_400GP = 6,
	MALI_400PP = 7
	             /* insert new core here, do NOT alter the existing values */
};

/* Binary flags valid for shader objects  */
struct bs_vertex_flags
{
	enum mali_core core;                   /**< typically MALI_GP2 */
	mali_bool transform_status;            /**< Is the position given by a matrix multiplication only? */

	s32 pointsize_register;                 /**< Point size register ( row-position, not cell position - used by backend ) */
	s32 position_register;                 /**< Position varying register (row again, not cell - used by backend ) */

	u32 num_input_registers;               /**< Number of GP2 input registers used by the program (all attributes) */
	u32 num_output_registers;              /**< Number of GP2 output registers used by the program (includes varyings, position, pointsize)
                                                See the varying_stream_count flag in the main program struct for the number of generic attributes */
	u32 instruction_start;                 /**< offset (given in instruction numbers) to the first instruction */
	u32 instruction_end;                   /**< offset to one past the last instruction (given in instruction numbers) */
	u32 instruction_last_touching_input;   /**< one past the last instruction that touches the input registers.
                                                If no FINS block is given, this is equal to instruction_end. */
};

/* Binary flags valid for fragment shader objects */
struct bs_fragment_flags
{
	enum mali_core core;                   /**< typically MALI_200*/
	u32 size_of_first_instruction;         /**< We also need the size of the first instruction */
	mali_bool color_read, color_write;     /**< Is color buffer read/written to? */
	mali_bool depth_read, depth_write;     /**< Is depth buffer read/written to? */
	mali_bool stencil_read, stencil_write; /**< Is stencil buffer read/written to? */

	mali_bool used_discard;                /**< Does this shader use the discard directive? */
	mali_bool rendezvous_flag;             /**< does this shader have rendezvous points */
	u32 stack_size;                        /**< Size of the stack */
	u32 initial_stack_offset;              /**< initial stack offset */

};

/* info per attriute stream */
struct bs_attribute_stream_info
{
	u32 index;                             /* The index of this stream */
	struct bs_symbol *symbol;              /* The symbol attached to this stream */
};

/* all varying stream info for the program, stored in one struct */
struct bs_attribute_stream_set
{
	u32 count;                             /**< The number of attribute streams this program require */
	struct bs_attribute_stream_info *info; /**< An array of stream info structures, one per attribute stream in the program */
};

/* info per varying stream */
struct bs_varying_stream_info
{
	u32 offset;                            /* bytewise offset where this stream starts */
	u32 component_count;                   /* is this stream using 1, 2, 3 or 4 components */
	u32 component_size;                    /* Size requirement (in bytes) for each of the components in this stream */
};

/* all varying stream info for the program, stored in one struct */
struct bs_varying_stream_set
{
	u32 count;                             /**< The number of varying streams this program require */
	u32 block_stride;                      /**< Distance in bytes between each set of packed varying streams */
	struct bs_varying_stream_info *info;   /**< An array of stream info structures, one per varying stream in the program */
};

/* info about one sampler */
struct bs_sampler_info
{
	struct bs_symbol *symbol;              /**< Symbol of this sampler, usable information getting purposes */
	u32 td_remap_table_index;              /**< The index in the TD remap table corresponding to this sampler */
	s32 fragment_location;                 /**< The location of this sampler in the fragment shader uniform table, or -1 if optimized */

	mali_bool YUV;                         /**< MALI_TRUE if this sampler is a YUV sampler. YUV samplers takes three entries in the remap table and have valid metadata */
	s32 YUV_metadata_index;                /**< The index of the YUV metadata in the fragment uniform array corresponding to this sampler. Only valid for YUV samplers */

	mali_bool is_grad;                     /**< MALI_TRUE if this sampler is used from a grad lod sampling function. Such functions needs the texture size. */
	s32 grad_metadata_index;               /**< The index of the texture size in the fragment uniform array corresponding to this sampler. Only valid if GRAD is MALI_TRUE */

	u32 API_value;                         /**< The currently bound value of this sampler from the API */
};

/* All binary sampler information for one core, stored in one struct */
struct bs_sampler_set
{
	struct bs_sampler_info *info;          /**< An array of used samplers and their bound value  */
	u32 num_samplers;                      /**< Size of this array in elements, contains both optimized and non-optimized samplers */
	u32 td_remap_table_size;               /**< The required size of the TD remap table as seen by this program */
};

/* A uniform set struct. */
struct bs_uniform_set
{
	float *array;                          /**< The uniform array for the fragment shader */
	u32 cellsize;                          /**< The uniform array size in cells */
};

/* all shader flags. Union, to hold the overlapping set of both */
union bs_shader_object_flags
{
	/* This union holds all compiler-specific flags required by the relevant backend */
	struct bs_vertex_flags vertex;
	struct bs_fragment_flags fragment;
};

/* Shaderpass structure. One for the GP, PP and each of the pilot job passes */
struct bs_shaderpass
{
	mali_mem_handle shader_binary_mem;
	u32 shader_size;              /**< Size in bytes of the fragment binary program */

	union bs_shader_object_flags flags;
};

#ifdef MALI_BB_TRANSFORM

#define BS_POSITION_ATTRIBUTE 0xF
#define BS_POSITION_ATTRIBUTE_INDEX 0xFF
#define BS_MAXMEMORY_FOR_PATTERNS 16*9

enum bs_chunk_vertex_type
{
	BS_VERTEX_TYPE_EXPRESSION = 1,
	BS_VERTEX_TYPE_OPERAND = 2,
	BS_VERTEX_TYPE_RESULT = 3
};


enum expression_kind
{
	EXPR_ADD = 0,   /* addition */
	EXPR_SUB = 1,   /* subtraction */
	EXPR_MUL = 2,   /* multiplication */
	EXPR_DIV = 3,        /* division */
	EXPR_SWIZZLE = 4,   /* swizzle */
	EXPR_CONSTR = 5,    /* vector/matrix constructor */
	EXPR_ASSIGN = 6,     /* assignment */
	EXPR_INDEX = 7      /* array subscript */
};

enum operand_kind
{
	OPND_CONST,                  /* literal */
	OPND_LVAR,                     /* local variable */
	OPND_VUNI,                     /* uniform */
	OPND_VATT,                     /* attribute */
	OPND_VVAR                     /* varying */
};

enum expression_res_size
{
	EXPR_VEC_SIZE_1 = 1,                   /* float, int , bool*/
	EXPR_VEC_SIZE_2 = 2,                   /* vec2, ivec2, bvec2 */
	EXPR_VEC_SIZE_3 = 3,                    /* vec3, ivec3, bvec3 */
	EXPR_VEC_SIZE_4 = 4,                   /* vec4, ivec4, bvec4 */
	EXPR_MAT_SIZE_2 = 22,               /* mat2 */
	EXPR_MAT_SIZE_3 = 23,               /* mat3 */
	EXPR_MAT_SIZE_4 = 24                /* mat4 */
};

enum operand_basic_type
{
	OPND_TYPE_FLOAT = 1,
	OPND_TYPE_INT = 2,
	OPND_TYPE_BOOL = 3,
	OPND_TYPE_MATRIX = 4
};


typedef struct binary_shader_expression_item
{
	u8 type; /*Expression or operand*/
	void *data; /* data*/
} binary_shader_expression_item;

/* block EXPR */
typedef struct binary_shader_chunk_vertex_expression
{
	u8 expression_kind;                     /* represents an elementary operation, possible list of operations is given below  */
	u8 expression_res_size;               /* vector size of an expression result, possible size are given below */
	u8 expression_num_opnd;         /* number of en expression operands */
	u8 swizzle;                                  /* a mask describing how an output of an expression is constructed */
} binary_shader_chunk_vertex_expression;

/* block OPND */
typedef struct binary_shader_chunk_vertex_operand
{
	u8 operand_kind;                            /* operand kind, list of possible operands is give below */
	u8 operand_basic_type;               /* operand basic type (float, int, bool) */
	u16 padding;                                        /* unused field for alignment */
	u32 operand_index;                       /* index of an operand in an appropriate table of variables (-1 for constant operands) */
	u32 operand_value;                       /* value of an operand represented as u32 (has sense only for constants) */
} binary_shader_chunk_vertex_operand;

/* this structure describes the attributes and unifroms positions in their tables for pretransform pattern
 * particulary for now we parse only patterns like mvp*attr, or mvp*vec3(pos,1), mvp*vec2(pos,0,1)
 * mvp *vec4, mvp1*mvp2*vec4
 */
typedef struct gles_gb_cpu_pretrans_pass
{
	u16 attrib_array_pos;
	u16 mvp1_index;
	u16 mvp2_index;
	u16 mvp2_set;
	u32 value1;

} gles_gb_cpu_pretrans_pass;

#endif

/* Error log struct
 * NOTE only bs_error should reference the internals of this struct
 */
typedef struct bs_log
{
	char *log;                          /**< A dynamically built error string */
	const char *log_out_of_memory;      /**< A pointer to a constant 'out-of-mem' message */
} bs_log;


/* binary state for program objects - only valid after linking */
typedef struct bs_program
{
	/* general states */
	mali_bool linked;                      /**< Set to MALI_TRUE or MALI_FALSE, depending on whether this binary state is legal */
	struct bs_log log;                     /**< An error log describing what went wrong at the last link attempt, or NULL */

	/* texture descriptors used - for the fragment shader only */
	struct bs_sampler_set samplers;

	/* symbol tables; built while linking */
	struct bs_symbol_table *uniform_symbols; /**< The uniform symbol table for this program. */
	struct bs_symbol_table *attribute_symbols; /**< The attribute symbol table for this program. */
	struct bs_symbol_table *varying_symbols; /**< The varyings in this program (not including pointsize/position) */

#ifdef MALI_BB_TRANSFORM
	struct binary_shader_expression_item **cpu_pretrans;     /**< The expression involved in a CPU pre-transform */
	struct gles_gb_cpu_pretrans_pass *cpu_pass_parsed;   /* parsed patterns container*/
	u32  num_pass;                                  /* must not be greater then 1 for BB ( only gl_Position pass is required ) */
	int cpu_pretrans_size;     /**< CPU pre-transform actuall size */
	int gl_position_item; /* -1 if pattern has not been already parsed, 1 otherwise */
#endif

	/* all info about the standard streams */
	struct bs_varying_stream_set varying_streams; /**< Varying stream stride, count and per-stream information */
	struct bs_attribute_stream_set attribute_streams; /**< Attribute stream count and per-stream information */

	/* special varying streams (or at least the symbols that define them) */
	struct bs_symbol *varying_position_symbol;      /**< The varying position symbol */
	struct bs_symbol *varying_pointsize_symbol;     /**< The varying pointsize symbol */

	/* uniform arrays */
	struct bs_uniform_set vertex_shader_uniforms; /**< A set of uniforms for the vertex shader */
	struct bs_uniform_set fragment_shader_uniforms; /**< A set of uniforms for the fragment shader */

	/* shader passes */
	struct bs_shaderpass vertex_pass;
	struct bs_shaderpass fragment_pass;

	u32 num_fragment_pilot_job_passes;
	u32 pilot_job_uniform_offset;
	u32 pilot_job_uniform_stride;
	struct bs_shaderpass *fragment_pilot_job_passes;   /**< Array of PP pilot_job passes */

	u32 num_vertex_pilot_job_passes;
	struct bs_shaderpass *vertex_pilot_job_passes;   /**< Array of GP pilot job passes */

} bs_program;

/* binary state for shader objects - only valid after compile */
typedef struct bs_shader
{
	mali_bool compiled;                    /**< Set to MALI_TRUE if this binary shader is valid */
	struct bs_log log;                     /**< If something went wrong at the last compile attempt, this log describes what */

	void *shader_block;                    /** < The compiled shader program. */
	u32 shader_size;                       /** < Size of the data above, in bytes */

	void *binary_block;
	u32 binary_size;

	/* binary shader blocks. */
	void *varyings;                        /**< The varyings specified by the binary_shader_block */
	u32 varying_size;                      /**< Size of the block */
	void *uniforms;                        /**< The uniforms specified by the binary_shader_block */
	u32 uniform_size;                      /**< Size of the block */
	void *attributes;                      /**< The attributes specified by te binary_shader_block. Only valid for vertex shaders */
	u32 attribute_size;                    /**< Size of the block */
#ifdef MALI_BB_TRANSFORM
	void *cpu_operations_stream;                      /**< The stack of operations specified by te binary_shader_block. Only valid for vertex shaders */
	u32 cpu_operations_stream_size;                    /**< Size of the block */
#endif

	/* mainjob flags */
	union bs_shader_object_flags flags;

	/* pilot job states */
	void *pilot_jobs;                         /**< The content of the DPRO block, holding all pilot job data */
	u32 pilot_job_size;                       /**< Size of the block */

} bs_shader;


/**
 * @brief initializes a binary shader state
 * @param bs The struct to initialize
 */
MALI_IMPORT void __mali_shader_binary_state_init(bs_shader *bs);

/**
 * @brief frees all attached objects to the binary state struct, and re-initializes it
 * @param bs the struct to work with
 */
MALI_IMPORT void __mali_shader_binary_state_reset(bs_shader *bs);

/**
 * @brief initializes a program shader state
 * @param bs the struct to initialize
 */
MALI_IMPORT void __mali_program_binary_state_init(bs_program *bs);

/**
 * @brief frees all attached objects to the binary state struct, and re-initializes it
 * @param bs the struct to work with
 */
MALI_IMPORT void __mali_program_binary_state_reset(bs_program *bs);

/**
 * @brief Links the vertex object and the fragment object. Result is placed in the program object.
 * @param base_ctx Base context from which the mali memory is allocated
 * @param po The program object to recieve the new state. Any old state is overwritten as required, so init/reset this before use.
 * @param vert_obj The vertex object for us to link.
 *        May be NULL, which is useful if you do not use a geometry processor (OpenVG).
 * @param frag_obj The fragment object for us to link.
 *        May be NULL, which is useful if you are doing a pure GPGPU job with no pixel processor work component.
 * @return Returns whether this function was successful or not.
 *         On FUNCTION FAILED, refer to program log for details.
 *         On OUT OF MEMORY, no log will be generated.
 *         On SUCCESS no log will be generated.
 */
MALI_IMPORT mali_err_code __mali_link_binary_shaders(mali_base_ctx_handle base_ctx, bs_program *po, bs_shader *vert_obj, bs_shader *frag_obj) MALI_CHECK_RESULT;

/**
 * @brief Merges the MBS1 blocks found inside the vs binary, fs binary and the imprompty block defined by the "attrib block" pointer and size.
 *        The result is allocated and stored in the "binary block" pointer and size.
 * @param binary_block [out] - Pointer where the result is stored. The pointer is allocated with _mali_sys_malloc.
 * @param binary_size [out] - Number of bytes stored in the "binary block" pointer.
 * @param attrib_block - A block holding one BATT block.
 * @param attrib_size - The size of the BATT block.
 * @param vsBinary - The vertex shader binary, already compiled.
 * @param fsBinary - The fragment shader binary, already compiled
 * @return MALI_ERR_NO_ERROR on success, or MALI_ERR_OUT_OF_MEMORY on oom.
 */
MALI_EXPORT mali_err_code __mali_merge_binary_shaders(void **binary_block, u32 *binary_size, void *attrib_block, u32 attrib_size, bs_shader *vsBinary, bs_shader *fsBinary);

/**
 * @brief Stores the raw shader binary image in the shader object
 *
 * @param so    Shader object
 * @param block Raw shader binary blob
 * @param size  Binary blob size
 *
 * @return MALI_ERR_NO_ERROR on success, MALI_ERR_OUT_OF_MEMORY on OOM.
 */
MALI_EXPORT mali_err_code __mali_shader_binary_store_binary_block(bs_shader *so, const void *block, const u32 size);

#endif /* BS_OBJECT_H */

