#! /bin/sh

PROLOG=$1

../touch.sh cmd...

split -l 7 cmd... cmd..._

for f in cmd..._*; do
     cat cmd...hdr $f | "$PROLOG"
done

rm cmd... cmd...hdr cmd..._*
