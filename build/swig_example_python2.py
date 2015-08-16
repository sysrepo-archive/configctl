#!/usr/bin/env python2

import os
import configctl_py2 as configctl

config_file = os.path.join(os.path.dirname(__file__), "../tests/config/hello.xml")
yang_file = os.path.join(os.path.dirname(__file__), "../tests/config/hello@2015-06-08.yin")
yang_folder = os.path.join(os.path.dirname(__file__), "../tests/config")

ctl_cnf = configctl.configctl_create()

configctl.configctl_init(ctl_cnf, config_file, yang_file, yang_folder)

result = configctl.configctl_get_string(ctl_cnf, "hello/foo")
print(result)
