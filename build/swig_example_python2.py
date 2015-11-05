#!/usr/bin/env python2

import os
import configctl_py2 as configctl

config_file = os.path.join(os.path.dirname(__file__), "../tests/config/hello.xml")
yang_file = os.path.join(os.path.dirname(__file__), "../tests/config/hello@2015-06-08.yin")
yang_folder = os.path.join(os.path.dirname(__file__), "../tests/config")

try:
    ctx = configctl.configctl_create()
    configctl.configctl_init(ctx, config_file, yang_file, yang_folder)
except:
    print("An error occured")

# be aware that this function does not work in python2
# we need to address this
#try:
#    result = configctl.configctl_get_string(ctx, "hello/foo")
#except:
#    print("An error occured")
#else:
#    print("Succes: get hello/foo -> " + result)

try:
    result = configctl.configctl_get_string(ctx, "hello/bar_error")
except:
    print("Success: Exception is thrown for geting non existing data!")

# be aware that this function does not work in python2
# we need to address this
#try:
#    result = configctl.configctl_get_string(ctx, "hello/bar")
#except:
#    print("An error occured")
#else:
#    print("Succes: get hello/bar -> " + result)

try:
    configctl.configctl_set_int8(ctx, "hello/number8", 123456)
except:
    print("Success: Exception is thrown for seting integer out of range!")

try:
    configctl.configctl_set_int8(ctx, "hello/number8", 12)
    result = configctl.configctl_get_int8(ctx, "hello/number8")
except:
    print("An error occured")
else:
    print("Succes: get hello/number8 ->" + str(result))

try:
    configctl.configctl_delete_element(ctx, "hello/foo")
    result = configctl.configctl_get_int8(ctx, "hello/foo")
except:
    print("Success: Exception is thrown for trying to get a node which was previously deleted!")

try:
    configctl.configctl_destroy(ctx)
except:
    print("An error occured")
else:
    print("Succes: freed context")




