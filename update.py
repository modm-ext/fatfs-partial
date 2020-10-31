# Script is tested on OS X 10.12
# YOUR MILEAGE MAY VARY

import re, os, io, time
import shutil
import zipfile
import subprocess
import urllib.request
from pathlib import Path

source_paths = [
    "LICENSE",
    "source/",
]

urls = {
    "full": ("http://elm-chan.org/fsw/ff/00index_e.html",
            r"arc/ff.+?\.zip",
             "http://elm-chan.org/fsw/ff/patches.html",
            r"\"(patch/ff.+_p\d+\.diff)\""),
    "tiny": ("http://elm-chan.org/fsw/ff/00index_p.html",
            r"arc/pff.+?\.zip",
             "http://elm-chan.org/fsw/ff/pfpatches.html",
            r"\"(patch/ff.+_p\d+\.diff)\"")
}

hdr = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11',
       'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
       'Accept-Charset': 'ISO-8859-1,utf-8;q=0.7,*;q=0.3',
       'Accept-Encoding': 'none',
       'Accept-Language': 'en-US,en;q=0.8',
       'Connection': 'keep-alive'}

def get_file(url):
    attempts = 60
    file = None
    while attempts > 0:
        try:
            file = urllib.request.urlopen(urllib.request.Request(url, headers=hdr)).read()
            break
        except:
            attempts -= 1
            print("Failed '{}' #{}".format(url, attempts))
            time.sleep(1)
    if file is None:
        print("URL Request expired")
        exit(1)
    return file

def get_regex(url, regex):
    return re.findall(regex, get_file(url).decode("utf-8"))

for key, (umain, rzip, upatch, rpatch) in urls.items():
    # Download main zip file
    zipf = os.path.join(os.path.dirname(umain), get_regex(umain, rzip)[0])
    z = zipfile.ZipFile(io.BytesIO(get_file(zipf)))
    shutil.rmtree(key, ignore_errors=True)
    for n in z.namelist():
        if any(n.startswith(s) for s in source_paths):
            z.extract(n, key)
            subprocess.run("dos2unix {}".format(n), cwd=key, shell=True)
    # Download and apply patches
    patches = (get_file(os.path.join(os.path.dirname(upatch), p)).decode("utf-8")
               for p in get_regex(upatch, rpatch))
    patches = (re.sub(r"([-+]{3} .*?)\d+_p\d+(\..*)", r"\1\2", p) for p in patches)
    for patch in patches:
        print(patch)
        subprocess.run("patch -l", input=patch, encoding='ascii',
                       cwd="{}/source".format(key), shell=True)

print("Normalizing FatFs newlines and whitespace...")
subprocess.run("sh ./post_script.sh > /dev/null 2>&1", shell=True)
