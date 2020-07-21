#!/bin/bash

set -x
exec clang -o imagent-trustall.dylib -dynamiclib imagent-trustall.m -framework Foundation
