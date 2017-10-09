#!/usr/bin/env bash

cd /home/anna/qore2

if [ ! -f "./commitNo" ] ; then
  var=0
else
  var=`cat ./commitNo`
fi

var=$((var+1))
#DATE=`date '+%d-%b-%Y-%H:%M'`
read -p "Enter commit message: " -e commit

git add -u && git commit -m "Commit${var} - ${commit}" && git push

echo "${var}" > ./commitNo
sleep 2
