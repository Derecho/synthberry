#!/bin/sh
git commit -a
make doc
cd doc/html && git commit -a -m "Updated documentation" && git push origin gh-pages && cd ../..
git push origin master
