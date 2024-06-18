#pragma once

constexpr int width = 1920 / 2;
constexpr int height = width / 16 * 9;
static const int N = 1024;  // 1024 samples for the FFT - 1024 / 44100 = 0.023 seconds -- values 2^n
