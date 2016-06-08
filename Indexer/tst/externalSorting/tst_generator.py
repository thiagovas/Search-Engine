#!/usr/bin/env python


import sys
from random import randint


def main():
  n_triples = int(input())
  for i in range(n_triples):
    sys.stdout.write(str(randint(0, 1000000)))
    sys.stdout.write(' ')
    sys.stdout.write(str(randint(0, 1000000)))
    sys.stdout.write(' ')
    sys.stdout.write(str(randint(0, 1000000)))
    sys.stdout.write('\n')
  


if __name__ == '__main__':
  main()
