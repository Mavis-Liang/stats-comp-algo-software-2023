#!/usr/bin/env bash

module load tex
for commit_count in {2..100}
do
  let linenum="10+$commit_count"
  sed -i "$linenum i This is the first sentence." foo.tex
  pdflatex foo.tex > /dev/null 2>&1
  git add -u
  git commit -m "Add $commit_count sentence to TeX file"
done
