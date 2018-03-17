#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

LIPCOIND=${LIPCOIND:-$SRCDIR/lipcoind}
LIPCOINCLI=${LIPCOINCLI:-$SRCDIR/lipcoin-cli}
LIPCOINTX=${LIPCOINTX:-$SRCDIR/lipcoin-tx}
LIPCOINQT=${LIPCOINQT:-$SRCDIR/qt/lipcoin-qt}

[ ! -x $LIPCOIND ] && echo "$LIPCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
LIPCVER=($($LIPCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for lipcoind if --version-string is not set,
# but has different outcomes for lipcoin-qt and lipcoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$LIPCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $LIPCOIND $LIPCOINCLI $LIPCOINTX $LIPCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${LIPCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${LIPCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
