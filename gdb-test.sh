#!/bin/bash
#!/bin/bash
scriptdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "$@" > /projects/findindi/workspace/gdb-launch.txt
pwd >> $scriptdir/gdb-launch.txt


#echo "$@" > /projects/findindi/workspace/gdb-launch.txt
#exit 1
gdb -x $scriptdir/gdb-startup.gdb "$@"
