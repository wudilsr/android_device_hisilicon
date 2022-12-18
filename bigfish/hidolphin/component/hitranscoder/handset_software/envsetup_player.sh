#!/bin/sh
find . -name Android.mk.release | xargs rename 's/.release//'
