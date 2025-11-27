IFS= "A"
set foo bar bam 
24
echo “$@”
foo bar bam
echo "$*"
fooAbarAbam
unset IFS
echo "$*"
foo bar bam 

