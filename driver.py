#!/usr/bin/env python3

import os
import subprocess
import numpy as np
import sys

size = int(sys.argv[1])
times = 100

result = open('result', 'a')

for j in range(times):
	subprocess.run(('taskset 0x1 ./test ' + str(size)).split(' '))

f = open('experiment', 'r')
contents = f.read().split('\n')
contents.remove('')
f.close()

orig = []
new = []

for j in contents:
	raw = j.split(' ')
	orig.append(raw[0])
	new.append(raw[1])

orig = list(map(int, orig))
new = list(map(int, new))

sum, cnt = 0, 0
mean, std = np.mean(orig), np.std(orig)
for j in orig:
	if abs(j - mean) <= 2 * std:
		sum += j
		cnt += 1

result.write('{} {} '.format(size, sum / cnt))

sum, cnt = 0, 0
mean, std = np.mean(new), np.std(new)
for j in new:
	if abs(j - mean) <= 2 * std:
		sum += j
		cnt += 1

result.write('{}\n'.format(sum / cnt))

result.close()
