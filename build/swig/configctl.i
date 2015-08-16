%module configctl

%{

#include <libyang/tree_data.h>
#include <libyang/tree_schema.h>
#include <libyang/libyang.h>
#include <sys/stat.h>

extern struct configctl {
        char *config_file;
        char *yang_file;
        char *yang_folder;
        LYS_INFORMAT yang_format;
        LYD_FORMAT in_format;
        LYD_FORMAT out_format;

        struct ly_ctx *libyang;
        struct lyd_node *root;
        struct lys_module *model;

        char *config;
        size_t len_config;
        char *schema;
        size_t len_schema;
};

extern struct configctl *configctl_create();
extern int configctl_init(struct configctl *ctx, char *config_file, char *yang_file, char *yang_folder);
extern int configctl_destroy(struct configctl *ctx);

extern int configctl_validate(struct configctl *ctx, char *config);

extern const char *configctl_get_string(struct configctl *ctx, char *path);
extern int8_t     *configctl_get_int8(  struct configctl *ctx, char *path);
extern int16_t    *configctl_get_int16( struct configctl *ctx, char *path);
extern int32_t    *configctl_get_int32( struct configctl *ctx, char *path);
extern int64_t    *configctl_get_int64( struct configctl *ctx, char *path);
extern uint8_t    *configctl_get_uint8( struct configctl *ctx, char *path);
extern uint16_t   *configctl_get_uint16(struct configctl *ctx, char *path);
extern uint32_t   *configctl_get_uint32(struct configctl *ctx, char *path);

%inline %{
int32_t configctl_get_int(struct configctl *ctx, char *path){
        return *configctl_get_int32(ctx, path);
}
%}

extern uint64_t   *configctl_get_uint64(struct configctl *ctx, char *path);

extern int configctl_add_string(struct configctl *ctx, const char *location, const char *value);
extern int configctl_add_int8(  struct configctl *ctx, const char *location, int8_t      value);
extern int configctl_add_int16( struct configctl *ctx, const char *location, int16_t     value);
extern int configctl_add_int32( struct configctl *ctx, const char *location, int32_t     value);
extern int configctl_add_int64( struct configctl *ctx, const char *location, int64_t     value);
extern int configctl_add_uint8( struct configctl *ctx, const char *location, uint8_t     value);
extern int configctl_add_uint16(struct configctl *ctx, const char *location, uint16_t    value);
extern int configctl_add_uint32(struct configctl *ctx, const char *location, uint32_t    value);
extern int configctl_add_uint64(struct configctl *ctx, const char *location, uint64_t    value);

extern int configctl_commit(struct configctl *ctx);
extern int configctl_delete_element(struct configctl *ctx, const char *path);
extern int confictl_add_leaf(struct configctl *ctx, const char *location, LY_DATA_TYPE type, union lyd_value_u val);
extern int configctl_init_dir(char *path);
%}

extern struct configctl {
        char *config_file;
        char *yang_file;
        char *yang_folder;
        LYS_INFORMAT yang_format;
        LYD_FORMAT in_format;
        LYD_FORMAT out_format;

        struct ly_ctx *libyang;
        struct lyd_node *root;
        struct lys_module *model;

        char *config;
        size_t len_config;
        char *schema;
        size_t len_schema;
};


extern struct configctl configctl;

extern struct configctl *configctl_create();
extern int configctl_init(struct configctl *ctx, char *config_file, char *yang_file, char *yang_folder);
extern int configctl_destroy(struct configctl *ctx);

extern int configctl_validate(struct configctl *ctx, char *config);

extern const char *configctl_get_string(struct configctl *ctx, char *path);
extern int8_t     *configctl_get_int8(  struct configctl *ctx, char *path);
extern int16_t    *configctl_get_int16( struct configctl *ctx, char *path);
extern int32_t    *configctl_get_int32( struct configctl *ctx, char *path);
extern int64_t    *configctl_get_int64( struct configctl *ctx, char *path);
extern uint8_t    *configctl_get_uint8( struct configctl *ctx, char *path);
extern uint16_t   *configctl_get_uint16(struct configctl *ctx, char *path);
extern uint32_t   *configctl_get_uint32(struct configctl *ctx, char *path);

int32_t configctl_get_int(struct configctl *ctx, char *path){
        return *configctl_get_int32(ctx, path);
}

extern uint64_t   *configctl_get_uint64(struct configctl *ctx, char *path);

extern int configctl_add_string(struct configctl *ctx, const char *location, const char *value);
extern int configctl_add_int8(  struct configctl *ctx, const char *location, int8_t      value);
extern int configctl_add_int16( struct configctl *ctx, const char *location, int16_t     value);
extern int configctl_add_int32( struct configctl *ctx, const char *location, int32_t     value);
extern int configctl_add_int64( struct configctl *ctx, const char *location, int64_t     value);
extern int configctl_add_uint8( struct configctl *ctx, const char *location, uint8_t     value);
extern int configctl_add_uint16(struct configctl *ctx, const char *location, uint16_t    value);
extern int configctl_add_uint32(struct configctl *ctx, const char *location, uint32_t    value);
extern int configctl_add_uint64(struct configctl *ctx, const char *location, uint64_t    value);

extern int configctl_commit(struct configctl *ctx);
extern int configctl_delete_element(struct configctl *ctx, const char *path);
extern int confictl_add_leaf(struct configctl *ctx, const char *location, LY_DATA_TYPE type, union lyd_value_u val);
extern int configctl_init_dir(char *path);
%}

extern struct configctl {
        char *config_file;
        char *yang_file;
        char *yang_folder;
        LYS_INFORMAT yang_format;
        LYD_FORMAT in_format;
        LYD_FORMAT out_format;

        struct ly_ctx *libyang;
        struct lyd_node *root;
        struct lys_module *model;

        char *config;
        size_t len_config;
        char *schema;
        size_t len_schema;
};


extern struct configctl configctl;

extern struct configctl *configctl_create();
extern uint64_t   *configctl_get_uint64(struct configctl *ctx, char *path);

extern int configctl_add_string(struct configctl *ctx, const char *location, const char *value);
extern int configctl_add_int8(  struct configctl *ctx, const char *location, int8_t      value);
extern int configctl_add_int16( struct configctl *ctx, const char *location, int16_t     value);
extern int configctl_add_int32( struct configctl *ctx, const char *location, int32_t     value);
extern int configctl_add_int64( struct configctl *ctx, const char *location, int64_t     value);
extern int configctl_add_uint8( struct configctl *ctx, const char *location, uint8_t     value);
extern int configctl_add_uint16(struct configctl *ctx, const char *location, uint16_t    value);
extern int configctl_add_uint32(struct configctl *ctx, const char *location, uint32_t    value);
extern int configctl_add_uint64(struct configctl *ctx, const char *location, uint64_t    value);

extern int configctl_commit(struct configctl *ctx);
extern int configctl_delete_element(struct configctl *ctx, const char *path);
extern int confictl_add_leaf(struct configctl *ctx, const char *location, LY_DATA_TYPE type, union lyd_value_u val);
extern int configctl_init_dir(char *path);

