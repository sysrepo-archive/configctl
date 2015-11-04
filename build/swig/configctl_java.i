%module configctlJava
%{
#include "src/configctl.h"
#include "limits.h"

void initConfigctl(struct configctl *ctx, char *config_file, char *yang_file, char *yang_folder, int *err) {
  int rc;
  rc = configctl_init(ctx, config_file, yang_file, yang_folder);
  if (rc)*err = -3;
}

int getConfigctlInt8(struct configctl *ctx, char *path, int *err) {
  int8_t value;
  int rc;
  if (!ctx)*err = -4;
  rc = configctl_get_int8(ctx, path, &value);
  if (rc)*err = -2;
  return value;
}

short getConfigctlInt16(struct configctl *ctx, char *path, int *err) {
  int16_t value;
  int rc;
  if (!ctx)*err = -4;
  rc = configctl_get_int16(ctx, path, &value);
  if (rc)*err = -2;
  return (short) value;
}

int getConfigctlInt32(struct configctl *ctx, char *path, int *err) {
  int32_t value;
  int rc;
  if (!ctx)*err = -4;
  rc = configctl_get_int32(ctx, path, &value);
  if (rc)*err = -2;
  return (int) value;
}

long long getConfigctlInt64(struct configctl *ctx, char *path, int *err) {
  int64_t value;
  int rc;
  if (!ctx)*err = -4;
  rc = configctl_get_int64(ctx, path, &value);
  if (rc)*err = -2;
  return (long long) value;
}

int getConfigctlUint8(struct configctl *ctx, char *path, int *err) {
  uint8_t value;
  int rc;
  if (!ctx)*err = -4;
  rc = configctl_get_uint8(ctx, path, &value);
  if (rc)*err = -2;
  return (int) value;
}

short getConfigctlUint16(struct configctl *ctx, char *path, int *err) {
  uint16_t value;
  int rc;
  if (!ctx)*err = -4;
  rc = configctl_get_uint16(ctx, path, &value);
  if (rc)*err = -2;
  return (short) value;
}

int getConfigctlUint32(struct configctl *ctx, char *path, int *err) {
  uint32_t value;
  int rc;
  if (!ctx)*err = -4;
  rc = configctl_get_uint32(ctx, path, &value);
  if (rc)*err = -2;
  return (int) value;
}

long long getConfigctlUint64(struct configctl *ctx, char *path, int *err) {
  uint64_t value;
  int rc;
  if (!ctx)*err = -4;
  rc = configctl_get_uint64(ctx, path, &value);
  if (rc)*err = -2;
  return (long long) value;
}

const char *getConfigctlString(struct configctl *ctx, char *path, int *err) {
  const char *value;
  value = configctl_get_string(ctx, path);
  if (!value)*err = -2;
  return value;
}

int setConfigctlString(struct configctl *ctx, const char *location, const char *value, int *err) {
  int rc;
  rc = configctl_set_string(ctx, location, value);
  if (rc)*err = -6;
  return rc;
}

void setConfigctlInt8(struct configctl *ctx, const char *location, int value, int *err) {
  int rc;
  if (value < INT8_MIN || value > INT8_MAX)
    *err = -5;
  int8_t new_value = (int8_t) value;
  rc = configctl_set_int8(ctx, location, new_value);
  if (rc)*err = -6;
}

void setConfigctlInt16(struct configctl *ctx, const char *location, int value, int *err) {
  int rc;
  if (value < INT16_MIN || value > INT16_MAX)
    *err = -5;
  int16_t new_value = (int16_t) value;
  rc = configctl_set_int16(ctx, location, new_value);
  if (rc)*err = -6;
}

void setConfigctlInt32(struct configctl *ctx, const char *location, int value, int *err) {
  int rc;
  int32_t new_value = (int32_t) value;
  rc = configctl_set_int32(ctx, location, new_value);
  if (rc)*err = -6;
}

void setConfigctlInt64(struct configctl *ctx, const char *location, long long value, int *err) {
  int rc;
  if (value < INT64_MIN || value > INT64_MAX)
    *err = -5;
  int64_t new_value = (int64_t) value;
  rc = configctl_set_int64(ctx, location, new_value);
  if (rc)*err = -6;
}

void setConfigctlUint8(struct configctl *ctx, const char *location, int value, int *err) {
  int rc;
  if (value < 0 || value > UINT8_MAX)
    *err = -5;
  uint8_t new_value = (uint8_t) value;
  rc = configctl_set_uint8(ctx, location, new_value);
  if (rc)*err = -6;
}

void setConfigctlUint16(struct configctl *ctx, const char *location, int value, int *err) {
  int rc;
  if (value < 0 || value > UINT16_MAX)
    *err = -5;
  uint16_t new_value = (uint16_t) value;
  rc = configctl_set_uint16(ctx, location, new_value);
  if (rc)*err = -6;
}

void setConfigctlUint32(struct configctl *ctx, const char *location, long long value, int *err) {
  int rc;
  if (value < 0 || value > UINT32_MAX)
    *err = -5;
  uint32_t new_value = (uint32_t) value;
  rc = configctl_set_uint32(ctx, location, new_value);
  if (rc)*err = -6;
}

void setConfigctlUint64(struct configctl *ctx, const char *location, long long value, int *err) {
  int rc;
  if (value < 0 || value > UINT64_MAX)
    *err = -5;
  uint64_t new_value = (uint64_t) value;
  rc = configctl_set_uint64(ctx, location, new_value);
  if (rc)*err = -6;
}

void destroyConfigctl(struct configctl *ctx, int *err) {
  int rc;
  rc = configctl_destroy(ctx);
  if (rc)*err = -1;
}

int validateConfigctl(struct configctl *ctx, char *config, int *err) {
  int rc;
  rc = configctl_validate(ctx, config);
  /// if (rc)*err = -1;
  return rc;
}

void deleteConfigctlElement(struct configctl *ctx, const char *path, int *err) {
  int rc;
  rc = configctl_delete_element(ctx, path);
  if (rc)*err = -7;
}

char *err_string(int err){
    switch(err){
    case -1:return "Configctl error!";
    case -2:return "Configctl get error!";
    case -3:return "Configctl init error!";
    case -4:return "Invalid configctl context!";
    case -5:return "Number out of boundary!";
    case -6:return "Configctl set error!";
    case -7:return "Configctl delete error!";
    default:return "Unknown error!";
    }
}

%}

%include <exception.i>

%typemap(in,numinputs=0) int *err (int myerr = 0) {
    $1 = &myerr;
}

%typemap(argout) int* err {
    if(*$1 != 0) {
        SWIG_exception(SWIG_ValueError,err_string(*$1));
    }
}


void initConfigctl(struct configctl *ctx, char *config_file, char *yang_file, char *yang_folder, int *err);
void destroyConfigctl(struct configctl *ctx, int *err);
int validateConfigctl(struct configctl *ctx, char *config, int *err);
void deleteConfigctlElement(struct configctl *ctx, const char *path, int *err);

int getConfigctlInt8(struct configctl *ctx, char *path, int *err);
short getConfigctlInt16(struct configctl *ctx, char *path, int *err);
int getConfigctlInt32(struct configctl *ctx, char *path, int *err);
long long getConfigctlInt64(struct configctl *ctx, char *path, int *err);
int getConfigctlUint8(struct configctl *ctx, char *path, int *err);
short getConfigctlUint16(struct configctl *ctx, char *path, int *err);
int getConfigctlUint32(struct configctl *ctx, char *path, int *err);
long long getConfigctlUint64(struct configctl *ctx, char *path, int *err);
const char *getConfigctlString(struct configctl *ctx, char *path, int *err);

int setConfigctlString(struct configctl *ctx, const char *location, const char *value, int *err);
void setConfigctlInt8(struct configctl *ctx, const char *location, int value, int *err);
void setConfigctlInt16(struct configctl *ctx, const char *location, int value, int *err);
void setConfigctlInt32(struct configctl *ctx, const char *location, int value, int *err);
void setConfigctlInt64(struct configctl *ctx, const char *location, long long value, int *err);
void setConfigctlUint8(struct configctl *ctx, const char *location, int value, int *err);
void setConfigctlUint16(struct configctl *ctx, const char *location, int value, int *err);
void setConfigctlUint32(struct configctl *ctx, const char *location, long long value, int *err);
void setConfigctlUint64(struct configctl *ctx, const char *location, long long value, int *err);


%ignore configctl_create();
%ignore configctl_destroy(struct configctl *ctx);
%ignore configctl_init(struct configctl *ctx, char *config_file, char *yang_file, char *yang_folder);
%ignore configctl_validate(struct configctl *ctx, char *config);

%ignore configctl_get_int8  (struct configctl *ctx, char *path, int8_t     *value);
%ignore configctl_get_int16 (struct configctl *ctx, char *path, int16_t    *value);
%ignore configctl_get_int32 (struct configctl *ctx, char *path, int32_t    *value);
%ignore configctl_get_int64 (struct configctl *ctx, char *path, int64_t    *value);
%ignore configctl_get_uint8 (struct configctl *ctx, char *path, uint8_t    *value);
%ignore configctl_get_uint16(struct configctl *ctx, char *path, uint16_t   *value);
%ignore configctl_get_uint32(struct configctl *ctx, char *path, uint32_t   *value);
%ignore configctl_get_uint64(struct configctl *ctx, char *path, uint64_t   *value);
%ignore configctl_get_string(struct configctl *ctx, char *path);

%ignore configctl_set_string(struct configctl *ctx, const char *location, const char *value);
%ignore configctl_set_int8  (struct configctl *ctx, const char *location, int8_t      value);
%ignore configctl_set_int16 (struct configctl *ctx, const char *location, int16_t     value);
%ignore configctl_set_int32 (struct configctl *ctx, const char *location, int32_t     value);
%ignore configctl_set_int64 (struct configctl *ctx, const char *location, int64_t     value);
%ignore configctl_set_uint8 (struct configctl *ctx, const char *location, uint8_t     value);
%ignore configctl_set_uint16(struct configctl *ctx, const char *location, uint16_t    value);
%ignore configctl_set_uint32(struct configctl *ctx, const char *location, uint32_t    value);
%ignore configctl_set_uint64(struct configctl *ctx, const char *location, uint64_t    value);

%ignore configctl_commit(struct configctl *ctx);
%ignore configctl_delete_element(struct configctl *ctx, const char *path);
%ignore configctl_init_dir(char *path);



%include "src/configctl.h"
