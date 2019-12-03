cmake_minimum_required(VERSION 3.10)

project(OCR)

add_executable(OCR main.c nn2/networkV2.c nn2/matrix/matrix.c)