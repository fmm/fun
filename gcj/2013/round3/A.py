#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys

maxn = 37

def func(cover,my,have,bet):
  work = list(bet)
  put = [0]*maxn
  for i in xrange(maxn):
    if i == cover:
      my = my + 1
    must = my - work[i]
    if have < must:
      return (False,0)
    if must > 0:
      have = have - must
      work[i] = my
      put[i] = must
  return (True,36./cover * (sum(put[0:cover])) - (sum(put)))

def process(testcase):
  B,N = map(int,raw_input().split())
  X = map(int,raw_input().split())
  X = X + [0]*(maxn-N)
  X.sort()
  ret = 0
  for j in xrange(1,maxn+1):
    i,add = 0, int(1e12)
    while add>0:
      ni = i + add
      ok, f = func(j,ni,B,X)
      if ok:
        ret = max(ret,f)
        i = ni
      else:
        add>>=1
  print "Case #{0}: {1:.10f}".format(testcase,ret)

for testcase in xrange(int(raw_input())):
  process(testcase+1)
