#!/usr/bin/env just --justfile

default:
    @just --list

help:
    @echo "Hello from solutions to Advent of Code 2025!"
    @printf "%s\n" "To create the executable for a specific day, run " " just day_n " "where 'n' is the number of the day/problem."

build:
    @echo "to build ..."