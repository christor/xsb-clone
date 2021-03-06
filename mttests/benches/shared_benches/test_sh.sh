#! /bin/sh

XEMU=$1
FILE=$2

echo "-------------------------------------------------------"
echo "--- Running benches/shared_benches/test_sh.sh       ---"
echo "-------------------------------------------------------"

# XEMU and options must be together in quotes
 ../genbench.sh "$XEMU"  "[trans_clos],readGraph(g256x128)."\
			 "sh_benches(g256x128,256)." "$FILE"
 ../genbench.sh "$XEMU"  "[trans_clos],readGraph(g512x8)."\
			 "sh_benches(g512x8,512)." "$FILE"
 ../genbench.sh "$XEMU"  "[trans_clos],readGraph(g2048x2)."\
			 "sh_benches(g2048x2,2048)." "$FILE"
 ../genbench.sh "$XEMU"  "[trans_clos],readGraph(g8192x1)."\
			 "sh_benches(g8192x1,8192)." "$FILE"



