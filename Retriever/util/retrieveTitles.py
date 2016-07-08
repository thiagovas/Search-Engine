#!/usr/bin/env python
# coding: utf-8
# By Thiago Silva


import urllib2, sys
from BeautifulSoup import BeautifulSoup


if len(sys.argv) != 3:
  print 'Incorrect arguments'
  print 'Usage: python ' + sys.argv[0] + ' [Input filename] [Output filename]'
else:
  filenamein = sys.argv[1]
  filenameout = sys.argv[2]
  fin = open(filenamein, 'r')
  out = open(filenameout, 'w')
  
  print 'Input file: ' + filenamein
  print 'Output file: ' + filenameout
  for line in fin.readlines():
    url = line.split(' ')[1][:-1]
    print 'Retrieving: ' + url
    try:
      soup = BeautifulSoup(urllib2.urlopen(url))
      if soup.title != None:
        title = soup.title.string
        title.replace('\n', ' ')
        title.replace('\t', ' ')
        title.replace('\0', ' ')
        for i in range(len(title)):
          sys.stdout.write(ord(title[i]))
        print ''
        title = (url + ' ' + soup.title.string + '\n').encode('utf-8')
        out.write(title)
      else:
        out.write(url + ' None\n')
    except urllib2.HTTPError:
        out.write(url + ' None\n')
        
  
  out.close()
  fin.close()
