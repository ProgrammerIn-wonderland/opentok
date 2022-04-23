#!/usr/bin/env python

import pycurl # to fetch data
from io import BytesIO # for pycurl writing
import json # for JSON parsing
import sys # to fetch command line arguments

if (len(sys.argv) < 2):
    print("no URL specified, please try again with a URL as an argument")
    quit()

# preform request
b_obj = BytesIO() 
crl = pycurl.Curl()
crl.setopt(crl.URL, sys.argv[1])
crl.setopt(crl.WRITEDATA, b_obj)
crl.setopt(crl.USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.157 Safari/537.36")
crl.setopt(crl.FOLLOWLOCATION, 1)
crl.perform()
crl.close()

# get json data inbetween two delimiters
body = b_obj.getvalue().decode('utf8')
start = body.find("script id=\"SIGI_STATE\" type=\"application/json\">") + len("script id=\"SIGI_STATE\" type=\"application/json\">")
end = body.find("</script><script id=\"SIGI_RETRY\" type=\"application/json\">")
jsonString = body[start:end]


jsonData = json.loads(jsonString) # parse json data

# print tiktok video url parsed from json data
sys.stdout.write(jsonData["ItemList"]["video"]["preloadList"][0]["url"])
