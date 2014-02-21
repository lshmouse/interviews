'''
Created on Apr 2, 2011

@author: liushaohui
'''

# -*- coding: utf-8 -*-
import os, sys, pexpect
password = 'xxxxxxxxxx'
p = pexpect.spawn("ssh xxxx@xxxxxxx")
i = p.expect(".*assword:")
j = p.sendline("xxxxxx")

try:
    p.interact()
    sys.exit(0)
except:
    sys.exit(1)