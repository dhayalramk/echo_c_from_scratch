#!/usr/bin/env bash
# Basic test suite for myecho

set -e

echo "Test 1: simple arguments"
OUT=$(./myecho hello world)
[ "$OUT" = "hello world" ] && echo "✅ Passed" || echo "❌ Failed: $OUT"

echo "Test 2: -n flag (no newline)"
OUT=$(./myecho -n no_newline)
[ "$OUT" = "no_newline" ] && echo "✅ Passed" || echo "❌ Failed: $OUT"

echo "Test 3: -e flag with newline and tab"
OUT=$(./myecho -e "a\nb\tc")
EXPECTED="a
b	c"
[ "$OUT" = "$EXPECTED" ] && echo "✅ Passed" || echo "❌ Failed"

echo "All tests complete!"
