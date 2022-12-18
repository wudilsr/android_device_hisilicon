/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2006-2014 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef BS_SYMBOL_H
#define BS_SYMBOL_H

#include "../../base/mali_types.h"

/* enum containing the parser datatypes available.
 * DO NOT modify existing numbers unless you accept breaking all compiled binary shaders,
 * but please add new types to the end of the stuct if required.  */
enum bs_datatype
{
	DATATYPE_FLOAT = 1, /**< float, vec2, vec3, vec4 types */
	DATATYPE_INT = 2, /**< int, ivec2, ivec3, ivec4 types */
	DATATYPE_BOOL = 3, /**< bool, bvec2, bvec3, bvec4 types */
	DATATYPE_MATRIX = 4, /**< mat2, mat3, mat4 types */
	DATATYPE_SAMPLER = 5, /**< sampler1D, sampler2D, sampler3D types */
	DATATYPE_SAMPLER_CUBE = 6, /**< samplerCube type */
	DATATYPE_SAMPLER_SHADOW = 7, /**< sampler2DShadow type */
	DATATYPE_STRUCT = 8, /**< struct types */
	DATATYPE_SAMPLER_EXTERNAL = 9  /**< samplerExternal type */
};

/* enum for precision - Again, DO NOT MODIFY numbers; new entries at the end */
enum bs_precision
{
	PRECISION_LOW = 1,
	PRECISION_MEDIUM = 2,
	PRECISION_HIGH = 3
};

/* brief forward declaration */
struct bs_symbol;

/* The symbolic table struct */
struct bs_symbol_table
{
	struct bs_symbol **members;     /**< Array of struct member fields */
	u32 member_count;               /**< Number of struct member fields */
};

/* intermediate structs for storing dual info for vertex/fragment shaders */
struct bs_dual_u32
{
	u32 vertex;
	u32 fragment;
};

struct bs_dual_s32
{
	s32 vertex;
	s32 fragment;
};

/* all the known info about a symbol */
struct bs_symbol
{
	/* Symbol info */
	char *name;                               /**< Name of symbol */

	/* Type information */
	enum bs_datatype datatype;  /**< Base datatype for this datatype - a struct, a float, sampler etc. */

	union
	{
		struct
		{
			struct bs_dual_u32 bit_precision; /**< The precision of this symbol, in number of bits */
			struct bs_dual_u32 essl_precision;/**< PRECISION_HIGH, PRECISION_MEDIUM or PRECISION_LOW */
			mali_bool invariant;              /**< Is this symbol Invariant? */
			u32 vector_size;                  /**< Size of the datatype. A mat3 has size 3, a vec4 has
                                                   size 4, a sampler3D has size 3, from 1 to 4 (no max is enforced) */
			struct bs_dual_u32 vector_stride; /**< The size spanned by each "row" in this symbol, from 1 to 4 (no max is enforced) */
		} primary;                            /**< primary datatype dimensions - not used for structs */
		struct bs_symbol_table construct;     /**< Datatype subtypes - only used for structs */
	} type;                                   /**< Contains all typeinfo */

	struct bs_dual_u32 array_element_stride;  /**< Aligned size of one element, used for array indexing */
	u32 array_size;                           /**< A float[4] has array_size 4, a mat4[13] has array_size 13.
                                                   Scalars have array_size 0 */
	struct bs_dual_u32 block_size;           /**< Size of this entire symbol in cells; spanning typesize,
                                                   alignment and arrays, but not anything beyond the last used cell in the symbol.
                                                   Example: a vec3[2] symbol with array_stride=4 will have this value = 7. */

	/* Locations - Given in offset compared to the parent node */
	struct bs_dual_s32 location;

	/* Flags, hints and extra information depending on what kind of symbol this is */
	union
	{
		/* extra data, depending on whether this is a uniform, attribute or varying symbol */
		struct
		{
			u32 td_index;       /** index of a sampler in the texture descriptor remap table */
			u32 external_index; /** index of a texture external sampler in the yuv data table */
			u32 grad_index;     /** index of a grad LOD sampler in the texture size table */
		} uniform;

		struct
		{
		} attribute;

		struct
		{
			s32 attribute_copy; /**< If this is a direct copy of an attribute; the number of the attribute, otherwise -1 */
			mali_bool clamped;  /**< Is this clamped? MALI_TRUE or MALI_FALSE*/
		} varying;
	} extra;
};

/* A struct holding all locations of a uniform and a pointer to the symbol */
typedef struct bs_uniform_location
{
	struct bs_dual_s32 reg_location;    /**< register locations */
	struct
	{
		s16 sampler_location;       /**< sampler info struct index */
		s16 base_index;             /**< base addressing offset for arrays in symbol */
	} extra;                        /**< keep the 16 bit members together */
	struct bs_symbol *symbol;       /**< pointer to the symbol */
} bs_uniform_location;

/*****************************************************************************/

/**
 * @brief Allocates and returns a new symbol table capable of holding "toplevel_elements" elements at the top level of the table.
 * @param toplevel_elements The number of toplevel elements.
 * @note All members are set to NULL on allocation
 */
MALI_IMPORT struct bs_symbol_table *bs_symbol_table_alloc(u32 toplevel_elements);

/**
 * @brief Frees and depopulates a symbolic table
 * @param table The table to delete
 * @note Will delete all symbols assigned to table, but ignores any NULL-members.
 */
MALI_IMPORT void bs_symbol_table_free(struct bs_symbol_table *table);

/**
 * @brief Allocates a new symbol, initializes it and sets its name
 * @param name A name for this symbol
 * @note The name of the symbol is copied into the symbol.
 *       Anything else is set to 0. You will probably want to alter this after creation.
 */
MALI_IMPORT struct bs_symbol *bs_symbol_alloc(const char *name);

/**
 * @brief Free one symbol
 * @param the symbol to free
 * @note A parameter of NULL is silently ignored.
 */
MALI_IMPORT void bs_symbol_free(struct bs_symbol *symbol);

/**
 * @brief Lookup a location-style name in a symbol table
 * @param table The table to look in
 * @param name The location name to look for
 * @param vertex_offset ouput parameter, the offset for this name, offsetted by the vertex settings. Can be NULL
 * @param fragment_offset output parameter, the offset for this name, offsetted by the fragment settings. Can be NULL
 * @param sampler_location output parameter, the location of this symbol in the sampler array (or -1 if not a sampler). Can be NULL.
 * @return Returns the symbol.
 * @note Quite slow, running at O(n). Cache your results instead of querying this function every frame.
 *       (For the same reasons you should cache your glLocations instead of getting them every frame).
 */
MALI_IMPORT struct bs_symbol *bs_symbol_lookup(struct bs_symbol_table *table, const char *name, s32 *vertex_offset, s32 *fragment_offset, s32 *sampler_location);

/**
 * @brief Lookup a location-style name location
 * @param table The table to look in
 * @param name The location name to look for
 * @return Returns the index. -1 indicates not found.
 * @note Quite slow, running at O(n). Cache your results instead of querying this function every frame.
 *       (For the same reasons you should cache your glLocations instead of getting them every frame).
 */
MALI_IMPORT s32 bs_lookup_uniform_location(struct bs_symbol_table *table, const char *name, const char **filters, int filtercount);

/**
 * Returns true if this symbol is a sampler. Calling this function is equivalent of checking whether the symbol->datatype
 * equals either of the DATATYPE_SAMPLER_* enum values, but by using this function you also ensure you check future sampler datatypes added later.
 * @param symbol the symbol to inspect
 * @return TRUE if a sampler type, otherwise false
 */
MALI_STATIC_FORCE_INLINE mali_bool bs_symbol_is_sampler(struct bs_symbol *symbol)
{
	MALI_DEBUG_ASSERT_POINTER(symbol);
	return (
	           symbol->datatype == DATATYPE_SAMPLER ||
	           symbol->datatype == DATATYPE_SAMPLER_CUBE ||
	           symbol->datatype == DATATYPE_SAMPLER_SHADOW ||
	           symbol->datatype == DATATYPE_SAMPLER_EXTERNAL);
}

/**
 * @brief returns the number of "locations" in this symbolic table.
 * @param table the table to count.
 * @param filters a string vector with symbol's prefix to filter out
 * @param filtercount the number of elements in filters vector
 * @return the number of symbols encapsulated by this table.
 * @note
 *
 * Arrays and their first element share locations, and thus only count as ONE location in total. Structures are not adressable, but
 * may be a part of a final location.
 *
 * vec4 foo;
 * vec2 table[2];
 * struct {
 *   struct {
 *       vec4 foobar;
 *   } innerdata[2];
 * } data[17];
 *
 * The symbol foo counts as one location.
 * The symbol table counts as two locations, since "table[0]" and "table" is the same location.
 * The symbol foobar counts by itself as one location... but, since it's a member of a struct, the struct steals the location.
 * The entire innerdata struct counts by itself as no locations, but all of its contents are counted once per array element, totalling as 2 locations. But, since this is also a member of a struct, the outer struct steals the locations.
 * The entire data struct counts as no locations, but again, its contets are counted once per array elements, totalling as 34 locations.
 *
 * In total, the example has 1+2+34= 37 locations
 *
 * This function runs at O(n). For speed reasons, do not call this every frame. Cache your result.
 *
 */
MALI_IMPORT u32 bs_symbol_count_locations(struct bs_symbol_table *table, const char **filters, int filtercount);

/**
 * @brief returns the number of samplers in this symbol table.
 * @param table the table to inspect
 * @retval the number.
 * @note This function works just like its count_locations counterpart, but limited to samplers. Running at O(n).
 */
MALI_IMPORT u32 bs_symbol_count_samplers(struct bs_symbol_table *table);

/**
 * @brief returns the longest location name length used in this symbol table.
 * @param table The table to examine
 * @return returns the number of bytes used for the longest possible name in this table, string terminator excluded.
 * @note In the example under bs_symbol_count_location, the longest name is "data[16].innerdata[1].foobar", and its length is 28 characters.
 *       This function is quite slow, running at O(n). Cache your results.
 */
MALI_IMPORT u32 bs_symbol_longest_location_name_length(struct bs_symbol_table *table);

/* @brief recursive function that traverses the symbol table and fills the uniform location table.
 * @param table The table to look up in
 * @param num_locations The size of the table. This parameter is only used in the debug implementation.
 * @param location Base address of the array of bs_uniform_location to fill.
 * @param filters a string vector with symbol's prefix to filter out
 * @param filtercount the number of elements in filters vector
 * @return Returns the number of locations filled.
 */
MALI_IMPORT u32  bs_symbol_fill_location_table(struct bs_symbol_table *table, int num_locations, struct bs_uniform_location *location, const char **filters, int filtercount);

/**
 * @brief Finds the n-th location in this table, returning its symbol and position, or NULL if no more positions.
 * @param table The table to spool through
 * @param n The index of the symbol to look for. Should not be larger than the result from bs_symbol_count_locations
 * @param location input_parameter The address of the bs_uniform_location structure to be filled
 * @param filters a string vector with symbol's prefix to filter out
 * @param filtercount the number of elements in filters vector
 * @return Returns the symbol associated with this location
 * @note This function is SLOW, far slower than bs_symbol_lookup. You should definitively cache the results if you want a quick lookup.
 * This is done automatically for uniforms, by the way (bs_program->uniform_locations), and its content are provided through this function.
 */
MALI_IMPORT struct bs_symbol *bs_symbol_get_nth_location(struct bs_symbol_table *table, u32 n,
        struct bs_uniform_location *location,
        const char **filters, int filtercount);

/**
 * @brief Retrieves the number of active variables as provided by glGetActiveUniform/Attribute.
 * @param table the table to spool through
 * @return the number of variables.
 * @note
 *  This function by large works just like count_locations, with one minor difference:
 *  This function never expands the end node arrays. So while the example
 *
 *  struct {
 *      int foo[4];
 *  } data[8];
 *
 *  Would yield 4*8=32 locations...
 *
 *      data[0].foo[0]
 *      data[0].foo[1]
 *      ...
 *      data[7].foo[3]
 *
 *  ....It yields only 8 actives.
 *
 *      data[0].foo
 *      data[1].foo
 *      ...
 *      data[7].foo
 *
 *  Note that there probably is little use for this function beyond the requirements of glGetActiveUniforms/Attributes and related getters.
 *
 * @note This function is also quite slow, working at O(n).
 */
MALI_IMPORT u32 bs_symbol_count_actives(struct bs_symbol_table *table, const char **filters, int numfilters);

/**
 * @Brief enumerates through all actives just like its location counterpart. All parameters are as given in bs_symbol_get_nth_location
 *
 * @note SLOW! O(n). But since glGetActive* isn't designed to be called in tight loops, this is ok.
 */
MALI_IMPORT struct bs_symbol *bs_symbol_get_nth_active(struct bs_symbol_table *table, u32 n,
        char *namebuffer, u32 namebuffersize, const char **filters, int numfilters);

/**
 * @brief Retrieves the nth sampler in the table. SLOW.
 * @note All parameters are like in the bs_get_nth_location. This function does not return the name. There was no need.
 * @param table The symbol table to look up into, typically the uniform table.
 * @param fragment_location the corresponding fragment location to this sampler, or -1 if optimized
 * @param optimized Whether the sampler found is optimized or not.
 * @return the symbol descripting the found sampler, or NULL if asking for more samplers than available.
 */
MALI_IMPORT struct bs_symbol *bs_symbol_get_nth_sampler(struct bs_symbol_table *table, u32 n, s32 *fragment_location, mali_bool *optimized);

/**
 * @brief Updates the block_size parameter of the symbol, based on alignment and size parameters already present
 * @param symbol The symbol to be updated
 */
MALI_IMPORT void bs_update_symbol_block_size(struct bs_symbol *symbol);

/**
 * @brief Compare the types of two symbols. Struct types are given a recursive comparison.
 * @param a Symbol a to consider.
 * @param b Symbol b to consider.
 * @param buffer A buffer where an comparison log may be placed. This buffer will only be used if the return value is MALI_FALSE.
 * @param buffersize Size of the buffer.
 * @return MALI_TRUE if types are identical. MALI_FALSE otherwise.
 */
MALI_IMPORT mali_bool bs_symbol_type_compare(struct bs_symbol *a, struct bs_symbol *b, char *buffer, u32 buffersize);

/**
 * @brief Compare the precision of two symbols. Struct types are given a recursive comparison.
 * @param vs The first symbol a to consider; this will be compared on the vertex side.
 * @param fs The second symbol to consider; this will be compared on the fragment side.
 * @param buffer A buffer where an comparison log may be placed. This buffer will only be used if the return value is MALI_FALSE.
 * @param buffersize Size of the buffer.
 * @return MALI_TRUE if precisions are identical. MALI_FALSE otherwise.
 * @note Basically compares vs.type.primary.essl_precision.vertex vs fs.type.primary.essl_precision.fragment
 */
MALI_IMPORT mali_bool bs_symbol_precision_compare(struct bs_symbol *vs, struct bs_symbol *fs, char *buffer, u32 buffersize);

/**
 * @brief updates both symbols' locations and alignments with eachother's values. This is used for symbol merging
 * when you have both symbols present, and want to update them with eachother's locations and alignment.
 * @param vertex A vertex symbol, with all vertex alignments and vertex locations set properly
 * @param fragment A fragment symbol, with all fragment alignments and fragment locations set properly
 * @note This function assumes the type and structure of both inputs match. To ensure that they match, you should
 * call bs_symbol_type_compare first.
 * @note This function also handles deep (struct) symbols.
 */
MALI_IMPORT void bs_symbol_merge_shadertype_specifics(struct bs_symbol *vertex, struct bs_symbol *fragment);

#endif /* BS_SYMBOL_H */
