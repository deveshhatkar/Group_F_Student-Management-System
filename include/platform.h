// Header for cross-platform determination based on answers from the following Stack Overflow question
// https://stackoverflow.com/questions/5919996/how-to-detect-reliably-mac-os-x-ios-linux-windows-in-c-preprocessor
// Question by Brian Tompsett
// Answers by Evgeny Gavrin, Top-Master, PatchyFog and Buzz Lightyear

#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H
#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#define NULL_DEV_PATH "NUL"
#define CLS_COMMAND "cls"
#ifdef _WIN64
//define something for Windows (64-bit only)
#else
//define something for Windows (32-bit only)
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#define NULL_DEV_PATH "/dev/null"
#define CLS_COMMAND "clear"
#else
#   error "Unknown Apple platform"
#endif
#elif __ANDROID__
// android
#elif __linux__
// linux
#define NULL_DEV_PATH "/dev/null"
#define CLS_COMMAND "clear"
#elif __unix__ // all unices not caught above
// Unix
#elif defined(_POSIX_VERSION)
// POSIX
#else
#   error "Unknown compiler"
#endif
#endif

