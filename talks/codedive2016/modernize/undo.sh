#!/bin/bash
for f in *.before.cpp; do
  cp $f ${f%.before.cpp}.after.cpp
done
