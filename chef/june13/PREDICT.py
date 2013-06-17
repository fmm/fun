#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys

f = lambda m,px:(1+(2*(1-px)))*m*px
func = lambda x,px: f(x,px) + f(10000-x,1-px)

def process():
	px = float(raw_input())
	ans=max(func(0,px),func(10000,px))
	print ans

for testcase in xrange(int(raw_input())):
	process()
