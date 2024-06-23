#pragma once

constexpr int width = 1920 / 2;
constexpr int height = width / 16 * 8;
static const int N = 4096;  // 1024 samples for the FFT - 1024 / 44100 = 0.023 seconds -- values 2^n
/*
1024 or lower appears to be way too small
2048 is getting Ok
4096 is in my opinion the bes
8192 is too much but still works
16384 is too much and I think it's slow
*/
