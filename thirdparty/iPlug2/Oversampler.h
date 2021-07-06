/*
 ==============================================================================

 This file is part of the iPlug 2 library. Copyright (C) the iPlug 2 developers.

 See LICENSE.txt for  more info.

 ==============================================================================
*/

#pragma once

#define OVERSAMPLING_FACTORS_VA_LIST "None", "2x", "4x", "8x", "16x"

#include <functional>
#include <vector>
#include <memory>
#include <cmath>

#include "hiir/Upsampler2xFpu.h"
#include "hiir/Downsampler2xFpu.h"

namespace iplug {

using namespace hiir;

enum EFactor
{
  kNone = 0,
  k2x,
  k4x,
  k8x,
  k16x,
  kNumFactors
};

template<typename T = double>
class OverSampler
{
public:
  OverSampler(EFactor factor = kNone, int nInChannels = 1, int nOutChannels = 1)
  : mNInChannels(nInChannels)
  , mNOutChannels(nOutChannels)
  {

    static constexpr double coeffs2x[12] = { 0.036681502163648017, 0.13654762463195794, 0.27463175937945444, 0.42313861743656711, 0.56109869787919531, 0.67754004997416184, 0.76974183386322703, 0.83988962484963892, 0.89226081800387902, 0.9315419599631839, 0.96209454837808417, 0.98781637073289585 };
    static constexpr double coeffs4x[4] = {0.041893991997656171, 0.16890348243995201, 0.39056077292116603, 0.74389574826847926 };
    static constexpr double coeffs8x[3] = {0.055748680811302048, 0.24305119574153072, 0.64669913119268196 };
    static constexpr double coeffs16x[2] = {0.10717745346023573, 0.53091435354504557 };

    for (auto c = 0; c < mNInChannels; c++)
    {
      mUpsampler2x.emplace_back(new Upsampler2xFpuTpl<12, T>());
      mUpsampler4x.emplace_back(new Upsampler2xFpuTpl<4, T>());
      mUpsampler8x.emplace_back(new Upsampler2xFpuTpl<3, T>());
      mUpsampler16x.emplace_back(new Upsampler2xFpuTpl<2, T>());

      mUpsampler2x[c]->set_coefs(coeffs2x);
      mUpsampler4x[c]->set_coefs(coeffs4x);
      mUpsampler8x[c]->set_coefs(coeffs8x);
      mUpsampler16x[c]->set_coefs(coeffs16x);

      // ptr location doesn't matter at this stage
      mNextInputPtrs.push_back(mUp2x.data());
    }

    for (auto c = 0; c < mNOutChannels; c++)
    {
      mDownsampler2x.emplace_back(new Downsampler2xFpuTpl<12, T>());
      mDownsampler4x.emplace_back(new Downsampler2xFpuTpl<4, T>());
      mDownsampler8x.emplace_back(new Downsampler2xFpuTpl<3, T>());
      mDownsampler16x.emplace_back(new Downsampler2xFpuTpl<2, T>());

      mDownsampler2x[c]->set_coefs(coeffs2x);
      mDownsampler4x[c]->set_coefs(coeffs4x);
      mDownsampler8x[c]->set_coefs(coeffs8x);
      mDownsampler16x[c]->set_coefs(coeffs16x);

      // ptr location doesn't matter at this stage
      mNextOutputPtrs.push_back(mDown2x.data());
    }

    SetOverSampling(factor);

    Reset();
  }

  ~OverSampler()
  {
    mUpsampler2x.clear();
    mDownsampler2x.clear();
    mUpsampler4x.clear();
    mDownsampler4x.clear();
    mUpsampler8x.clear();
    mDownsampler8x.clear();
    mUpsampler16x.clear();
    mDownsampler16x.clear();
  }

  OverSampler(const OverSampler&) = delete;
  OverSampler& operator=(const OverSampler&) = delete;

  void Reset(int blockSize = 512)
  {
    int numBufSamples = blockSize;

    numBufSamples *= mNInChannels;

    mUp2x.resize(2 * numBufSamples);
    mUp4x.resize(4 * numBufSamples);
    mUp8x.resize(8 * numBufSamples);
    mUp16x.resize(16 * numBufSamples);

    mDown2x.resize(2 * numBufSamples);
    mDown4x.resize(4 * numBufSamples);
    mDown8x.resize(8 * numBufSamples);
    mDown16x.resize(16 * numBufSamples);

    mUp16BufferPtrs.clear();
    mUp8BufferPtrs.clear();
    mUp4BufferPtrs.clear();
    mUp2BufferPtrs.clear();

    mDown16BufferPtrs.clear();
    mDown8BufferPtrs.clear();
    mDown4BufferPtrs.clear();
    mDown2BufferPtrs.clear();

    for (auto c = 0; c < mNInChannels; c++)
    {
      mUpsampler2x[c]->clear_buffers();
      mUpsampler4x[c]->clear_buffers();
      mUpsampler8x[c]->clear_buffers();
      mUpsampler16x[c]->clear_buffers();

      mUp2BufferPtrs.push_back(mUp2x.data() + c * 2 * blockSize);
      mUp4BufferPtrs.push_back(mUp4x.data() + (c * 4 * blockSize));
      mUp8BufferPtrs.push_back(mUp8x.data() + (c * 8 * blockSize));
      mUp16BufferPtrs.push_back(mUp16x.data() + (c * 16 * blockSize));
    }

    for (auto c = 0; c < mNOutChannels; c++)
    {
      mDownsampler2x[c]->clear_buffers();
      mDownsampler4x[c]->clear_buffers();
      mDownsampler8x[c]->clear_buffers();
      mDownsampler16x[c]->clear_buffers();

      mDown2BufferPtrs.push_back(mDown2x.data() + c * 2 * blockSize);
      mDown4BufferPtrs.push_back(mDown4x.data() + (c * 4 * blockSize));
      mDown8BufferPtrs.push_back(mDown8x.data() + (c * 8 * blockSize));
      mDown16BufferPtrs.push_back(mDown16x.data() + (c * 16 * blockSize));
    }
  }

  /** Over sample an input block with a per-block function (up sample input -> process with function -> down sample)
   * @param inputs Two-dimensional array containing the non-interleaved input buffers of audio samples for all channels
   * @param outputs Two-dimensional array for audio output (non-interleaved).
   * @param nFrames The block size for this block: number of samples per channel.
   * @param nInChans The number of input channels to process. Must be less or equal to the number of channels passed to the constructor
   * @param nOutChans The number of output channels to process. Must be less or equal to the number of channels passed to the constructor
   * @param func The function that processes the audio sample at the higher sampling rate. NOTE: std::function can call malloc if you pass in captures */
  template <class BlockProcessFunc> // void(T**, T**, int)
  void ProcessBlock(T** inputs, T** outputs, int nFrames, int nInChans, int nOutChans, BlockProcessFunc&& func)
  {
    assert(nInChans <= mNInChannels);
    assert(nOutChans <= mNOutChannels);

    if(mRate != mPrevRate)
    {
      switch (mRate) {
        case 2:
          mInPtrLoopSrc = &mUp2BufferPtrs;
          mOutPtrLoopSrc = &mDown2BufferPtrs;
          break;
        case 4:
          mInPtrLoopSrc = &mUp4BufferPtrs;
          mOutPtrLoopSrc = &mDown4BufferPtrs;
          break;
        case 8:
          mInPtrLoopSrc = &mUp8BufferPtrs;
          mOutPtrLoopSrc = &mDown8BufferPtrs;
          break;
        case 16:
          mInPtrLoopSrc = &mUp16BufferPtrs;
          mOutPtrLoopSrc = &mDown16BufferPtrs;
          break;
        default:
          break;
      }

      mPrevRate = mRate;
    }

    for(auto c = 0; c < nInChans; c++) {
      if (mRate >= 2) {
        mUpsampler2x[c]->process_block(mUp2BufferPtrs[c], inputs[c], nFrames);
      }
      if (mRate >= 4) {
        mUpsampler4x[c]->process_block(mUp4BufferPtrs[c], mUp2BufferPtrs[c], nFrames * 2);
      }
      if (mRate >= 8) {
        mUpsampler8x[c]->process_block(mUp8BufferPtrs[c], mUp4BufferPtrs[c], nFrames * 4);
      }
      if (mRate == 16) {
        mUpsampler16x[c]->process_block(mUp16BufferPtrs[c], mUp8BufferPtrs[c], nFrames * 8);
      }
    }

    if (mRate == 1) {
      func(inputs, outputs, nFrames);
    } else {
      for (auto i = 0; i < mRate; i++) {
        for(auto c = 0; c < nInChans; c++) {
          mNextInputPtrs[c] = (*mInPtrLoopSrc)[c] + (i * nFrames);
          mNextOutputPtrs[c] = (*mOutPtrLoopSrc)[c] + (i * nFrames);
        }
        func(mNextInputPtrs.data(), mNextOutputPtrs.data(), nFrames);
      }
    }

    for(auto c = 0; c < nOutChans; c++) {
      if (mRate == 16) {
        mDownsampler16x[c]->process_block(mDown8BufferPtrs[c], mDown16BufferPtrs[c], nFrames * 8);
      }
      if (mRate >= 8) {
        mDownsampler8x[c]->process_block(mDown4BufferPtrs[c], mDown8BufferPtrs[c], nFrames * 4);
      }
      if (mRate >= 4) {
        mDownsampler4x[c]->process_block(mDown2BufferPtrs[c], mDown4BufferPtrs[c], nFrames * 2);
      }
      if (mRate >= 2) {
        mDownsampler2x[c]->process_block(outputs[c], mDown2BufferPtrs[c], nFrames);
      }
    }
  }

  void SetOverSampling(EFactor factor)
  {
    if(factor != mFactor)
    {
      mFactor = factor;
      mRate = std::pow(2, (int) factor);

      Reset();
    }
  }

  static EFactor RateToFactor(int rate)
  {
    switch (rate)
    {
      case 1: return EFactor::kNone;
      case 2: return EFactor::k2x;
      case 4: return EFactor::k4x;
      case 8: return EFactor::k8x;
      case 16: return EFactor::k16x;
      default: assert(0); return EFactor::kNone;
    }
  }

  int GetRate()
  {
    return mRate;
  }

private:
  EFactor mFactor = kNone;
  int mPrevRate = 0;
  int mRate = 1;
  int mWritePos = 0;
  T mDownSamplerOutput = 0.;
  int mNInChannels; // 1
  int mNOutChannels;

  // the actual data
  std::vector<T> mUp16x;
  std::vector<T> mUp8x;
  std::vector<T> mUp4x;
  std::vector<T> mUp2x;

  std::vector<T> mDown16x;
  std::vector<T> mDown8x;
  std::vector<T> mDown4x;
  std::vector<T> mDown2x;

  //Ptrs into buffer data
  std::vector<T*> mUp16BufferPtrs;
  std::vector<T*> mUp8BufferPtrs;
  std::vector<T*> mUp4BufferPtrs;
  std::vector<T*> mUp2BufferPtrs;

  std::vector<T*> mDown16BufferPtrs;
  std::vector<T*> mDown8BufferPtrs;
  std::vector<T*> mDown4BufferPtrs;
  std::vector<T*> mDown2BufferPtrs;

  std::vector<T*> mNextInputPtrs;
  std::vector<T*> mNextOutputPtrs;

  //Ptrs to the buffer data ptrs, changed depending on rate (block processing only)
  std::vector<T*>* mInPtrLoopSrc = nullptr;
  std::vector<T*>* mOutPtrLoopSrc = nullptr;

  //Ptrs to oversamplers for each channel
  std::vector<std::unique_ptr<Upsampler2xFpuTpl<12, T>>> mUpsampler2x; // for 1x to 2x SR
  std::vector<std::unique_ptr<Upsampler2xFpuTpl<4, T>>> mUpsampler4x;  // for 2x to 4x SR
  std::vector<std::unique_ptr<Upsampler2xFpuTpl<3, T>>> mUpsampler8x;  // for 4x to 8x SR
  std::vector<std::unique_ptr<Upsampler2xFpuTpl<2, T>>> mUpsampler16x; // for 8x to 16x SR

  std::vector<std::unique_ptr<Downsampler2xFpuTpl<12, T>>> mDownsampler2x; // decimator for 2x to 1x SR
  std::vector<std::unique_ptr<Downsampler2xFpuTpl<4, T>>> mDownsampler4x;  // decimator for 4x to 2x SR
  std::vector<std::unique_ptr<Downsampler2xFpuTpl<3, T>>> mDownsampler8x;  // decimator for 8x to 4x SR
  std::vector<std::unique_ptr<Downsampler2xFpuTpl<2, T>>> mDownsampler16x; // decimator for 16x to 8x SR
};

} // namespace iplug
